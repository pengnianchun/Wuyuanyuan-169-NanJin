#include "include.h"
const unsigned char *  auxiliary_page1[] = 
{
	page6_linel1,	//= 电机运行状态;
	page6_linel2,	// = 电机功率;
	page6_linel3,	// = 电机温度;
	page6_linel4,	// = 控制器温度;
	page6_linel5,	// = 母线电压;
	NULL,

};

const unsigned char *  auxiliary_page2[] =
{
	page6_linel11,	// = 电机运行状态;
	page6_linel12,	// = 电机功率;
	page6_linel13,	// = 电机温度;
	page6_linel14,	// = 电机控制器温度;
	page6_linel15,	// = 母线电压;
	page6_linel16,	// = 转速;
	NULL,	

};

const unsigned char * auxiliary_page3[] =
{
	page6_linel21,	
	page6_linel22,	
	page6_linel23,	
	page6_linel24,	
	page6_linel25,
	page6_linel26,
	page6_linel27,
	page6_linel28,
	NULL,

};

const unsigned char *  auxiliary_page4[] =
{
	page6_linel31,	// = 绝缘电阻;
	page6_linel32,	// = 正极绝缘阻值;
	page6_linel33,	// = 负极绝缘阻值;
	page6_linel34,	// = 单元工作状态;
	NULL,

};

const unsigned char * storage_auxiliary[] = {
	page6_linel11,	// = 电机运行状态;
	page6_linel12,	// = 电机功率;
	page6_linel13,	// = 电机温度;
	page6_linel14,	// = 电机控制器温度;
	page6_linel15,	// = 母线电压;
	page6_linel16,	// = 转速;
	NULL,	

};
const unsigned char * st_dcdc_mode[] ={"Standby","Work","Failure","Rerating"};
const unsigned char * st_dcdc_derating[] ={"No Derating","Derating"};

void ShowAir(void)
{
	unsigned char Buff[20];
	unsigned int u16temp;
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
		else if (UP_KEY == key)
		{
			pagination++;
			subsection = 0;
		}
		else if (DOWN_KEY == key)
		{
			pagination--;
			subsection = 0;
		}
	}
	switch(subsection){
		case 0:
			subsection = 1;
			GUI_clearscreen(BLACK);
			break;
		case 1:
			switch(pagination%4)
			{
				case 0:
					subsection = 2;
					Battery_Manager_page(pape6_pagination0,auxiliary_page1);
					LCD_PutString16(120,27 * 17,"1/4",WHITE,BLACK);
					break;
				case 1:
					subsection = 3;
					Battery_Manager_page(pape6_pagination1,auxiliary_page2);
					LCD_PutString16(120,27 * 17,"2/4",WHITE,BLACK);
					break;
				case 2:
					subsection = 4;
					Battery_Manager_page(pape6_pagination2,auxiliary_page3);
					LCD_PutString16(120,27 * 17,"3/4",WHITE,BLACK);
					break;
				case 3:
					subsection = 5;
					Battery_Manager_page(pape6_pagination3,auxiliary_page4);
					LCD_PutString16(120,27 * 17,"4/4",WHITE,BLACK);
					break;
			}
			//Air_page();
			break;
		case 2:
				u16temp = PAGE6_PAGINATION0_1;
				if (u16temp == 0)
				{
					u16temp = LCD_PutString16(180,27 * 2,para_oil_state1,WHITE,BLACK);
					ClearStringLine(u16temp,27 * 2);
				}
				else if (u16temp == 1)
				{
					u16temp = LCD_PutString16(180,27 * 2,para_oil_state2,WHITE,BLACK);
					ClearStringLine(u16temp,27 * 2);
				}
				
				u16temp = PAGE6_PAGINATION0_2;
				if (u16temp >= 200){
					u16temp -= 200;
					sprintf(Buff,"%uKW",u16temp);
				}else{
					u16temp = 200 - PAGE6_PAGINATION0_2;
					sprintf(Buff,"-%uKW",u16temp);
				}
				u16temp = LCD_PutString16(180,27 * 3,Buff,WHITE,BLACK);
				ClearStringLine(u16temp,27 * 3);

				u16temp= PAGE6_PAGINATION0_3;//电机温度
				if (u16temp >= 40){
					u16temp -= 40;
					sprintf(Buff,"%u",u16temp);
					u16temp = LCD_PutString16(180,27 * 4,Buff,WHITE,BLACK);
				}else{
					u16temp = 40 - PAGE6_PAGINATION0_3;
					sprintf(Buff,"-%u",u16temp);
					u16temp = LCD_PutString16(180,27 * 4,Buff,WHITE,BLACK);
				}
				u16temp = LCD_PutString16(u16temp,27 * 4,symbol_temp,WHITE,BLACK);
				ClearStringLine(u16temp,27 * 4);

				u16temp = PAGE6_PAGINATION0_4;
				if (u16temp >= 40){
					u16temp -= 40;
					sprintf(Buff,"%u",u16temp);
					u16temp = LCD_PutString16(180,27 * 5,Buff,WHITE,BLACK);
				}else{
					u16temp = 40 - PAGE6_PAGINATION0_4;
					sprintf(Buff,"-%u",u16temp);
					u16temp = LCD_PutString16(180,27 * 5,Buff,WHITE,BLACK);
				}
				u16temp = LCD_PutString16(u16temp,27 * 5,symbol_temp,WHITE,BLACK);
				ClearStringLine(u16temp,27 * 5);

				u16temp = PAGE6_PAGINATION0_5;
				sprintf(Buff,"%uV",u16temp);
				u16temp = LCD_PutString16(180,27 * 6,Buff,WHITE,BLACK);	
				ClearStringLine(u16temp,27 * 6);
				break;
				
		case 3:
				u16temp = PAGE6_PAGINATION1_1;
				if (u16temp == 0)
				{
					u16temp = LCD_PutString16(150,27 * 2,para_oil_state1,WHITE,BLACK);
					ClearStringLine(u16temp,27 * 2);
				}
				else if (u16temp == 1)
				{
					u16temp = LCD_PutString16(150,27 * 2,para_oil_state2,WHITE,BLACK);
					ClearStringLine(u16temp,27 * 2);
				}
				u16temp = PAGE6_PAGINATION1_2;
				if (u16temp >= 200){
					u16temp -= 200;
					sprintf(Buff,"%uKW",u16temp);
				}else{
					u16temp = 200 - PAGE6_PAGINATION1_2;
					sprintf(Buff,"-%uKW",u16temp);
				}
				u16temp = LCD_PutString16(150,27 * 3,Buff,WHITE,BLACK);
				ClearStringLine(u16temp,27 * 3);

				u16temp = PAGE6_PAGINATION1_3;
				if (u16temp >= 40){
					u16temp -= 40;
					sprintf(Buff,"%u",u16temp);
					u16temp = LCD_PutString16(150,27 * 4,Buff,WHITE,BLACK);
				}else{
					u16temp = 40 - PAGE6_PAGINATION1_3;
					sprintf(Buff,"-%u",u16temp);
					u16temp = LCD_PutString16(150,27 * 4,Buff,WHITE,BLACK);
				}
				u16temp = LCD_PutString16(u16temp,27 * 4,symbol_temp,WHITE,BLACK);
				ClearStringLine(u16temp,27 * 4);

				u16temp = PAGE6_PAGINATION1_4;
				if (u16temp >= 40){
					u16temp -= 40;
					sprintf(Buff,"%u",u16temp);
					u16temp = LCD_PutString16(150,27 * 5,Buff,WHITE,BLACK);
				}else{
					u16temp = 40 - PAGE6_PAGINATION1_4;
					sprintf(Buff,"-%u",u16temp);
					u16temp = LCD_PutString16(150,27 * 5,Buff,WHITE,BLACK);
				}
				u16temp = LCD_PutString16(u16temp,27 * 5,symbol_temp,WHITE,BLACK);
				ClearStringLine(u16temp,27 * 5);

				u16temp = PAGE6_PAGINATION1_5;
				sprintf(Buff,"%uV",u16temp);
				u16temp = LCD_PutString16(150,27 * 6,Buff,WHITE,BLACK);
				ClearStringLine(u16temp,27 * 6);

				u16temp = PAGE6_PAGINATION1_6;
				sprintf(Buff,"%urpm/min",u16temp/8);
				u16temp = LCD_PutString16(150,27 * 7,Buff,WHITE,BLACK);	
				ClearStringLine(u16temp,27 * 7);
				break;
		case 4:
				u16temp = PAGE6_PAGINATION2_1;
				if (u16temp == 0)
				{
					u16temp = LCD_PutString16(180,27 * 2,para_dcdc_state1,WHITE,BLACK);
					ClearStringLine(u16temp,27 * 2);
				}
				else if (u16temp == 1)
				{
					u16temp = LCD_PutString16(180,27 * 2,para_dcdc_state2,WHITE,BLACK);
					ClearStringLine(u16temp,27 * 2);
				}
				
				u16temp = PAGE6_PAGINATION2_2; //工作温温度
				u16temp = LCD_PutString16(180,27 * 3,st_dcdc_mode[u16temp],WHITE,BLACK);
				ClearStringLine(u16temp,27 * 3);
				
				u16temp = PAGE6_PAGINATION2_3;
				u16temp = LCD_PutString16(180,27 * 4,st_dcdc_derating[u16temp],WHITE,BLACK);
				ClearStringLine(u16temp,27 * 4);

				u16temp = PAGE6_PAGINATION2_4;
				sprintf(Buff,"%uA",u16temp);
				u16temp = LCD_PutString16(180,27 * 5,Buff,WHITE,BLACK);
				ClearStringLine(u16temp,27 * 5);

				u16temp = PAGE6_PAGINATION2_5;
				if(u16temp>= 40){
				u16temp -= 40;
				sprintf(Buff,"%u",u16temp);
				u16temp = LCD_PutString16(180,27 * 6,Buff,WHITE,BLACK);
				}else{
				u16temp = 40 - u16temp;
				sprintf(Buff,"-%u",u16temp);
				u16temp = LCD_PutString16(180,27 * 6,Buff,WHITE,BLACK);
				}
				u16temp = LCD_PutString16(u16temp,27 * 6,symbol_temp,WHITE,BLACK);
				ClearStringLine(u16temp,27 * 6);

				u16temp = PAGE6_PAGINATION2_6;
				sprintf(Buff,"%uV",u16temp);
				u16temp = LCD_PutString16(180,27 * 7,Buff,WHITE,BLACK);
				ClearStringLine(u16temp,27 * 7);

				u16temp = PAGE6_PAGINATION2_7;
				sprintf(Buff,"%uV",u16temp*3);
				u16temp = LCD_PutString16(180,27 * 8,Buff,WHITE,BLACK);
				ClearStringLine(u16temp,27 * 8);

				u16temp = PAGE6_PAGINATION2_8;
				sprintf(Buff,"%u",u16temp);
				u16temp = LCD_PutString16(180,27 * 9,Buff,WHITE,BLACK);
				ClearStringLine(u16temp,27 * 9);
				break;
		case 5:
			u16temp = PAGE6_PAGINATION3_1;
			sprintf(Buff,"%u",u16temp);
			u16temp = LCD_PutString16(180,27 * 2,Buff,WHITE,BLACK);
			u16temp = LCD_PutString16(u16temp,27 * 2,symbol_temp2,WHITE,BLACK);
			ClearStringLine(u16temp,27 * 2);

			u16temp = PAGE6_PAGINATION3_2;
			sprintf(Buff,"%u",u16temp);
			u16temp = LCD_PutString16(180,27 * 3,Buff,WHITE,BLACK);
			u16temp = LCD_PutString16(u16temp,27 * 3,symbol_temp2,WHITE,BLACK);
			ClearStringLine(u16temp,27 * 3);
			
			u16temp = PAGE6_PAGINATION3_3;
			sprintf(Buff,"%u",u16temp);
			u16temp = LCD_PutString16(180,27 * 4,Buff,WHITE,BLACK);
			u16temp = LCD_PutString16(u16temp,27 * 4,symbol_temp2,WHITE,BLACK);
			ClearStringLine(u16temp,27 * 4);

			u16temp = PAGE6_PAGINATION3_4;
			if(u16temp == 0)
			{
				u16temp = LCD_PutString16(180,27 * 5,para_bms1,WHITE,BLACK);
				ClearStringLine(u16temp,27 * 5);
			}
			else if(u16temp == 1)
			{
				u16temp = LCD_PutString16(180,27 * 5,para_bms2,WHITE,BLACK);
				ClearStringLine(u16temp,27 * 5);
			}
			else if(u16temp == 2)
			{
				u16temp = LCD_PutString16(180,27 * 5,para_fault,WHITE,BLACK);
				ClearStringLine(u16temp,27 * 5);
			}
			else if(u16temp == 3)
			{
				u16temp = LCD_PutString16(180,27 * 5,para_fault_23,WHITE,BLACK);
				ClearStringLine(u16temp,27 * 5);
			}
				break;
		default:
			break;
	}
}

