#include "zf_driver_pwm.h"
#include "zf_driver_gpio.h"
#include "motor.h"

#define pwm_max  10000
#define MOTOR1_DIR               (D0 )
#define MOTOR1_PWM               (PWM2_MODULE3_CHA_D2)

#define MOTOR2_DIR               (D1 )
#define MOTOR2_PWM               (PWM2_MODULE3_CHB_D3)

#define MOTOR3_DIR               (D13 )
#define MOTOR3_PWM               (PWM1_MODULE1_CHB_D15)

#define MOTOR4_DIR               (D12 )
#define MOTOR4_PWM               (PWM1_MODULE1_CHA_D14)


void motor_init(unsigned int freq, unsigned int duty)
{
    pwm_init(MOTOR1_PWM, freq, duty); 
	  pwm_init(MOTOR2_PWM, freq, duty);
	  pwm_init(MOTOR3_PWM, freq, duty); 
	  pwm_init(MOTOR4_PWM, freq, duty);
	gpio_init( MOTOR1_DIR, GPO, GPIO_HIGH, GPO_PUSH_PULL);
	gpio_init( MOTOR2_DIR, GPO, GPIO_HIGH, GPO_PUSH_PULL);
	gpio_init( MOTOR3_DIR, GPO, GPIO_HIGH, GPO_PUSH_PULL);
	gpio_init( MOTOR4_DIR, GPO, GPIO_HIGH, GPO_PUSH_PULL);


}

void motor_out(int pwm_1,int pwm_2,int pwm_3,int pwm_4)
{
  if(pwm_1>0){
		gpio_set_level(MOTOR1_DIR, GPIO_HIGH);
	  pwm_set_duty(MOTOR1_PWM, pwm_1);
	}		
	else{
		gpio_set_level(MOTOR1_DIR, GPIO_LOW);
		pwm_set_duty(-MOTOR1_PWM, pwm_1);
	}

	
	if(pwm_2>0){
		gpio_set_level(MOTOR2_DIR, GPIO_HIGH);
	  pwm_set_duty(MOTOR2_PWM, pwm_2);
	}		
	else{
		gpio_set_level(MOTOR2_DIR, GPIO_LOW);
		pwm_set_duty(-MOTOR2_PWM, pwm_2);
	}	
	
	}





