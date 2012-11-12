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


// �I�u�W�F�N�g��ÓI�Ɋm�ۂ���
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

// �f�o�C�X�������p�t�b�N�֐�
// ���̊֐���nxtOSEK�N�����Ɏ��s����܂��B
void ecrobot_device_initialize()
{
	// �Z���T�A���[�^�Ȃǂ̊e�f�o�C�X�̏������֐���
	// �����Ŏ������邱�Ƃ��ł��܂�
	// �ˁ@���Z���T�ԐFLED��ON�ɂ���
	run_time = 0;
	ecrobot_set_light_sensor_active(NXT_PORT_S3);
	if(ecrobot_get_bt_status() == BT_NO_INIT){
		ecrobot_set_bt_device_name("ET025");
	}
	ecrobot_init_bt_slave("LEJOS-OSEK");
}

// �f�o�C�X�I���p�t�b�N�֐�
// ���̊֐���STOP�܂���EXIT�{�^���������ꂽ���Ɏ��s����܂��B
void ecrobot_device_terminate()
{
	// �Z���T�A���[�^�Ȃǂ̊e�f�o�C�X�̏I���֐���
	// �����Ŏ������邱�Ƃ��ł��܂��B
	// �ˁ@���Z���T�ԐFLED��OFF�ɂ���
	ecrobot_set_light_sensor_inactive(NXT_PORT_S3);
	ecrobot_term_bt_connection();
}

// 1msec�������荞��(ISR�J�e�S��2)����N������郆�[�U�[�p�t�b�N�֐�
void user_1ms_isr_type2(void)
{
	// ����͉����s��Ȃ�
}

TASK(TaskMain)
{
	ecrobot_device_initialize();
	// �I�u�W�F�N�g�Ԃ̃����N���\�z����
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
	

	// �e�I�u�W�F�N�g������������
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

	// UI�ɊJ�n�҂����˗�����
	UI_waitStart(&ui);
	// 4ms�����ŁA���C���g���[�T�Ƀg���[�X���s���˗�����
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

	gyro = GyroSensor_getAngularVelocity(&gyroSensor);//�W���C���Z���T�[�̒l��������	
	

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

