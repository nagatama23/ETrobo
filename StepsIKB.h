#if !defined(StepsIKB__INCLUDED_)
#define StepsIKB__INCLUDED_

#include "BalanceRunner.h"
#include "Motor.h"
#include "GyroSensor.h"
#include "LineTracer.h"

typedef struct StepsIKB
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
} StepsIKB;

void StepsIKB_init(StepsIKB *this);
void StepsIKB_run(StepsIKB *this);
int StepsIKB_GetAVE(StepsIKB *this);

#endif /*!defined(EA_0311591B_68F8_4d9d_A572_FDE0A82543E8__INCLUDED_)*/
