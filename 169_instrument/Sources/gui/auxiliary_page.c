#include "include.h"



unsigned char * Motor_control_page4[] = {
	page4_linel1,	// 驱动电机序号;
	page4_linel2, 	// 驱动电机状态;
	page4_linel3,	// 驱动电机温度;
	page4_linel4, 	//控制器温度;
	page4_linel5,	// 控制器输入电压;
	page4_linel6, 	//控制器直流母线电流;
	page4_linel7,	// 驱动电机转速;
	page4_linel8,	// 驱动电机转矩;
	page4_linel9,	//驱动电机故障总数N2;
	page4_linela,	// 自定义故障代码;
	NULL,
};

unsigned char * storage_motor[] = {
	NULL,
	para_div_state1,		// 耗电;
	para_div_state2,		// 发电;
	para_div_state3,		// 关闭;
	para_div_state4,		// 准备;
	para_div_state5,		// 异常;

};

void ShowAuxiliary(void)
{
	const unsigned char Buff[20];
	 unsigned int u16temp,y;
	 y = TEXTBOX_Y_COORDINATE;
	memset(Buff,0,sizeof(Buff));
    {
		KEY_TYPE_e key;
		key = ReadKey();
		if (NONE_KEY == key)
		{
		}
		else if (BACK_KEY == key)
		{
			SetShowMenuPage(SWITCH_PAGINATION);
		}
	}
	switch(subsection){
		case 0:
			subsection = 1;
			GUI_clearscreen(BLACK);
			break;
		case 1:
			{
				subsection = 2;
				Battery_Manager_page(submenu_4,Motor_control_page4);
			}
			break;

		case 2:
			{
		    ShowDigit(PAGE4_PAGINATION0_1,0);
			
			u16temp = PAGE4_PAGINATION0_2;		//驱动电机状态
		   if (u16temp <= 0x05)
		   {
				ShowSelectStrin(u16temp,storage_motor);
		   }
		   else
		   {
			   ShowNull();

		   }
			ShowDigit_sign(PAGE4_PAGINATION0_3,40,symbol_temp);
			ShowDigit_sign(PAGE4_PAGINATION0_4,40,symbol_temp);
			ShowFlot_sign(PAGE4_PAGINATION0_5,0,10,"V");
			ShowFlot_sign(PAGE4_PAGINATION0_6,1000,10,"A");
			ShowDigit_sign(PAGE4_PAGINATION0_7,2000,"r/min");
			ShowDigit_sign(PAGE4_PAGINATION0_8,2000,"N.M");
			ShowDigit(PAGE4_PAGINATION0_9,0);
			ShowHexLong(PAGE4_PAGINATION0_a);
		}
	}	
}

