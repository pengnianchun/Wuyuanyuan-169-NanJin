#ifndef KEY_H__
	#define KEY_H__


/**
 * ����˵��
:
 * K1:����˵�
 * K2:�˳�/�������泤�����С�����
 * K3:����
 * K4:����
 */
typedef unsigned char KEY_TYPE_e;

#define ENTER_KEY			(0X01)
#define BACK_KEY			(0X02)
#define DOWN_KEY			(0x04)
#define UP_KEY				(0x08)
#define LONG_KEY			(0x10)

#define NONE_KEY			(0x00)



void DetectKeyEvent();
KEY_TYPE_e ReadKey(void);
#endif