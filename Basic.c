#include "Basic.h"
#include<stdlib.h>

void Basic_init(Basic *this)
{
	this->run_time = 0;
	//this->angleR = 0;
	//this->angleL = 0;
	this->speed = 140;
	//this->phase = 0;
}

void Basic_run(Basic *this)
{

	if(this->run_time > 3000 && this->run_time < 9000)	this->speed = 100;
	//else if (this->run_time > 20000 && this->run_time < 25000)	this->speed = 120;
	else if (this->run_time > 25000 && this->run_time < 28500)	this->speed = 120;
	else	this->speed = 140;
	


/*	if(this->run_time < 5000){
		this->speed = 140;
	}else if(this->run_time < 5000)
	else if(this->run_time % 20 == 0){
		if(abs((Motor_getAngle(this->leftMotor) - this->angleL) - (Motor_getAngle(this->rightMotor) - this->angleR)) > 30){
			this->speed = 100;
			ecrobot_sound_tone(2000, 200, 50);
		}else{
			this->speed =140;
		}
	}else{
		this->angleR = Motor_getAngle(this->rightMotor);
		this->angleL = Motor_getAngle(this->leftMotor);
	}
	*/
	LineTracer_trace(this->lineTracer, this->speed);

	this->run_time+=4;
}

