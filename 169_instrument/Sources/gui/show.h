#ifndef SHOW_H__
	#define SHOW_H__

typedef void (*ShowMenuFun)(void);
extern ShowMenuFun ShowMenu[];

extern void Door_FL(unsigned char onoff);

extern void Door_RL(unsigned char onoff);

extern void Door_FR(unsigned char onoff);

extern void Door_RR(unsigned char onoff);

extern void Door_R(unsigned char onoff);

#define TEXTBOX_X_COORDINATE     (180)
#define TEXTBOX_Y_COORDINATE     (27 * 2)
#define LINE_PACKING			 (27)

#define MAIN_PAGINATION		     (0)
#define DEBUG_PAGINATION         (1)
#define FAULT_PAGINATION		 (2)


#define ShowFlot_sign(data,idx,precision,sign)			do{\
															u16temp = data;\
															DigitToString_flot(Buff,u16temp,idx,precision);\
															u16temp = LCD_PutString16(TEXTBOX_X_COORDINATE,y,Buff,WHITE,BLACK);\
															u16temp = LCD_PutString16(u16temp,y,sign,WHITE,BLACK);\
															ClearStringLine(u16temp,y);\
															y += LINE_PACKING;\
														}while(0)

#define ShowDigit_sign(data,idx,sign)			       do{\
															u16temp = data;\
															DigitToString_int(Buff,u16temp,idx);\
															u16temp = LCD_PutString16(TEXTBOX_X_COORDINATE,y,Buff,WHITE,BLACK);\
															u16temp = LCD_PutString16(u16temp,y,sign,WHITE,BLACK);\
															ClearStringLine(u16temp,y);\
															y += LINE_PACKING;\
														}while(0)
#define ShowDigit(data,idx)			                    do{\
																u16temp = data;\
																DigitToString_int(Buff,u16temp,idx);\
																u16temp = LCD_PutString16(TEXTBOX_X_COORDINATE,y,Buff,WHITE,BLACK);\
																ClearStringLine(u16temp,y);\
																y += LINE_PACKING;\
															}while(0)

#define ShowSelectStrin(idx,arr)						do{\
															u16temp = idx;\
														    u16temp = LCD_PutString16(TEXTBOX_X_COORDINATE,y,arr[u16temp],WHITE,BLACK);\
															ClearStringLine(u16temp,y);\
															y += LINE_PACKING;\
														}while(0)

#define ShowHexLong(pdata)							    do{\
															sprintf(Buff,"%02X%02X%02X%02X",pdata[3],pdata[2],pdata[1],pdata[0]);\
															u16temp = LCD_PutString16(TEXTBOX_X_COORDINATE,y,Buff,WHITE,BLACK);\
															ClearStringLine(u16temp,y);\
															y += LINE_PACKING;\
														}while(0)
#define ShowNull()								        do{\
															ClearStringLine(TEXTBOX_X_COORDINATE,y);\
															y += LINE_PACKING;\
														}while(0)
extern unsigned int GetShowSize(void);														
void SetShowMenuPage(unsigned int page);

						
#endif