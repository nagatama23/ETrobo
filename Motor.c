/****************************************************
 *  Motor.c                                         
 *  Created on: 2012/05/05 8:35:16                      
 *  Implementation of the Class Motor       
 *  Original author: hiroyuki.watanabe                     
 ****************************************************/

#include "Motor.h"


// ‰Šú‰»‚·‚é
void Motor_init(Motor* this, MOTOR_PORT_T outputPort)
{
	this->outputPort = outputPort;
}

// ‰ñ“]Šp“x‚ðƒŠƒZƒbƒg‚·‚é
void Motor_resetAngle(Motor* this)
{
	return nxt_motor_set_count(this->outputPort, 0);
}

// ‰ñ“]Šp“x‚ð“¾‚é
long Motor_getAngle(Motor* this)
{
	return nxt_motor_get_count(this->outputPort);
}

// ‰ñ“]‚³‚¹‚é
void Motor_rotate(Motor* this, int pwm)
{
	nxt_motor_set_speed(this->outputPort, pwm, 1);
} 

// K”ö‚ð“®‚©‚·
void Motor_tailControl(Motor* this, int angle)
{
	float pwm = (float)(angle - nxt_motor_get_count(this->outputPort))*P_GAIN; /* ”ä—á§Œä */
	/* PWMo—Í–O˜aˆ— */
	if (pwm > PWM_ABS_MAX)
	{
		pwm = PWM_ABS_MAX;
	}
	else if (pwm < -PWM_ABS_MAX)
	{
		pwm = -PWM_ABS_MAX;
	}

	nxt_motor_set_speed(this->outputPort, (signed char)pwm, 1);
}
