/****************************************************
 *  UI.c                                         
 *  Created on: 2012/05/05 8:28:46                      
 *  Implementation of the Class UI       
 *  Original author: hiroyuki.watanabe                     
 ****************************************************/

#include "UI.h"

static int UI_remoteStart(UI* this);

void UI_init(UI* this)
{
	// 何もしない
}

void UI_waitStart(UI* this)
{
	// タッチセンサが押されるまで、待ち続ける
	while(1)
	{
		// 尻尾を立てて完全停止状態にする
		Motor_tailControl(this->tailMotor, TAIL_ANGLE_STAND_UP);
		if(TouchSensor_isPressed(this->touchSensor))
		{
			// タッチセンサが押されたら尻尾を上げる
			Motor_tailControl(this->tailMotor, TAIL_ANGLE_DRIVE);
			break;		// タッチセンサが押された
		}
		if(UI_remoteStart(this))
		{
			// タッチセンサが押されたら尻尾を上げる
			Motor_tailControl(this->tailMotor, TAIL_ANGLE_DRIVE);
			break;		// タッチセンサが押された
		}

	}
} 

static int UI_remoteStart(UI* this)
{
	int i;
	unsigned int rx_len;
	unsigned char start = 0;

	for (i=0; i<BT_MAX_RX_BUF_SIZE; i++)
	{
		this->rx_buf[i] = 0; /* 受信バッファをクリア */
	}

	rx_len = ecrobot_read_bt(this->rx_buf, 0, BT_MAX_RX_BUF_SIZE);
	if (rx_len > 0)
	{
		/* 受信データあり */
		if (this->rx_buf[0] == CMD_START)
		{
			start = 1; /* 走行開始 */
		}
		ecrobot_send_bt(this->rx_buf, 0, rx_len); /* 受信データをエコーバック */
	}

	return start;
}

int UI_isEmergency(UI *this)
{
	if (ecrobot_get_gyro_sensor(NXT_PORT_S1) < 400)
		return 1;
	else
		return 0;
}
