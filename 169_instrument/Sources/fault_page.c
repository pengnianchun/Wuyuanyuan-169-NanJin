#include "include.h"

const unsigned char *fault_name[] = 
{
	vcu_diag_1,vcu_diag_2,vcu_diag_3,vcu_diag_4,vcu_diag_5,vcu_diag_6,vcu_diag_7,vcu_diag_8,vcu_diag_9,vcu_diag_10,
	vcu_diag_11,vcu_diag_12,vcu_diag_13,vcu_diag_14,vcu_diag_15,vcu_diag_16,vcu_diag_17,vcu_diag_18,vcu_diag_19,vcu_diag_20,
	
};

void ShowFrame(unsigned char ** name,unsigned int len)
{
	int l;
	unsigned int temp;
	for(l = 0;l<len;l++)
	{
		temp = LCD_Put24String(10,70 + l*34,name[l],WHITE,BLACK);
		LCD_Put24String(temp,70 + l*34,":",WHITE,BLACK);
	}
}

#define SHOW_FAULT(x,s_true,s_fault)	\
	do{\
		if (x)\
		{\
			LCD_Put24String(214,y,s_fault,RED,BLACK);\
		}\
		else\
		{\
			LCD_Put24String(214,y,s_true,GREEN,BLACK);\
		}\
		y += 34;\
	}while(0)
void FaultMenu(void)
{
	U8 u8temp[3];
	int i,j;
	unsigned int y;
	unsigned char idx_byte,idx_bit;
	y =70;
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
		else if (UP_KEY == key)
		{
			if (pagination < 2)
			{
				pagination++;
				subsection = 0;
			}
			
		}
		else if (DOWN_KEY == key)
		{
			if (pagination > 0)
			{
				pagination--;
				subsection = 0;
			}
		}
	}
	switch(subsection){
		case 0:
			subsection = 1;
			GUI_clearscreen(BLACK);
			break;
		case 1:
			switch(pagination%3)
			{
				case 0:
					LCD_PutBmp(20-5,2,BmpZheng[0],BmpZheng[1],&BmpZheng[3],RED,BLACK);
					LCD_PutBmp(20-5+44,0,BmpChe[0],BmpChe[1],&BmpChe[3],RED,BLACK);
					LCD_PutBmp(20-5+44+42,1,BmpGu[0],BmpGu[1],&BmpGu[3],RED,BLACK);
					LCD_PutBmp(20-5+44+42+43,4,BmpZhang[0],BmpZhang[1],&BmpZhang[3],RED,BLACK);
					LCD_PutBmp(20-5+44+42+43+41,5,BmpMa[0],BmpMa[1],&BmpMa[3],RED,BLACK);
					LCD_PutBmp(20+44+42+43+41+44,10,Bmp1[0],Bmp1[1],&Bmp1[3],RED,BLACK);
					LCD_Put24String(50,440,hint2,RED,BLACK);
					LCD_Put24String(160,440,hint3,WHITE,BLACK);
					ShowFrame(fault_name,8);
					subsection = 2;
					break;
				case 1:
					LCD_PutBmp(20-5,2,BmpZheng[0],BmpZheng[1],&BmpZheng[3],RED,BLACK);
					LCD_PutBmp(20-5+44,0,BmpChe[0],BmpChe[1],&BmpChe[3],RED,BLACK);
					LCD_PutBmp(20-5+44+42,1,BmpGu[0],BmpGu[1],&BmpGu[3],RED,BLACK);
					LCD_PutBmp(20-5+44+42+43,4,BmpZhang[0],BmpZhang[1],&BmpZhang[3],RED,BLACK);
					LCD_PutBmp(20-5+44+42+43+41,5,BmpMa[0],BmpMa[1],&BmpMa[3],RED,BLACK);
					LCD_PutBmp(20+44+42+43+41+44,10,Bmp2[0],Bmp2[1],&Bmp2[3],RED,BLACK);
					LCD_Put24String(10,440,hint2,RED,BLACK);
					LCD_Put24String(110,440,hint1,WHITE,BLACK);
					LCD_Put24String(218,440,hint3,WHITE,BLACK);
					ShowFrame(&fault_name[8],7);
					subsection = 3;
					break;
				case 2:
					LCD_PutBmp(20-5,2,BmpZheng[0],BmpZheng[1],&BmpZheng[3],RED,BLACK);
					LCD_PutBmp(20-5+44,0,BmpChe[0],BmpChe[1],&BmpChe[3],RED,BLACK);
					LCD_PutBmp(20-5+44+42,1,BmpGu[0],BmpGu[1],&BmpGu[3],RED,BLACK);
					LCD_PutBmp(20-5+44+42+43,4,BmpZhang[0],BmpZhang[1],&BmpZhang[3],RED,BLACK);
					LCD_PutBmp(20-5+44+42+43+41,5,BmpMa[0],BmpMa[1],&BmpMa[3],RED,BLACK);
					LCD_PutBmp(20+44+42+43+41+44,10,Bmp3[0],Bmp3[1],&Bmp3[3],RED,BLACK);
					LCD_Put24String(50,440,hint1,RED,BLACK);
					LCD_Put24String(168,440,hint3,WHITE,BLACK);
					ShowFrame(&fault_name[15],5);
					subsection = 4;
					break;
			}
			break;
		case 2:
			if(IfClean_ID041000A0< 15) {
				SHOW_FAULT(can_signal.ID_041000A0.VCU_Diag_Code1.Bits.bit7,vc_para1,vc_para4);
				SHOW_FAULT(can_signal.ID_041000A0.VCU_Diag_Code1.Bits.bit6,vc_para1,vc_para4);
				SHOW_FAULT(can_signal.ID_041000A0.VCU_Diag_Code1.Bits.bit5,vc_para2,vc_para5);
				SHOW_FAULT(can_signal.ID_041000A0.VCU_Diag_Code1.Bits.bit4,vc_para2,vc_para5);
				SHOW_FAULT(can_signal.ID_041000A0.VCU_Diag_Code1.Bits.bit3,vc_para1,vc_para4);
				SHOW_FAULT(can_signal.ID_041000A0.VCU_Diag_Code1.Bits.bit2,vc_para1,vc_para4);
				SHOW_FAULT(can_signal.ID_041000A0.VCU_Diag_Code1.Bits.bit1,vc_para1,vc_para4);
				SHOW_FAULT(can_signal.ID_041000A0.VCU_Diag_Code1.Bits.bit0,vc_para1,vc_para4);			
			} else {
				SHOW_FAULT(can_signal.ID_041000A0.VCU_Diag_Code1.Bits.bit7,"    ","    ");
				SHOW_FAULT(can_signal.ID_041000A0.VCU_Diag_Code1.Bits.bit6,"    ","    ");
				SHOW_FAULT(can_signal.ID_041000A0.VCU_Diag_Code1.Bits.bit5,"    ","    ");
				SHOW_FAULT(can_signal.ID_041000A0.VCU_Diag_Code1.Bits.bit4,"    ","    ");
				SHOW_FAULT(can_signal.ID_041000A0.VCU_Diag_Code1.Bits.bit3,"    ","    ");
				SHOW_FAULT(can_signal.ID_041000A0.VCU_Diag_Code1.Bits.bit2,"    ","    ");
				SHOW_FAULT(can_signal.ID_041000A0.VCU_Diag_Code1.Bits.bit1,"    ","    ");
				SHOW_FAULT(can_signal.ID_041000A0.VCU_Diag_Code1.Bits.bit0,"    ","    ");
			}
			break;
		case 3:
			if(IfClean_ID041000A0< 15) {
				SHOW_FAULT(can_signal.ID_041000A0.VCU_Diag_Code2.Bits.bit6,vc_para1,vc_para4);
				SHOW_FAULT(can_signal.ID_041000A0.VCU_Diag_Code2.Bits.bit5,vc_para1,vc_para4);
				SHOW_FAULT(can_signal.ID_041000A0.VCU_Diag_Code2.Bits.bit4,vc_para2,vc_para5);
				SHOW_FAULT(can_signal.ID_041000A0.VCU_Diag_Code2.Bits.bit3,vc_para1,vc_para3);
				SHOW_FAULT(can_signal.ID_041000A0.VCU_Diag_Code2.Bits.bit2,vc_para1,vc_para6);
				SHOW_FAULT(can_signal.ID_041000A0.VCU_Diag_Code2.Bits.bit1,vc_para1,vc_para4);
				SHOW_FAULT(can_signal.ID_041000A0.VCU_Diag_Code2.Bits.bit0,vc_para1,vc_para7);
			} else {
				SHOW_FAULT(can_signal.ID_041000A0.VCU_Diag_Code2.Bits.bit6,"    ","    ");
				SHOW_FAULT(can_signal.ID_041000A0.VCU_Diag_Code2.Bits.bit5,"    ","    ");
				SHOW_FAULT(can_signal.ID_041000A0.VCU_Diag_Code2.Bits.bit4,"    ","    ");
				SHOW_FAULT(can_signal.ID_041000A0.VCU_Diag_Code2.Bits.bit3,"    ","    ");
				SHOW_FAULT(can_signal.ID_041000A0.VCU_Diag_Code2.Bits.bit2,"    ","    ");
				SHOW_FAULT(can_signal.ID_041000A0.VCU_Diag_Code2.Bits.bit1,"    ","    ");
				SHOW_FAULT(can_signal.ID_041000A0.VCU_Diag_Code2.Bits.bit0,"    ","    ");
			}
			break;
		case 4:
			if(IfClean_ID041000A0< 15) {
				SHOW_FAULT(can_signal.ID_041000A0.VCU_Diag_Code3.Bits.bit3,vc_para1,vc_para3);
				SHOW_FAULT(can_signal.ID_041000A0.VCU_Diag_Code3.Bits.bit2,vc_para1,vc_para4);
				SHOW_FAULT(can_signal.ID_041000A0.VCU_Diag_Code3.Bits.bit1,vc_para1,vc_para4);
				SHOW_FAULT(can_signal.ID_041000A0.VCU_Diag_Code3.Bits.bit0,vc_para1,vc_para4);
				SHOW_FAULT(can_signal.ID_041000A0.VCU_Diag_Code3.Bits.bit4,vc_para1,vc_para3);
			} else {
				SHOW_FAULT(can_signal.ID_041000A0.VCU_Diag_Code3.Bits.bit3,"    ","    ");
				SHOW_FAULT(can_signal.ID_041000A0.VCU_Diag_Code3.Bits.bit2,"    ","    ");
				SHOW_FAULT(can_signal.ID_041000A0.VCU_Diag_Code3.Bits.bit1,"    ","    ");
				SHOW_FAULT(can_signal.ID_041000A0.VCU_Diag_Code3.Bits.bit0,"    ","    ");
				SHOW_FAULT(can_signal.ID_041000A0.VCU_Diag_Code3.Bits.bit4,"    ","    ");
			}
			break;

			default:
				subsection = 0;
				break;
	}
} 
