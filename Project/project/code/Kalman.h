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

#ifndef _Kalman_h_
#define _Kalman_h_
    typedef struct 
    {
        float LastP;//上次估算协方差 初始化值为0.02
        float Now_P;//当前估算协方差 初始化值为0
        float out;//卡尔曼滤波器输出 初始化值为0
        float Kg;//卡尔曼增益 初始化值为0
        float Q;//过程噪声协方差 初始化值为0.001
        float R;//观测噪声协方差 初始化值为0.543
    }KFP;//Kalman Filter parameter
    // The angle should be in degrees and the rate should be in degrees per second and the delta time in seconds
    float getAngle(float newAngle, float newRate, float dt);

    void setAngle(float angle); // Used to set angle, this should be set as the starting angle
    float getRate(); // Return the unbiased rate

    /* These are used to tune the Kalman filter */
    void setQangle(float Q_angle);
    /**
     * setQbias(float Q_bias)
     * Default value (0.003f) is in Kalman.cpp. 
     * Raise this to follow input more closely,
     * lower this to smooth result of kalman filter.
     */
    void setQbias(float Q_bias);
    void setRmeasure(float R_measure);

    float getQangle();
    float getQbias();
    float getRmeasure();
    /* Kalman filter variables */
    extern float Q_angle; // Process noise variance for the accelerometer
    extern float Q_bias; // Process noise variance for the gyro bias
    extern float R_measure; // Measurement noise variance - this is actually the variance of the measurement noise
    extern float angle; // The angle calculated by the Kalman filter - part of the 2x1 state vector
    extern float bias; // The gyro bias calculated by the Kalman filter - part of the 2x1 state vector
    extern float rate; // Unbiased rate calculated from the rate and the calculated bias - you have to call getAngle to update the rate
    extern float P[2][2]; // Error covariance matrix - This is a 2x2 matrix
    extern float YawAxis; // 小车只在xy平面上移动，陀螺仪位姿结算只涉及偏航角

    /* 测试只对陀螺仪初始数据滤波*/

    void KFP_acc_Init(KFP *KFP_height);
    void KFP_gyro_Init(KFP *KFP_height);
    float kalmanFilter(KFP *kfp, float input);
    extern KFP KFP_acc_x;
    extern KFP KFP_acc_y;
    extern KFP KFP_gyro;

#endif