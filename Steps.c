
#include "Steps.h"
#include<stdlib.h>


//初期化する
void Steps_init(Steps *this)
{
	
	this->i = 0;
	this->time = 0;
	this->sum = 0;
	this->j = 0;
	this->run_time = 0;
	this->step = 0;//現在の段差
	this->phase = 0;//階段を上るフェーズ
	for(this->i=0 ; this->i<125; this->i++){
		this->gyro_ave[this->i] = 600;//ジャイロセンサーの値の平均を取るための250の配列（1秒分）
	}
}
//直近の1秒のジャイロセンサの平均を出す関数
int Steps_GetAVE(Steps *this)
{
	this->sum = 0;
	this->gyro_ave[this->i] = GyroSensor_getAngularVelocity(this->gyroSensor);
	for(this->j = 0; this->j < 125; this->j++)	this->sum += this->gyro_ave[this->j];
	
	if(this->i == 125)	this->i = 0;
	else			this->i++;
	
	return this->sum/125;
}

//階段走行をする
void Steps_run(Steps *this)
{
	//if(this->time > 3500){
		switch(this->phase){
	
		case 0:
			LineTracer_changePID(this->lineTracer , 0.9, 0.08, 0.08, 600);
			LineTracer_trace(this->lineTracer, 20);
			this->phase = 1;
			break;
		
		case 1://段差を検知するまでライントレース
			LineTracer_trace(this->lineTracer, 20);
			if(this->run_time > 500){
				if(GyroSensor_getAngularVelocity(this->gyroSensor) > 700){
					//ecrobot_sound_tone(2000, 200, 50);
					if(!this->step)	this->phase = 2;
					else	this->phase = 3;
					this->run_time = 0;
				}
			}
			this->run_time+=4;
			break;
	
		case 2://上るまで直進する(一段目)
			BalanceRunner_run(this->balanceRunner, 0, 30);
			if(this->run_time > 1200){
					this->phase = 1;
					this->step = 2;
					this->run_time = 0;
			}
			this->run_time += 4;
			break;

		case 3://上るまで直進する（2段目）
			BalanceRunner_run(this->balanceRunner, 0, 30);
			if(this->run_time > 2000){
					this->phase = 4;
					this->run_time = 0;
			}
			this->run_time += 4;
			break;

		case 4://速度を落として90度カーブを曲がる
			LineTracer_trace(this->lineTracer, 12);
			//ecrobot_sound_tone(2000, 200, 50);
			if(this->run_time > 4000){
				if(abs(Motor_getAngle(this->leftMotor)-Motor_getAngle(this->rightMotor)) < 300){
					this->step = 3;
					this->run_time = 1;
				}
			 if(this->step == 2)	this->run_time+=4;
				if(this->run_time >= 2500){
					ecrobot_sound_tone(2000, 200, 50);
					this->phase = 5;
					this->run_time = 0;
				}
			}
			this->run_time+=4;
			break;

		case 5:
			BalanceRunner_run(this->balanceRunner, 0, 30);
			this->run_time+=4;
			if(this->run_time > 3000)	this->phase  = 6;
			break;

		case 6:
			LineTracer_trace(this->lineTracer, 70);
			break;

		}
	//}else	LineTracer_trace(this->lineTracer, 55);
	//this->time+=4;
}
