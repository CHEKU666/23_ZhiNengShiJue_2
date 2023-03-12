#ifndef _pid_h_
#define _pid_h_


typedef struct
{
    float                kp;         //P
    float                ki;         //I
    float                kd;         //D
    float                imax;       //积分限幅

    float                out_p;  //KP输出
    float                out_i;  //KI输出
    float                out_d;  //KD输出
    float                out;    //pid输出

    float                integrator; //< 积分值
    float                last_error; //< 上次误差
    float                last_derivative;//< 上次误差与上上次误差之差
    unsigned long        last_t;     //< 上次时间
}pid_param_t;

extern pid_param_t pid12;
extern pid_param_t pid34;
extern pid_param_t pid_z12;
extern pid_param_t pid_z34;
extern pid_param_t pid_adjustment;

float constrain_float(float amt, float low, float high);//限幅函数
void PidInit(pid_param_t * pid);
float PidLocCtrl(pid_param_t * pid, float error);
float PidIncCtrl(pid_param_t * pid, float error);


#endif
