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
	// �������Ȃ�
}

void UI_waitStart(UI* this)
{
	// �^�b�`�Z���T���������܂ŁA�҂�������
	while(1)
	{
		// �K���𗧂ĂĊ��S��~��Ԃɂ���
		Motor_tailControl(this->tailMotor, TAIL_ANGLE_STAND_UP);
		if(TouchSensor_isPressed(this->touchSensor))
		{
			// �^�b�`�Z���T�������ꂽ��K�����グ��
			Motor_tailControl(this->tailMotor, TAIL_ANGLE_DRIVE);
			break;		// �^�b�`�Z���T�������ꂽ
		}
		if(UI_remoteStart(this))
		{
			// �^�b�`�Z���T�������ꂽ��K�����グ��
			Motor_tailControl(this->tailMotor, TAIL_ANGLE_DRIVE);
			break;		// �^�b�`�Z���T�������ꂽ
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
		this->rx_buf[i] = 0; /* ��M�o�b�t�@���N���A */
	}

	rx_len = ecrobot_read_bt(this->rx_buf, 0, BT_MAX_RX_BUF_SIZE);
	if (rx_len > 0)
	{
		/* ��M�f�[�^���� */
		if (this->rx_buf[0] == CMD_START)
		{
			start = 1; /* ���s�J�n */
		}
		ecrobot_send_bt(this->rx_buf, 0, rx_len); /* ��M�f�[�^���G�R�[�o�b�N */
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
