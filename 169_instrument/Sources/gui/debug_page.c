#include "include.h"


void ShowDebugPage(void)
{
	unsigned int u16temp;
	
	{
		KEY_TYPE_e key;
		key = ReadKey();
		if (NONE_KEY == key)
		{
		}
		else if (BACK_KEY == key)
		{
			SetShowMenuPage(MAIN_PAGINATION);
			
		}
	}
	switch(subsection){
		case 0:
			subsection = 1;
			GUI_clearscreen(BLACK);
			break;
		case 1:
			u16temp = LCD_PutString16((272-7*8)/2,100,"VERSION",WHITE,BLACK);
			u16temp = strlen(VERSION) * 8;
			u16temp = 272 - u16temp;
			u16temp = u16temp/2;
			u16temp = LCD_PutString16(u16temp,120,VERSION,WHITE,BLACK);
			subsection = 2;
			break;
		default:
			break;
	}

}

