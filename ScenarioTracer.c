/****************************************************
 *  ScenarioTracer.c                                         
 *  Created on: 2012/05/05 8:48:56                      
 *  Implementation of the Class ScenarioTracer       
 *  Original author: hiroyuki.watanabe                     
 ****************************************************/

#include "ScenarioTracer.h"
#include "Motor.h"
#define	TASK_CYCLE	4	// タスクの周期（msec）

// 非公開操作
static void ScenarioTracer_updateScenario(ScenarioTracer* this);


void ScenarioTracer_init(ScenarioTracer* this, int countScenario)
{
	this->countScenario = countScenario;	// シナリオ数
	this->currentScenario = 0;		// 現在のシナリオ位置リセット
	this->runtime = 0;			// 走行時間をリセット
}

void ScenarioTracer_trace(ScenarioTracer* this)
{
	if(this->runtime
	     >= this->scenarios[this->currentScenario]->time)
	{
		// シナリオで指定された走行時間が経過したら、
		// シナリオを更新し、走行時間をリセットする
		ScenarioTracer_updateScenario(this);
		this->runtime = 0;
	}
	
	// 現在のシナリオに書かれている方向で、
	// 倒立走行に走行を依頼する

	BalanceRunner_run(
		this->balanceRunner, 
		this->scenarios[this->currentScenario]->forward, 
		this->scenarios[this->currentScenario]->direction);
	
	this->runtime += TASK_CYCLE;	// 走行時間を加算する
	}


static void ScenarioTracer_updateScenario(ScenarioTracer* this)
{
	if(this->currentScenario < this->countScenario)
	{
		// 次のシナリオあり
		// ⇒次のシナリオを現在のシナリオにする
		this->currentScenario++;
	}
	else
	{
		// 次のシナリオなし
		// ⇒　先頭のシナリオを現在のシナリオにする
		this->currentScenario = 0;
	}
} 




