/****************************************************
 *  LightSensor.c                                         
 *  Created on: 2012/05/05 8:28:55                      
 *  Implementation of the Class LightSensor       
 *  Original author: hiroyuki.watanabe                     
 ****************************************************/

#include "LightSensor.h"


void LightSensor_init(LightSensor* this, SENSOR_PORT_T inputPort)
{
	this->inputPort = inputPort;
	
}

// ‹P“x‚ð“¾‚é
unsigned int LightSensor_getBrightness(LightSensor* this)
{
	return ecrobot_get_light_sensor(this->inputPort);
} 

