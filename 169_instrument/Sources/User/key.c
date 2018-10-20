#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "config.h"
#include "global.h"
#include "key.h"
#include "main.h"
#include "Show.h"

#define KEY_LONG_PERIOD         125 

// ״̬��
typedef enum
{
    KEY_STATE_INIT = 0,
    KEY_STATE_WOBBLE,
    KEY_STATE_PRESS,
    KEY_STATE_LONG,
    KEY_STATE_RELEASE
}KEY_STATE_e;

static volatile KEY_TYPE_e  key_info;

/******************************************************************************
Note: �����ĸ��ӿ�Ϊ�ϲ��߼��ӿڡ�
KeyPressed : ���¾ͼ��̴���
KeyRelease : �̰����ɿ�����
KeyLongRelease : �������ɿ�����
KeyLongPressed : �����ͻᴥ��

******************************************************************************/
void KeyPressed(KEY_TYPE_e keyType)
{
}

void KeyRelease(KEY_TYPE_e keyType)
{
	
}

void KeyLongRelease(KEY_TYPE_e keyType)
{
	
}


void KeyLongPressed(KEY_TYPE_e keyType)
{	
	
	if ( (0 == MenuPage) && (keyType == BACK_KEY) ) {
		//!<TODO:�����̱�
		DisableInterrupts;
		KmTotalShort = 0;
		KmTotalShortFlag = 1;
		EnableInterrupts;
	}
}

/******************************************************************************
�ײ��߼���������ֲ
******************************************************************************/
static KEY_TYPE_e  KeyScan(void)
{
	KEY_TYPE_e temp;
	temp = NONE_KEY;
	if ( KEY_1 == 0 ) {
		temp |= ENTER_KEY;
	}
	if ( KEY_2 == 0 ) {
		temp |= BACK_KEY;
	}
	if ( KEY_3 == 0 ) {
		temp |= DOWN_KEY;
	}
	if ( KEY_4 == 0 ) {
		temp |= UP_KEY;
	}

	return temp;
}


void DetectKeyEvent()
{
	static KEY_STATE_e s_keyState = 0;
	static KEY_STATE_e s_lastKeyState = 0; //Ŀ�������ֳ������ɿ������Ƕ̰����ɿ�
	static U8 s_keyTimeCnt = 0;
	static KEY_TYPE_e s_lastKey = NONE_KEY;
	static KEY_TYPE_e s_firstKey = NONE_KEY;
	KEY_TYPE_e tempKey = NONE_KEY;

	tempKey = KeyScan(); // ���ڱ���˲ʱ�ļ�ֵ

	switch(s_keyState)
	{
		case KEY_STATE_INIT :
		{
			if ( tempKey != NONE_KEY ) {
				s_firstKey = tempKey;
				s_keyState = KEY_STATE_WOBBLE;
				s_lastKeyState = KEY_STATE_INIT;
			}
		}
		break;

		case KEY_STATE_WOBBLE :
		{
			s_keyState = KEY_STATE_PRESS;
			s_lastKeyState = KEY_STATE_WOBBLE;
		}
		break;

		case KEY_STATE_PRESS :
		{
			if ( tempKey != NONE_KEY && tempKey == s_firstKey ) {
				s_lastKey = tempKey; // �����ֵ�� Ŀ�������ͷŵ�ʱ��õ���ֵ��
				// �а��������ˡ� 
				//KeyPressed(tempKey);
				key_info = tempKey;//!<
				s_keyState = KEY_STATE_LONG;
			}
			else {
				s_keyState = KEY_STATE_INIT;  // ��Ϊ��������
			}
			s_lastKeyState = KEY_STATE_PRESS;
		}
		break;

		case KEY_STATE_LONG : // ���ڳ���״̬��  ���������ǳ�����
		{
			if ( tempKey != NONE_KEY && tempKey == s_firstKey ) { /*�м������ҳ�ֵδ��*/ 
				if ( ++s_keyTimeCnt > KEY_LONG_PERIOD ) {
					s_keyTimeCnt = 0;
					// �������¼����� 
					//KeyLongPressed(tempKey);
					key_info = tempKey | LONG_KEY;
					s_lastKeyState = KEY_STATE_LONG;
				}
			}
			else {
				s_keyTimeCnt = 0;  // ��ֹ��ζ̰����s_keyTimeCnt�ۻ�
				s_keyState = KEY_STATE_RELEASE; // �ǳ����� ���Ѿ��ͷš�
			}
		}
		break;

		case KEY_STATE_RELEASE : 
		{
			if (s_lastKeyState == KEY_STATE_LONG) { // ��ʾ�����������ɿ�
				KeyLongRelease(s_lastKey);
			}
			else { // ��ʾ�����ɿ� 
				KeyRelease(s_lastKey);
			}
			s_keyState = KEY_STATE_INIT;
			s_lastKeyState = KEY_STATE_RELEASE;
		}
		break;
	}
}

KEY_TYPE_e ReadKey(void)
{
	KEY_TYPE_e temp;
	temp = key_info;
	key_info = 0;
	return temp;
}




