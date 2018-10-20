
#include "include.h"
void PanelInit(void)
{
	LIGHT_14White = 0;
	
	L_PANEL_LED_1 = 0;
	L_PANEL_LED_1_SHIFT = 0;
	L_PANEL_LED_2 = 0;
	L_PANEL_LED_3 = 0;
	L_PANEL_LED_4 = 0;
	L_PANEL_LED_5 = 0;
	L_PANEL_LED_6 = 0;
	L_PANEL_LED_7 = 0;

	R_PANEL_LED_1 = 0;
	R_PANEL_LED_2 = 0;
	R_PANEL_LED_3 = 0;
	R_PANEL_LED_4 = 0;
	R_PANEL_LED_5 = 0;
	R_PANEL_LED_6 = 0;
	R_PANEL_LED_7 = 0;
	R_PANEL_LED_8 = 0;

	U_PANEL_LED_1 = 0;
	U_PANEL_LED_2 = 0;
	U_PANEL_LED_3 = 0;
	U_PANEL_LED_4 = 0;
	
}
void PanelTest(void)
{
	L_PANEL_LED_4 = 1;
	L_PANEL_LED_6 = 1;
	L_PANEL_LED_7 = 1;

	R_PANEL_LED_1 = 1;
	R_PANEL_LED_2 = 1;
	R_PANEL_LED_5 = 1;
	R_PANEL_LED_6 = 1;
	R_PANEL_LED_7 = 1;
	R_PANEL_LED_8 = 1;

	U_PANEL_LED_2 = 1;
	U_PANEL_LED_3 = 1;

}
void SetPanelStatus(void)
{		
	if (J1_1 == 0)
	{
		Set_Warning_LED(R_PANEL_LED_2,R_PANEL_IN2());
		if (U_PANEL_IN2() == 3)
    	{
    		U_PANEL_LED_2 = 1;
    	}
    	else if (U_PANEL_IN2() == 0)
    	{
    		U_PANEL_LED_2 = 0;
    	}
    	else if (U_PANEL_IN2() == 0x02)
    	{
    		if (panel_pulsation)
    		{
    			U_PANEL_LED_2 = 1;
    		}
    		else
    		{
    			U_PANEL_LED_2 = 0;
    		}
    	}
        return;
	}
	if (PanelUpdateFlag == 0){
		return;
	}
	if (start_lock == 1)
	{
		return;
	}

	PanelUpdateFlag = 0;

	LIGHT_14White = 1;
	//左仪表盘LED
	if (L_PANEL_IN1_SHIFT())
	{
		L_PANEL_LED_1_SHIFT = 1;
		L_PANEL_LED_1 = 0;
	}
	else if(L_PANEL_IN1())
	{
		L_PANEL_LED_1_SHIFT = 0;
		L_PANEL_LED_1 = 1;
	}
	else
	{
		L_PANEL_LED_1_SHIFT = 0;
		L_PANEL_LED_1 = 0;
	}
	Set_Warning_LED(L_PANEL_LED_2,L_PANEL_IN2());
	Set_Warning_LED(L_PANEL_LED_3,L_PANEL_IN3());
	g_safety_belt = L_PANEL_IN3();
	Set_Warning_LED(L_PANEL_LED_4,L_PANEL_IN4());
	Set_Warning_LED(L_PANEL_LED_5,L_PANEL_IN5());
	Set_Warning_LED(L_PANEL_LED_6,L_PANEL_IN6());
	Set_Warning_LED(L_PANEL_LED_7,L_PANEL_IN7());
	//右仪表盘LED
	Set_Warning_LED(R_PANEL_LED_1,R_PANEL_IN1());
	Set_Warning_LED(R_PANEL_LED_2,R_PANEL_IN2());
	Set_Warning_LED(R_PANEL_LED_3,R_PANEL_IN3());
	Set_Warning_LED(R_PANEL_LED_4,R_PANEL_IN4());
	Set_Warning_LED(R_PANEL_LED_5,R_PANEL_IN5());
	Set_Warning_LED(R_PANEL_LED_6,R_PANEL_IN6());
	Set_Warning_LED(R_PANEL_LED_7,R_PANEL_IN7());
	Set_Warning_LED(R_PANEL_LED_8,R_PANEL_IN8());
	//上部分LED
	Set_Warning_LED(U_PANEL_LED_1,U_PANEL_IN1());
	if (U_PANEL_IN2() == 3)
	{
		U_PANEL_LED_2 = 1;
	}
	else if (U_PANEL_IN2() == 0)
	{
		U_PANEL_LED_2 = 0;
	}
	else if (U_PANEL_IN2() == 0x02)
	{
		if (panel_pulsation)
		{
			U_PANEL_LED_2 = 1;
		}
		else
		{
			U_PANEL_LED_2 = 0;
		}
	}
	Set_Warning_LED(U_PANEL_LED_3,U_PANEL_IN3());
	Set_Warning_LED(U_PANEL_LED_4,U_PANEL_IN4());	
}

void AlarmBeep()
{
	U8 temp;
	temp = can_signal.ID_1810A6A0.LED.byte;
	if (temp&0x80)
	{
		alarm_msg = 1;
	}
	else
	{
		alarm_msg = 0;
	}	
}
