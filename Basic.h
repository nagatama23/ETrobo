
#if !defined(Basic__INCLUDED_)
#define Basic__INCLUDED_

#include "GyroSensor.h"
#include "LineTracer.h"

typedef struct Basic
{
	Motor *rightMotor;
	Motor *leftMotor;
	GyroSensor *gyroSensor;
	LineTracer *lineTracer;
	int run_time, speed;

	//unsigned int angleR,angleL;

} Basic;

void Basic_init(Basic *this);
void Basic_run(Basic *this);

#endif

