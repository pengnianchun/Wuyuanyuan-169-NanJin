#include "include.h"


unsigned char * page0[] = {
	page1_line1,page1_line2,page1_line3,page1_line4,page1_line5,page1_line6,page1_line7,page1_line8,
	page1_line9,page1_linea,page1_lineb,page1_linec,page1_lined,page1_linee,page1_linef,NULL,
};
unsigned char * page1[] = {
	page1_line11,page1_line12,page1_line13,page1_line14,page1_line15,page1_line16,page1_line17,page1_line18,
	page1_line19,page1_line1a,page1_line1b,page1_line1c,page1_line1d,page1_line1e,page1_line1f,NULL,
};
unsigned char * page2[] = {
	page1_line21,page1_line22,NULL,
};

unsigned char * storage[] = {para_storage_type9,para_storage_type1,para_storage_type2,para_storage_type3,para_storage_type4,para_storage_type5,
	para_storage_type6,para_storage_type7,para_storage_type8,para_storage_type9};

unsigned char * para_bms[] = {para_bms1,para_bms2,para_bms3,para_bms4,};

void Battery_Manager_page(unsigned char * name,unsigned char **line)
{
	int l;
	l = strlen(name)/2;
	l = 272 - l*16;
	l /= 2;
	LCD_PutString16(l,27,name,GREEN,BLACK);
	for(l = 0;line[l] != NULL;l++)
	{
		LCD_PutString16(10,LINE_PACKING * (l+2),line[l],WHITE,BLACK);	
	}
}
/**
 * @ DigitToString_flot
 * @ para: dest[out] 输出字符串
 * @ para: data :转化数字
 * @ para: idx :偏移
 * @ para: precision :精度
 * @例:
     DigitToString_flot(buffer,1000,2000,1000);
     结果:buffer = "-1.0";
 */
void DigitToString_flot(unsigned char *dest,unsigned int data,int idx,unsigned int precision)
{
	if (0 == precision)
	{
		precision = 1;
	}
	idx = precision * idx;
	if (idx>data)
	{
		data = idx - data;
		sprintf(dest,"-%u.%u",data/precision,data%precision);
	}
	else
	{
		data = data - idx;
		sprintf(dest,"%u.%u",data/precision,data%precision);
	}
}
/**
 * @ DigitToString_int
 * @ para: dest[out] 输出字符串
 * @ para: data :转化数字
 * @ para: idx :偏移
 */

void DigitToString_int(unsigned char *dest,unsigned int data,int idx)
{
	if (idx>data)
	{
		data = idx - data;
		sprintf(dest,"-%u",data);
	}
	else
	{
		data = data - idx;
		sprintf(dest,"%u",data);
	}
}



void ShowBatteryManager(void)
{
	unsigned char Buff[20];
	unsigned int u16temp;
	unsigned int y;
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
			u16temp = pagination % 3;
			if (u16temp == 2)
			{
				subsection = 4;
				Battery_Manager_page(submenu_1,page2);
				LCD_PutString16(120,27 * 17,"3/3",WHITE,BLACK);
			}
			else if (u16temp == 1)
			{
				subsection = 3;
				Battery_Manager_page(submenu_1,page1);
				LCD_PutString16(120,27 * 17,"2/3",WHITE,BLACK);
			}
			else
			{
				subsection = 2;
				Battery_Manager_page(submenu_1,page0);
				LCD_PutString16(120,27 * 17,"1/3",WHITE,BLACK);
			}
			break;
		case 2:
			
			ShowFlot_sign(PAGE1_PAGINATION0_1,0,10,"V");
			ShowFlot_sign(PAGE1_PAGINATION0_2,1000,10,"A");
			ShowDigit_sign(PAGE1_PAGINATION0_3,0,"%");
			ShowFlot_sign(PAGE1_PAGINATION0_4,0,10,"V");
				
			u16temp = PAGE1_PAGINATION0_5;
			if (u16temp == 0xFC)
			{
				u16temp = 8;

			}
			else if (u16temp >0x07)
			{
				u16temp = 9;
			}
			ShowSelectStrin(u16temp,storage);
			ShowDigit(PAGE1_PAGINATION0_6,0);
			ShowDigit(PAGE1_PAGINATION0_7,0);
			ShowFlot_sign(PAGE1_PAGINATION0_8,0,1000,"V");
			ShowDigit_sign(PAGE1_PAGINATION0_9,40,symbol_temp);
			ShowDigit_sign(PAGE1_PAGINATION0_a,40,symbol_temp);
			ShowDigit_sign(PAGE1_PAGINATION0_b,0,symbol_temp);
			ShowDigit_sign(PAGE1_PAGINATION0_c,0,symbol_temp);
			ShowDigit_sign(PAGE1_PAGINATION0_d,0,symbol_temp);
			ShowFlot_sign(PAGE1_PAGINATION0_e,0,1000,"V");
			ShowFlot_sign(PAGE1_PAGINATION0_f,0,1000,"V");
			break;
		case 3:
			ShowDigit(PAGE1_PAGINATION1_1,0);
			ShowDigit(PAGE1_PAGINATION1_2,0);
			ShowHexLong(PAGE1_PAGINATION1_3);
			ShowFlot_sign(PAGE1_PAGINATION1_4,0,10,"V");
			ShowFlot_sign(PAGE1_PAGINATION1_5,0,10,"A");


			u16temp = PAGE1_PAGINATION1_6;
			if (u16temp == 1)
			{
				u16temp = LCD_PutString16(TEXTBOX_X_COORDINATE,y,para_charge,WHITE,BLACK);
				ClearStringLine(u16temp,27 * 7);
			}
			if (u16temp == 2)
			{
				u16temp = LCD_PutString16(TEXTBOX_X_COORDINATE,y,para_stop,WHITE,BLACK);
				ClearStringLine(u16temp,27 * 7);
			}
			y += LINE_PACKING;
			ShowDigit(PAGE1_PAGINATION1_7,0);
			ShowFlot_sign(PAGE1_PAGINATION1_8,0,1000,"V");
			ShowFlot_sign(PAGE1_PAGINATION1_9,0,1000,"V");
			ShowFlot_sign(PAGE1_PAGINATION1_a,0,1000,"V");
			ShowFlot_sign(PAGE1_PAGINATION1_b,0,1000,"V");
			ShowFlot_sign(PAGE1_PAGINATION1_c,0,10,"A");
			ShowFlot_sign(PAGE1_PAGINATION1_d,0,10,"A");
			ShowDigit_sign(PAGE1_PAGINATION0_e,0,"Ah");
			
			u16temp = PAGE1_PAGINATION1_f;
			if (u16temp<=3){
				ShowSelectStrin(u16temp,para_bms);
			}
			break;
		case 4:
			u16temp = PAGE1_PAGINATION2_1;
			if(u16temp == 0)
			{
				u16temp = LCD_PutString16(180,27 * 2,para_off,WHITE,BLACK);
			}
			else
			{
				u16temp = LCD_PutString16(180,27 * 2,para_on,WHITE,BLACK);
			}
			ClearStringLine(u16temp,27 * 2);

			u16temp = PAGE1_PAGINATION2_2;
			if(u16temp == 0)
			{
				u16temp = LCD_PutString16(180,27 * 3,para_off,WHITE,BLACK);
			}
			else
			{
				u16temp = LCD_PutString16(180,27 * 3,para_on,WHITE,BLACK);
			}
			ClearStringLine(u16temp,27 * 3);
			break;

		default:
			subsection = 2;
			break;
	}
}

