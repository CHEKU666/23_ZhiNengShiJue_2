#ifndef _pid_h_
#define _pid_h_


typedef struct
{
    float                kp;         //P
    float                ki;         //I
    float                kd;         //D
    float                imax;       //�����޷�

    float                out_p;  //KP���
    float                out_i;  //KI���
    float                out_d;  //KD���
    float                out;    //pid���

    float                integrator; //< ����ֵ
    float                last_error; //< �ϴ����
    float                last_derivative;//< �ϴ���������ϴ����֮��
    unsigned long        last_t;     //< �ϴ�ʱ��
}pid_param_t;

extern pid_param_t pid12;
extern pid_param_t pid34;
extern pid_param_t pid_z12;
extern pid_param_t pid_z34;
extern pid_param_t pid_adjustment;

float constrain_float(float amt, float low, float high);//�޷�����
void PidInit(pid_param_t * pid);
float PidLocCtrl(pid_param_t * pid, float error);
float PidIncCtrl(pid_param_t * pid, float error);


#endif
