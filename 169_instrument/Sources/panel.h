#ifndef	PANEL_H__
	#define PANEL_H__
	
#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "config.h"
#include "main.h"
#include "global.h"

//!< LED低有效
/**
 * 硬件引脚定义
 * @{
 */

#define LIGHT_14White              PTP_PTP1

#define L_PANEL_LED_1              PT01AD_PT0AD5
#define L_PANEL_LED_1_SHIFT        PORTB_PB7
#define L_PANEL_LED_2              PT01AD_PT0AD6
#define L_PANEL_LED_3              PT01AD_PT1AD7
#define L_PANEL_LED_4              PTS_PTS6
#define L_PANEL_LED_5              PTS_PTS5
#define L_PANEL_LED_6              PTS_PTS4
#define L_PANEL_LED_7              PTM_PTM2

#define R_PANEL_LED_1              PORTB_PB4
#define R_PANEL_LED_2              PTT_PTT2
#define R_PANEL_LED_3              panel_reserved
#define R_PANEL_LED_4              PTT_PTT5
#define R_PANEL_LED_5              PTT_PTT4
#define R_PANEL_LED_6              PORTA_PA6
#define R_PANEL_LED_7              PTT_PTT3
#define R_PANEL_LED_8              PTP_PTP4

#define U_PANEL_LED_1              PORTA_PA5
#define U_PANEL_LED_2              PORTB_PB3
#define U_PANEL_LED_3              PTP_PTP7
#define U_PANEL_LED_4              PORTA_PA7
/**
 * @}
 */  
/**
 * @条件定义
 * @{
 */

#define L_PANEL_IN1()                   (!CHECKBIT(ReadL,B1))
#define L_PANEL_IN1_SHIFT()             (can_signal.ID_1811A6A0.LED8)
#define L_PANEL_IN2()                   (can_signal.ID_041000A0.VCU_Diag_Code3.Bits.bit0)//(!CHECKBIT(ReadH,B1))
#define L_PANEL_IN3()                   (!CHECKBIT(ReadL,B2))
#define L_PANEL_IN4()                   (PTM_PTM3)//(CHECKBIT(ReadH,B3))
#define L_PANEL_IN5()                   (!CHECKBIT(ReadH,B7))
#define L_PANEL_IN6()                   (can_signal.ID_1811A6A0.LED7)
#define L_PANEL_IN7()                   (0)//(can_signal.ID_1811A6A0.LED6)


#define R_PANEL_IN1()                   ((can_signal.ID_1811A6A0.LED2)||(can_signal.ID_1810A6A0.LED.bit.LED3))
#define R_PANEL_IN2()                   ((can_signal.ID_1810A6A0.LED.bit.LED2))
#define R_PANEL_IN3()                   (0)
#define R_PANEL_IN4()                   (0)//?
#define R_PANEL_IN5()                   (can_signal.ID_1811A6A0.LED4)
#define R_PANEL_IN6()                   (can_signal.ID_1811A6A0.LED3)
#define R_PANEL_IN7()                   (0)//(can_signal.ID_041000A0.VCU_Diag_Code3.Bits.bit0)
#define R_PANEL_IN8()                   (0)

#define U_PANEL_IN1()                   (CHECKBIT(ReadH,B6))
#define U_PANEL_IN2()                   (can_signal.ID_1810A6A0.LED.bit.LED1)
#define U_PANEL_IN3()                   (can_signal.ID_1810A6A0.LED.bit.LED5)
#define U_PANEL_IN4()                   (CHECKBIT(ReadH,B0))
/**
 * @}
 */
/**
 * @para LED 待操作LED
 * @para V 条件
 * 条件为真时亮灯
 */
#define Set_Warning_LED(LED,V)		do{(LED) = (V)?1:0;}while(0)

//!<任务循环中调用
extern void SetPanelStatus(void);
extern void PanelInit(void);
void PanelTest(void);
#endif