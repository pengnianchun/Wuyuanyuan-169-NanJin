#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "config.h"
#include "global.h"
#include "key.h"
#include "main.h"
#include "Show.h"

#define KEY_LONG_PERIOD         125 

// 状态机
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
Note: 以下四个接口为上层逻辑接口。
KeyPressed : 按下就即刻触发
KeyRelease : 短按后松开触发
KeyLongRelease : 长按后松开触发
KeyLongPressed : 长按就会触发

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
		//!<TODO:清除里程表
		DisableInterrupts;
		KmTotalShort = 0;
		KmTotalShortFlag = 1;
		EnableInterrupts;
	}
}

/******************************************************************************
底层逻辑，方便移植
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
	static KEY_STATE_e s_lastKeyState = 0; //目的是区分长按后松开或者是短按是松开
	static U8 s_keyTimeCnt = 0;
	static KEY_TYPE_e s_lastKey = NONE_KEY;
	static KEY_TYPE_e s_firstKey = NONE_KEY;
	KEY_TYPE_e tempKey = NONE_KEY;

	tempKey = KeyScan(); // 用于保存瞬时的键值

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
				s_lastKey = tempKey; // 保存键值， 目的是在释放的时候得到键值。
				// 有按键按下了。 
				//KeyPressed(tempKey);
				key_info = tempKey;//!<
				s_keyState = KEY_STATE_LONG;
			}
			else {
				s_keyState = KEY_STATE_INIT;  // 认为发生抖动
			}
			s_lastKeyState = KEY_STATE_PRESS;
		}
		break;

		case KEY_STATE_LONG : // 处于长按状态，  但不代表是长按。
		{
			if ( tempKey != NONE_KEY && tempKey == s_firstKey ) { /*有键按下且初值未变*/ 
				if ( ++s_keyTimeCnt > KEY_LONG_PERIOD ) {
					s_keyTimeCnt = 0;
					// 长按键事件发生 
					//KeyLongPressed(tempKey);
					key_info = tempKey | LONG_KEY;
					s_lastKeyState = KEY_STATE_LONG;
				}
			}
			else {
				s_keyTimeCnt = 0;  // 防止多次短按造成s_keyTimeCnt累积
				s_keyState = KEY_STATE_RELEASE; // 非长按， 建已经释放。
			}
		}
		break;

		case KEY_STATE_RELEASE : 
		{
			if (s_lastKeyState == KEY_STATE_LONG) { // 表示按键长按后松开
				KeyLongRelease(s_lastKey);
			}
			else { // 表示按键松开 
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




