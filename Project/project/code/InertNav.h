#ifndef _InertNav_h_
#define _InertNav_h_
#include "zf_common_headfile.h"
/*坐标结构体*/
typedef struct Position
{
    int16 coordinateX;
    int16 coordinateY;
}strPosition;
extern float Gyro;          //卡尔曼滤波获得的角速度 
extern float yawViaGyro;    // 卡尔曼滤波得出的角速度再次积分获得的偏航角
extern float Acc[2];        //卡尔曼滤波获得的加速度
extern float absAcc[2];     //相对于大地系的加速度
extern float absV[2];       //卡尔曼滤波得出的加速度再次积分获得的速度
extern strPosition selfLoc; // 小车绝对坐标

/**
 * 更新角速度,获取新的姿态角
 * @param 角速度卡尔曼结构体
 * @param 时间间隔 m/s
 * @return 偏航角 。
 */
float getNowYaw(KFP* strKFP,float t);
/* 更新加速度和新的大地系x,y方向速度,以及自身坐标*/
void getNowAbsVAndLoc(float t, float Yaw);

#endif