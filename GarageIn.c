
#include "Direction.h"
#include "GarageIn.h"

#define P_GAIN             2.5F /* 完全停止用モータ制御比例係数 */
#define PWM_ABS_MAX          60 /* 完全停止用モータ制御PWM絶対最大値 */
#define	TASK_CYCLE	4	/* タスクの周期（msec）*/
#define TAIL_ANGLE_STAND_UP 90  /* 完全停止時のしっぽ角度*/

// 非公開操作
static void GarageIn_tailcontrol(signed int angle);


// 初期化する
void GarageIn_init(GarageIn* this)
{
	this->runtime = 1000; //停止するまでの走行時間(ms)
}


//ガレージインを行なう
void GarageIn_run(GarageIn* this)
{
	//しっぽを接地させる
	GarageIn_tailcontrol(TAIL_ANGLE_STAND_UP);

	//一定時間(runtime)直進後停止
	if(this->runtime >= 0){
		Motor_rotate(this->leftMotor ,50);
		Motor_rotate(this->rightMotor,50);
		this->runtime = this->runtime - 4;
	}else{
		Motor_rotate(this->leftMotor ,0);
		Motor_rotate(this->rightMotor,0);
	}
}


static void GarageIn_tailcontrol(signed int angle)
{
	float pwm = (float)(angle - nxt_motor_get_count(NXT_PORT_A))*P_GAIN; /* 比例制御 */
	/* PWM出力飽和処理 */
	if (pwm > PWM_ABS_MAX)
	{
		pwm = PWM_ABS_MAX;
	}
	else if (pwm < -PWM_ABS_MAX)
	{
		pwm = -PWM_ABS_MAX;
	}

	nxt_motor_set_speed(NXT_PORT_A, (signed char)pwm, 1);
}
