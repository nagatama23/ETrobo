/****************************************************
 *  ScenarioTracer.h                                         
 *  Created on: 2012/05/05 8:48:56                      
 *  Implementation of the Class ScenarioTracer       
 *  Original author: hiroyuki.watanabe                     
 ****************************************************/

#if !defined(EA_E8CF7052_18D2_4397_8E40_09614166DBBE__INCLUDED_)
#define EA_E8CF7052_18D2_4397_8E40_09614166DBBE__INCLUDED_

#define	MAX_SCENARIO	10

#include "BalanceRunner.h"
#include "Scenario.h"
#include "Motor.h"

// ëÆê´Çï€éùÇ∑ÇÈÇΩÇﬂÇÃç\ë¢ëÃÇÃíËã`
typedef struct ScenarioTracer
{
	int runtime;
	int countScenario;
	int currentScenario;
	BalanceRunner *balanceRunner;
	Scenario *scenarios[MAX_SCENARIO];
} ScenarioTracer;

// åˆäJëÄçÏ
void ScenarioTracer_init(ScenarioTracer* this, int countScenario);
void ScenarioTracer_trace(ScenarioTracer* this);

#endif /*!defined(EA_E8CF7052_18D2_4397_8E40_09614166DBBE__INCLUDED_)*/

