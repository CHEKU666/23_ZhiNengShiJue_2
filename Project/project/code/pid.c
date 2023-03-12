#include "pid.h"


pid_param_t pid12;
pid_param_t pid34;
pid_param_t pid_z12;
pid_param_t pid_z34;
pid_param_t pid_adjustment;

void PidInit(pid_param_t * pid)//pid参数初始化
{
  pid->kp        = 0;
  pid->ki        = 0;
  pid->kd        = 0;
  pid->imax      = 0;
  pid->out_p     = 0;
  pid->out_i     = 0;
  pid->out_d     = 0;
  pid->out       = 0;
  pid->integrator= 0;
  pid->last_error= 0;
  pid->last_derivative   = 0;
  pid->last_t    = 0;
}



//限幅函数
float constrain_float(float amt, float low, float high)
{
  return ((amt)<(low)?(low):((amt)>(high)?(high):(amt)));
}



/*************************************************************************
*  函数名称：float PidLocCtrl(pid_param_t * pid, float error)
*  功能说明：pid位置式控制器输出
*  参数说明：
* @param    pid     pid参数
* @param    error   pid输入误差
*  函数返回：PID输出结果
*  修改时间：2020年4月1日
*  备    注：
*************************************************************************/
float PidLocCtrl(pid_param_t * pid, float error)
{
  /* 累积误差 */
  pid->integrator += error;
  
  /* 误差限幅 */
  constrain_float(pid->integrator, -pid->imax, pid->imax);
//  if(error == 0) pid->integrator = 0; 
  
  pid->out_p = pid->kp * error;
  pid->out_i = pid->ki * pid->integrator;
  pid->out_d = pid->kd * (error - pid->last_error);
  
  pid->last_error = error;
  
  pid->out = pid->out_p + pid->out_i + pid->out_d;
  
  return pid->out;
}


/*************************************************************************
*  函数名称：float PidIncCtrl(pid_param_t * pid, float error)
*  功能说明：pid增量式控制器输出
*  参数说明：
* @param    pid     pid参数
* @param    error   pid输入误差
*  函数返回：PID输出结果   注意输出结果已经包涵了上次结果
*  修改时间：2020年4月1日
*  备    注：
*************************************************************************/
float PidIncCtrl(pid_param_t * pid, float error)
{
  

  
  pid->out_p = pid->kp * (error - pid->last_error);
  pid->out_i = pid->ki * error;
  pid->out_d = pid->kd * ((error - pid->last_error) - pid->last_derivative);
  
  pid->last_derivative = error - pid->last_error;
  pid->last_error = error;
  
  pid->out += pid->out_p + pid->out_i + pid->out_d;
   /* 输出限幅 */
  
  return pid->out;
}
