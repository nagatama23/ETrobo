/****************************************************
 *  UI.h                                         
 *  Created on: 2012/05/05 8:28:46                      
 *  Implementation of the Class UI       
 *  Original author: hiroyuki.watanabe                     
 ****************************************************/

#if !defined(EA_FB3DF40C_CBF0_454a_9BA8_39674A045269__INCLUDED_)
#define EA_FB3DF40C_CBF0_454a_9BA8_39674A045269__INCLUDED_

#include "TouchSensor.h"
#include "Motor.h"

#define TAIL_ANGLE_STAND_UP 110 /* 完全停止時の角度[度] */
#define TAIL_ANGLE_DRIVE      3 /* バランス走行時の角度[度] */
#define CMD_START            '1'/* リモートスタートコマンド(変更禁止) */

// 属性を保持するための構造体の定義
typedef struct UI
{
	TouchSensor *touchSensor;
	Motor		*tailMotor;
    char rx_buf[BT_MAX_RX_BUF_SIZE];
} UI;

// 公開操作
void UI_init(UI* this);
void UI_waitStart(UI* this);
int UI_isEmergency(UI *this);

#endif /*!defined(EA_FB3DF40C_CBF0_454a_9BA8_39674A045269__INCLUDED_)*/

