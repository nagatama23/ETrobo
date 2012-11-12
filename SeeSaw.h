#if !defined(SeeSae__INCLUDED_)
#define SeeSaw__INCLUDED_

#include "BalanceRunner.h"
#include "Motor.h"
#include "GyroSensor.h"
#include "LineTracer.h"
//#include "ScenarioTracer.h"

typedef struct SeeSaw
{
	Motor *tailMotor;
	Motor *rightMotor;
	Motor *leftMotor;
	BalanceRunner *balanceRunner;
	GyroSensor *gyroSensor;
	LineTracer *lineTracer;
	int step;
	int run_time;
} SeeSaw;

void SeeSaw_init(SeeSaw *this);
void SeeSaw_run(SeeSaw* this);


#endif /*!defined(EA_0311591B_68F8_4d9d_A572_FDE0A82543E8__INCLUDED_)*/
