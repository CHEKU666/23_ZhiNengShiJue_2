#ifndef _motor_h_
#define _motor_h_

void motor_init(unsigned int freq, unsigned int duty);
void motor_out(int duty_l1,int duty_r1,int duty_l2,int duty_r2);


#endif