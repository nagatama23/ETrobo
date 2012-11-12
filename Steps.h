#if !defined(Steps__INCLUDED_)
#define Steps__INCLUDED_

#include "BalanceRunner.h"
#include "Motor.h"
#include "GyroSensor.h"
#include "LineTracer.h"
//#include "ScenarioTracer.h"

typedef struct Steps
{
	Motor *rightMotor;
	Motor *leftMotor;
	BalanceRunner *balanceRunner;
	GyroSensor *gyroSensor;
	LineTracer *lineTracer;
	int time;
	int sum;
	int i;
	int j;
	int step;
	int phase;
	int gyro_ave[125];
	int run_time;
} Steps;

void Steps_init(Steps *this);
void Steps_run(Steps *this);
int Steps_GetAVE(Steps *this);


#endif /*!defined(EA_0311591B_68F8_4d9d_A572_FDE0A82543E8__INCLUDED_)*/
