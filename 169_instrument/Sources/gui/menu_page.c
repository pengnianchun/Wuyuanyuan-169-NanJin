
#include "include.h"


#define START_SHOW_Y			80
#define START_SHOW_X			60
#define LINE_SPACE				40


void *name[] = {submenu_1,submenu_3,submenu_4,submenu_6,submenu_7};


void menu_page(void)
{
	U8 i;
	
	Select_old = Select;
	LCD_PutString16(20,80+Select*40,"-->",GREEN,BLACK);
	for( i=0; i<sizeof(name)/sizeof(name[0]);i++)
	{
		LCD_PutString16(START_SHOW_X,START_SHOW_Y+LINE_SPACE*i,name[i],WHITE,BLACK);
	}
	
	
}
void ShowSwtich(void)
{
	/**
	 * @TODO:按键处理；
	 */
	{
		KEY_TYPE_e key;
		unsigned int len;
		len = GetShowSize();
		key = ReadKey();
		len = len - SWITCH_PAGINATION -1;//!<菜单长度需要大于2否者会有问题
		if (NONE_KEY == key)
		{
		}
		else if (ENTER_KEY == key)
		{
			SetShowMenuPage(SWITCH_PAGINATION + Select);
			pagination = 0;
		}
		else if (BACK_KEY == key)
		{
			SetShowMenuPage(MAIN_PAGINATION);
		}
		else if (UP_KEY == key)
		{
			Select ++;
			if (Select > len)
			{
				Select = 0;
			}
		}
		else if (DOWN_KEY == key)
		{
			if (Select == 0)
			{

				Select = len;	
			}
			else
			{
				Select--;
			}
		}
	}

	switch(subsection){
		case 0:
			subsection = 1;
			GUI_clearscreen(BLACK);
			break;
		case 1:
			subsection = 2;
			//Select = 0;
			//Select_old=0;
			menu_page();
			break;
		case 2:
			if (Select_old != Select)
			{
				LCD_PutString16(20,80+Select_old*40,"   ",GREEN,BLACK);
				LCD_PutString16(20,80+Select*40,"-->",GREEN,BLACK);
				Select_old = Select;
			}
			break;
		default:
			subsection = 2;
			break;
	}
}

