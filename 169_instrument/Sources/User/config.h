#ifndef __config_h
#define __config_h


#include <hidef.h>

#include "derivative.h"
#include "delay.h"
#include "SPI25LC1024.h"
#include "main.h"

#include "gui.h"
#include "ILI9481.h"
#include "systermf.h"
#include "typedef.h"
//#include "pt.h"
//#include "pt-sem.h"

#define OnlineCheckID       0x121//检测节点是否在线
#define ExcuteAppID         0x129//回退到boot

#define FAULT_DEBUG					//测试故障显示
#define TEST_STEPPER				//自检指针


#endif