#include "include.h"

const unsigned char * Control_page0[] = {
	page3_linel1,page3_linel2,page3_linel4,page3_linel5,page3_linel6,page3_linel7,page3_linel8,
	page3_linel9,page3_linela,page3_linelb,page3_linelc,page3_lineld,page3_linele,NULL,
};

unsigned char * storage_control[] = {
	para_cat_state1,para_cat_state2,para_cat_state3,			/*启动熄火其他*/
	para_cat_mode1,para_cat_mode2,para_cat_mode3,				/*纯电燃油混动*/
	para_cat_diver1,para_cat_diver2,							/*有无驱动力*/
	para_cat_off,para_cat_on,									/*开关机*/
	para_cat_start_dis,para_cat_start_en,						/*允许禁止启动*/
	para_cat_dc_state1,para_cat_dc_state2,para_cat_dc_state3	/*工作断开异常*/
};


void ShowControl(void)
{
	volatile unsigned char Buff[20];
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
				Battery_Manager_page(submenu_3,Control_page0);
			}
			break;
		case 2:
			
			u16temp = PAGE3_PAGINATION0_1;//车辆状态
			if(u16temp == 0x01){
				u16temp = 0;
			}else if (u16temp == 0x02){
				u16temp = 1;
			}else if(u16temp < 0xFE){
				u16temp = 2;
			}
			ShowSelectStrin(u16temp,storage_control);

			
			u16temp = PAGE3_PAGINATION0_2;
			if(u16temp == 0x01){
				u16temp = 3;
			}else if(u16temp == 0x02){
				u16temp = 5;
			}else if(u16temp < 0XFE){
				u16temp = 4;
			}
			ShowSelectStrin(u16temp,storage_control);
			
			u16temp = PAGE3_PAGINATION0_3;
			if(u16temp == 1){
				u16temp = 7;
			}else
				u16temp =6;
			ShowSelectStrin(u16temp,storage_control);
			ShowDigit_sign(PAGE3_PAGINATION0_4,0,"%");
			ShowDigit_sign(PAGE3_PAGINATION0_5,0,"%");
			ShowDigit(PAGE3_PAGINATION0_6,0);
			ShowHexLong(PAGE3_PAGINATION0_7);
			ShowDigit(PAGE3_PAGINATION0_8,0);


			u16temp = PAGE3_PAGINATION0_9;
			if(u16temp == 0xaa){
				u16temp = 8;
			}else{
				u16temp = 9;
			}
			ShowSelectStrin(u16temp,storage_control);

			u16temp = PAGE3_PAGINATION0_a;
			if(u16temp == 0xaa){
				u16temp = 8;
			}else{
				u16temp = 9;
			}
			ShowSelectStrin(u16temp,storage_control);

			u16temp = PAGE3_PAGINATION0_b;
			if(u16temp == 0xaa){
			    u16temp = 8;
			}else
				u16temp = 9;
			ShowSelectStrin(u16temp,storage_control);

			u16temp = PAGE3_PAGINATION0_c;
			   if(u16temp == 0xaa){
			u16temp = 8;
			}else
				u16temp = 9;
			ShowSelectStrin(u16temp,storage_control);

			u16temp = PAGE3_PAGINATION0_d;
			if(u16temp == 0x01){
				u16temp = 13;
			}else if(u16temp < 0xFE)
				u16temp =14;
			ShowSelectStrin(u16temp,storage_control);
			break;

			}
}



