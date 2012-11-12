///////////////////////////////////////////////////////////
//  model_impl.c
///////////////////////////////////////////////////////////

#include "LineTracer.h"
#include "UI.h"
#include "ColorJudgement.h"
#include "BalanceRunner.h"
#include "TouchSensor.h"
#include "LightSensor.h"
#include "GyroSensor.h"
#include "Motor.h"
#include "SeeSaw.h"
#include "Steps.h"
#include "GarageIn.h"
#include "StepsIKB.h"
#include "Basic.h"
#include "GrayDetector.h"

#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

#define	COUNT_SCENARIO	4


unsigned int run_time;
int gyro;
int gfrag = 0;
int stop = 0;


// オブジェクトを静的に確保する
LineTracer 	lineTracer;
UI 		ui;
ColorJudgement 	colorJudgement;
BalanceRunner 	balanceRunner;
TouchSensor 	touchSensor;
LightSensor 	lightSensor;
GyroSensor 	gyroSensor;
Motor 		leftMotor, rightMotor, tailMotor;
SeeSaw      seeSaw;
Steps		steps;
GarageIn	garageIn;
StepsIKB	stepsIKB;
Basic		basic;
GrayDetector grayDetector;

// デバイス初期化用フック関数
// この関数はnxtOSEK起動時に実行されます。
void ecrobot_device_initialize()
{
	// センサ、モータなどの各デバイスの初期化関数を
	// ここで実装することができます
	// ⇒　光センサ赤色LEDをONにする
	run_time = 0;
	ecrobot_set_light_sensor_active(NXT_PORT_S3);
	if(ecrobot_get_bt_status() == BT_NO_INIT){
		ecrobot_set_bt_device_name("ET025");
	}
	ecrobot_init_bt_slave("LEJOS-OSEK");
}

// デバイス終了用フック関数
// この関数はSTOPまたはEXITボタンが押された時に実行されます。
void ecrobot_device_terminate()
{
	// センサ、モータなどの各デバイスの終了関数を
	// ここで実装することができます。
	// ⇒　光センサ赤色LEDをOFFにする
	ecrobot_set_light_sensor_inactive(NXT_PORT_S3);
	ecrobot_term_bt_connection();
}

// 1msec周期割り込み(ISRカテゴリ2)から起動されるユーザー用フック関数
void user_1ms_isr_type2(void)
{
	// 今回は何も行わない
}

TASK(TaskMain)
{
	ecrobot_device_initialize();
	// オブジェクト間のリンクを構築する
	lineTracer.colorJudgement  = &colorJudgement;
	lineTracer.balanceRunner   = &balanceRunner;
	int i;
	for(i = 0; i < COUNT_SCENARIO; i++)
	{
		//scenarioTracer.scenarios[i]  = &scenarios[i];
	}
	//scenarioTracer.balanceRunner = &balanceRunner;
	lineTracer.lightSensor	     = &lightSensor;
	ui.touchSensor		   = &touchSensor;
	ui.tailMotor		   = &tailMotor;
	colorJudgement.lightSensor = &lightSensor;
	
	balanceRunner.gyroSensor   = &gyroSensor;
	balanceRunner.leftMotor    = &leftMotor;
	balanceRunner.rightMotor   = &rightMotor;
	
	seeSaw.tailMotor		   = &tailMotor;
	seeSaw.balanceRunner	   = &balanceRunner;
	seeSaw.lineTracer		   = &lineTracer;
	seeSaw.rightMotor		   = &rightMotor;
	seeSaw.leftMotor           = &leftMotor;
	seeSaw.gyroSensor          = &gyroSensor;
	
	steps.balanceRunner	   = &balanceRunner;
	steps.lineTracer		   = &lineTracer;
	steps.rightMotor		   = &rightMotor;
	steps.leftMotor           = &leftMotor;
	steps.gyroSensor          = &gyroSensor;

	stepsIKB.balanceRunner	  = &balanceRunner;
	stepsIKB.gyroSensor       = &gyroSensor;
	stepsIKB.lineTracer       = &lineTracer;
	stepsIKB.leftMotor       = &leftMotor;
	stepsIKB.rightMotor       = &rightMotor;

	garageIn.leftMotor		  = &leftMotor;
	garageIn.rightMotor		  = &rightMotor;

	basic.leftMotor			  = &leftMotor;
	basic.rightMotor		  = &rightMotor;
	basic.gyroSensor		  = &gyroSensor;
	basic.lineTracer		  = &lineTracer;
	

	// 各オブジェクトを初期化する
	LineTracer_init(&lineTracer);
	UI_init(&ui);
	ColorJudgement_init(&colorJudgement);
	BalanceRunner_init(&balanceRunner);
	TouchSensor_init(&touchSensor, NXT_PORT_S4);
	LightSensor_init(&lightSensor, NXT_PORT_S3);
	GyroSensor_init(&gyroSensor, NXT_PORT_S1);
	Motor_init(&leftMotor, NXT_PORT_C);
	Motor_init(&rightMotor, NXT_PORT_B);
	Motor_init(&tailMotor, NXT_PORT_A);
	StepsIKB_init(&stepsIKB);
	Steps_init(&steps);
	Basic_init(&basic);
	GrayDetector_init(&grayDetector, NXT_PORT_S3);

	// UIに開始待ちを依頼する
	UI_waitStart(&ui);
	// 4ms周期で、ライントレーサにトレース走行を依頼する
	while(1)
	{		
		//ecrobot_bt_data_logger(0, 0);

		if(gfrag == 0){
			LineTracer_trace(&lineTracer, 120);
		}

		if(gfrag == 2){
			Steps_run(&steps);
		}

		if(gfrag == 1 && stop < 3000){
			LineTracer_trace(&lineTracer, 0);
			stop+=4;
		}else if(gfrag == 1 && stop > 3000){
			gfrag = 2;
		}

		GrayDetector_enqueue(&grayDetector);
		if(GrayDetector_calcAverage(&grayDetector) > 50){
			gfrag = 1;
		}

		/*
		if(run_time > 35000 && run_time <= 38000){
			LineTracer_trace(&lineTracer, 0);	
		}else if(run_time > 38000){
			Steps_run(&steps);
		}
		else{
			Basic_run(&basic);
		}
		*/
		

		if (UI_isEmergency(&ui))
			break;
		
		run_time+=4;
		systick_wait_ms(4);

	gyro = GyroSensor_getAngularVelocity(&gyroSensor);//ジャイロセンサーの値を代入する	
	

	display_clear(0);
	display_goto_xy(0,1);
	display_string("gyro=");
	display_int(gyro,1);
	display_update();
	
	
	}

	Motor_rotate(&leftMotor, 0);
	Motor_rotate(&rightMotor, 0);
	systick_wait_ms(100);

}

