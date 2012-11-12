#pragma once

#include "Motor.h"

typedef struct GarageIn
{
	int runtime; //’â~‚·‚é‚Ü‚Å‚Ì‘–sŠÔ
	Motor *leftMotor;
	Motor *rightMotor;
} GarageIn;

// ŒöŠJ‘€ì
void GarageIn_init(GarageIn* this);
void GarageIn_run(GarageIn* this);
