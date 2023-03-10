/* Copyright (C) 2012 Kristian Lauszus, TKJ Electronics. All rights reserved.
 This software may be distributed and modified under the terms of the GNU
 General Public License version 2 (GPL2) as published by the Free Software
 Foundation and appearing in the file GPL2.TXT included in the packaging of
 this file. Please note that GPL2 Section 2[b] requires that all works based
 on this software must also be made publicly available under the terms of
 the GPL2 ("Copyleft").
 Contact information
 -------------------
 Kristian Lauszus, TKJ Electronics
 Web      :  http://www.tkjelectronics.com
 e-mail   :  kristianl@tkjelectronics.com
 */

#include "Kalman.h"

    /* We will set the variables like so, these can also be tuned by the user */
    float Q_angle = 0.001f;
    float Q_bias = 0.003f;
    float R_measure = 0.03f;

    float angle = 0.0f; // Reset the angle
    float bias = 0.0f;  // Reset bias

    float P[2][2] = {{0.0f,0.0f},{0.0f,0.0f}}; // Since we assume that the bias is 0 and we know the starting angle (use setAngle), the error covariance matrix is set like so - see: http://en.wikipedia.org/wiki/Kalman_filter#Example_application.2C_technical
    float rate;
// The angle should be in degrees and the rate should be in degrees per second and the delta time in seconds
float getAngle(float newAngle, float newRate, float dt)
{
    // KasBot V2  -  Kalman filter module - http://www.x-firm.com/?page_id=145
    // Modified by Kristian Lauszus
    // See my blog post for more information: http://blog.tkjelectronics.dk/2012/09/a-practical-approach-to-kalman-filter-and-how-to-implement-it

    // Discrete Kalman filter time update equations - Time Update ("Predict")
    // Update xhat - Project the state ahead
    /* Step 1 */
    rate = newRate - bias;
    angle += dt * rate;

    // Update estimation error covariance - Project the error covariance ahead
    /* Step 2 */
    P[0][1] -= dt * P[1][1];
    P[1][0] -= dt * P[1][1];
    P[0][0] += dt * (dt * P[1][1] - P[0][1] - P[1][0] + Q_angle);
    P[1][1] += Q_bias * dt;

    // Discrete Kalman filter measurement update equations - Measurement Update ("Correct")
    // Calculate Kalman gain - Compute the Kalman gain
    /* Step 4 */
    float S = P[0][0] + R_measure; // Estimate error
    /* Step 5 */
    float K[2]; // Kalman gain - This is a 2x1 vector
    K[0] = P[0][0] / S;
    K[1] = P[1][0] / S;

    // Calculate angle and bias - Update estimate with measurement zk (newAngle)
    /* Step 3 */
    float y = newAngle - angle; // Angle difference
    /* Step 6 */
    angle += K[0] * y;
    bias += K[1] * y;

    // Calculate estimation error covariance - Update the error covariance
    /* Step 7 */
    float P00_temp = P[0][0];
    float P01_temp = P[0][1];

    P[0][0] -= K[0] * P00_temp;
    P[0][1] -= K[0] * P01_temp;
    P[1][0] -= K[1] * P00_temp;
    P[1][1] -= K[1] * P01_temp;

    return angle;
};

void setAngle(float Angle) { angle = Angle; }; // Used to set angle, this should be set as the starting angle
float getRate() { return rate; };              // Return the unbiased rate

/* These are used to tune the Kalman filter */
void setQangle(float Qangle) {Q_angle = Qangle; };
void setQbias(float Qbias) { Q_bias = Qbias; };
void setRmeasure(float Rmeasure) { R_measure = Rmeasure; };

float getQangle() { return Q_angle; };
float getQbias() { return Q_bias; };
float getRmeasure() { return R_measure; };
/*
Q:过程噪声，Q增大，动态响应变快，收敛稳定性变坏
R:测量噪声，R增大，动态响应变慢，收敛稳定性变好
其中p的初值可以随便取，但是不能为0（为0的话卡尔曼滤波器就认为已经是最优滤波器了）
q,r的值需要我们试出来，讲白了就是(买的破温度计有多破，以及你的超人力有多强)
r参数调整滤波后的曲线与实测曲线的相近程度，r越小越接近。
q参数调滤波后的曲线平滑程度，q越小越平滑。
*/

KFP KFP_acc_x;
KFP KFP_acc_y;
KFP KFP_gyro;
void KFP_acc_Init(KFP *KFP_height)
{
    KFP_height->LastP = 0.02;
    KFP_height->Now_P = 0;
    KFP_height->out = 0;
    KFP_height->Kg = 0;
    KFP_height->Q = 0.003;
    KFP_height->R = 0.543;
}

void KFP_gyro_Init(KFP *KFP_height)
{
    KFP_height->LastP = 0.02;
    KFP_height->Now_P = 0;
    KFP_height->out = 0;
    KFP_height->Kg = 0;
    KFP_height->Q = 0.001;
    KFP_height->R = 0.6;
}
/**
 *卡尔曼滤波器
 *@param KFP *kfp 卡尔曼结构体参数
 *   float input 需要滤波的参数的测量值（即传感器的采集值）
 *@return 滤波后的参数（最优值）
 */
float kalmanFilter(KFP *kfp, float input)
{
    // 预测协方差方程：k时刻系统估算协方差 = k-1时刻的系统协方差 + 过程噪声协方差
    kfp->Now_P = kfp->LastP + kfp->Q;
    // 卡尔曼增益方程：卡尔曼增益 = k时刻系统估算协方差 / （k时刻系统估算协方差 + 观测噪声协方差）
    kfp->Kg = kfp->Now_P / (kfp->Now_P + kfp->R);
    // 更新最优值方程：k时刻状态变量的最优值 = 状态变量的预测值 + 卡尔曼增益 * （测量值 - 状态变量的预测值）
    kfp->out = kfp->out + kfp->Kg * (input - kfp->out); // 因为这一次的预测值就是上一次的输出值
    // 更新协方差方程: 本次的系统协方差付给 kfp->LastP 威下一次运算准备。
    kfp->LastP = (1 - kfp->Kg) * kfp->Now_P;
    return kfp->out;
}