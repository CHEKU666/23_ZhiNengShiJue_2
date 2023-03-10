#include "InertNav.h"
#include "math.h"
float Gyro = 0;  //保存上一次的角速度输出，在角度积分时使用中值法
float yawViaGyro = 0;
float Acc[2] = {0,0};
float absAcc[2] = {0, 0}; // 保存上一次的加速度输出，在速度积分时使用中值法
float absV[2] = {0,0};  
strPosition selfLoc;

void getNowYaw(KFP* strKFP, float t){
    yawViaGyro = yawViaGyro+(Gyro+kalmanFilter(strKFP,mpu6050_gyro_transition(mpu6050_gyro_z)))/2*t;
    Gyro=kalmanFilter(strKFP,mpu6050_gyro_transition(mpu6050_gyro_z));  //更新角速度
};
void getNowAbsVAndLoc(float t,float Yaw){
        Acc[0] = kalmanFilter(&KFP_acc_x,mpu6050_acc_transition(mpu6050_acc_x));  //更新加速度
        Acc[1] = kalmanFilter(&KFP_acc_y,mpu6050_acc_transition(mpu6050_acc_y));
        selfLoc.coordinateX +=(absV[0]+(absV[0]+(absAcc[0]+ (Acc[0] *cosf(Yaw)-Acc[1]*sinf(Yaw)))/2*t))/2*t; //更新坐标
        selfLoc.coordinateY +=(absV[1]+(absV[1]+(absAcc[1]+ (Acc[0] *sinf(Yaw)+Acc[1]*cosf(Yaw)))/2*t))/2*t;
        absV[0] =absV[0]+(absAcc[0]+ (Acc[0] * cosf(Yaw) -Acc[1]*sinf(Yaw)))/2*t;   //更新相对于大地系的速度
        absV[1] =absV[1]+(absAcc[1]+ (Acc[0] * sinf(Yaw) + Acc[1] * cosf(Yaw)))/2*t;
        absAcc[0] = Acc[0] * cosf(Yaw) - Acc[1] * sinf(Yaw); // 更新相对于大地系的加速度
        absAcc[1] = Acc[0]*sinf(Yaw)+Acc[1]*cosf(Yaw);
};

