#include "include.h"



unsigned char * Motor_control_page4[] = {
	page4_linel1,	// ����������;
	page4_linel2, 	// �������״̬;
	page4_linel3,	// ��������¶�;
	page4_linel4, 	//�������¶�;
	page4_linel5,	// �����������ѹ;
	page4_linel6, 	//������ֱ��ĸ�ߵ���;
	page4_linel7,	// �������ת��;
	page4_linel8,	// �������ת��;
	page4_linel9,	//���������������N2;
	page4_linela,	// �Զ�����ϴ���;
	NULL,
};

unsigned char * storage_motor[] = {
	NULL,
	para_div_state1,		// �ĵ�;
	para_div_state2,		// ����;
	para_div_state3,		// �ر�;
	para_div_state4,		// ׼��;
	para_div_state5,		// �쳣;

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
			
			u16temp = PAGE4_PAGINATION0_2;		//�������״̬
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

