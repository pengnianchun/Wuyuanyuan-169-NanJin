#include "include.h"


static unsigned char DangWei=0,WarningP1=0,WarningP3=0,WarningP4=0;


static unsigned char KM1[]="000.0Km";
static unsigned char KM2[]="000000Km";
static char s_display_tack_a = 0;
static char s_display_tack_a2= 0;//画剩余里程图标标志
static char s_display_tack_a3= 0;//平均功耗标志位

static char FaultPicUpdate = 0;
unsigned char flag[7],old_flag[7];


static U8 fault_config = 0;
static U8 driving_mode = 0xFF;





void main_page(void)//刷新主界面固定部分
{
	ChargeDischargeCurrentFlag = 1;
	BatteryTotalVoltageUpdateFlag = 1;
	ready_flag = 0;
	Door_Flag = 0;
	soc_low_time = 0;
	s_display_tack_a = 0;
	s_display_tack_a2= 0;
	s_display_tack_a3= 0;
	fault_config = 1;
	DangWei = 0;
	ready_flag = 0;
	driving_mode = 0xFF;
	//!<TODO:显示部分
	LCD_Put24String(10,9,main_page_1,WHITE,BLACK);
	LCD_Put24String(10,85,main_page_2,WHITE,BLACK);
	//LCD_Put24String(248,456,"KM",WHITE,BLACK);
	LCD_Put24String(91 - 71,36,"V",WHITE,BLACK);
	LCD_Put24String(91 - 71,112,"A",WHITE,BLACK);
	//GUI_box(10,376,90,470,PURPLE);//

	//GUI_box(200,0,201,75,GRAY);
	//GUI_box(200,77,201,151,GRAY);
	GUI_box(1,75,271,76,WHITE);
	GUI_box(1,152,271,153,WHITE);
	GUI_box(1,330,271,331,WHITE);
	GUI_box(1,400,271,401,WHITE);
	GUI_box(1,281,271,282,GRAY);
	GUI_box(54,283,55,329,GRAY);
	GUI_box(109,283,110,329,GRAY);
	GUI_box(162,283,163,329,GRAY);
	GUI_box(216,283,217,329,GRAY);
	LCD_PutBmp(200,19,SOCLow[0],SOCLow[1],&SOCLow[3],GRAY,BLACK);
	LCD_PutBmp(200,94,BatteryTempHigh[0],BatteryTempHigh[1],&BatteryTempHigh[3],GRAY,BLACK);
	LCD_PutBmp(3,287,MotorFault[0],MotorFault[1],&MotorFault[3],GRAY,BLACK);
	LCD_PutBmp(58,288,TimingCharge[0],TimingCharge[1],&TimingCharge[3],GRAY,BLACK);
	LCD_PutBmp(111,287,VehicleLowSpeed[0],VehicleLowSpeed[1],&VehicleLowSpeed[3],GRAY,BLACK);
	LCD_PutBmp(164,287,DriverPowerLimit[0],DriverPowerLimit[1],&DriverPowerLimit[3],GRAY,BLACK);
	LCD_PutBmp(218+2,287,AutoDriver[0],AutoDriver[1],&AutoDriver[3],GRAY,BLACK);
	memset(flag,0,sizeof(flag));
	memset(old_flag,0,sizeof(old_flag));
	//LCD_Put24String(107, 338,"Ready" , GREEN,BLACK);
	
	//LCD_Put24CHStringMultiply(76,340,"READY",GREEN,BLACK);

}
/**************************************************************************/
/**
 * 思路:将显示任务拆分;由于不是所有显示都需要进行修改;
 * 对于不需要修改的任务直接跳过到下一个任务执行.
 */
void ShowBattCurrentINS(void)
{
	U16 u16temp;
	U8 u8_20[20];
	U8 buffer[8];
	
	u16temp = PAGE0_PAGINATION0_2;
	if ((ChargeDischargeCurrent != u16temp)||ChargeDischargeCurrentFlag)
	{
		if(IfClean_ID1810A6A0 < TIMEOUT_RANGE_MIN){
			ChargeDischargeCurrent = u16temp;
			memset(buffer,0,sizeof(buffer));
			memset(u8_20,0,sizeof(u8_20));
			if (ChargeDischargeCurrent < 4000)
			{
				u16temp = 4000 - u16temp;
				sprintf(u8_20, "%4u.%u", u16temp/10, u16temp%10);
				LCD_Put24String(91+35-71,112,"-",WHITE,BLACK);
			}
			else
			{
				u16temp = u16temp - 4000;
				if(u16temp > 12000) {
				    u16temp = 12000;
				}
				sprintf(u8_20, "%4u.%u", u16temp/10, u16temp%10);
				LCD_Put24String(91+35-71,112,"-",BLACK,BLACK);
			}
			memcpy(buffer,u8_20,strlen(u8_20));
			u16temp = strlen(u8_20);
			LCD_Put24String(162-71,112,buffer,WHITE,BLACK);
		}else {
			LCD_Put24String(162-71,112,"----.-",WHITE,BLACK);
			LCD_Put24String(91+35-71,112,"-",BLACK,BLACK);
			
		}
	}
}
void ShowBattVoltINS(void)
{
	U16 u16temp;
	U8 u8_20[20];
	
	u16temp = PAGE0_PAGINATION0_1;
	if ((BatteryTotalVoltage != u16temp)||BatteryTotalVoltageUpdateFlag)
	{
		if(IfClean_ID1810A6A0 < TIMEOUT_RANGE_MIN){
		    if(u16temp > 8000) {
		        u16temp = 8000;
		    }
			BatteryTotalVoltage = u16temp;
		    sprintf(u8_20, "%4u.%u", u16temp/10, u16temp%10);
			LCD_Put24String(162-71,36,u8_20,WHITE,BLACK);		
		} else {
			LCD_Put24String(162-71,36," ---.-",WHITE,BLACK);
		}
	}
	
}

void ShowMileage(void)
{
	unsigned long Ltemp;
	U8 buffer[12] = {0};
	Ltemp = KmTotalShort;
	sprintf(buffer,"%3lu.%luKm",Ltemp/10,Ltemp%10);
	LCD_Put24String(176,455,buffer,WHITE,BLACK);
	memset(buffer,0,sizeof(buffer));
	Ltemp=KmTotalLong;
	sprintf(buffer,"%6luKm",Ltemp/10);
	LCD_Put24String(164,415,buffer,WHITE,BLACK);
}



/**
 * @区域A
 * @{
 */
void ShowOpenDoor(U8 door)
{
	U8 temp;
	U16 fcolor;
	if (Door_Flag == 0)
	{
		s_display_tack_a = 0;
		GUI_box(0,154,271,329,BLACK);
		LCD_PutBmp(117,169,bmp_car_39x130[2],bmp_car_39x130[4],&bmp_car_39x130[6],RED,BLACK);			
	}
	temp = door ^ Door_Flag;
	Door_Flag = door;
	if (temp & 0x01)
	{
		if (door & 0x01)
		{
			fcolor = RED;
		}
		else
		{
			fcolor = BLACK;
		}
		LCD_PutBmp(118,169+130+2,gImage_postern_36x10[2],gImage_postern_36x10[4],&gImage_postern_36x10[6],fcolor,BLACK);
	}
	if (temp & 0x02)
	{
		if (door & 0x02)
		{
			fcolor = RED;
		}
		else
		{
			fcolor = BLACK;
		}
		GUI_box(165,240,170,280,fcolor);
	}
	if (temp & 0x04)
	{
		if (door & 0x04)
		{
			fcolor = RED;
		}
		else
		{
			fcolor = BLACK;
		}
		LCD_PutBmp(117+39,169+39,gImage_door_r_24x26[2],gImage_door_r_24x26[4],&gImage_door_r_24x26[6],fcolor,BLACK);
	}
	if (temp & 0x08)
	{
		if (door & 0x08)
		{
			fcolor = RED;
		}
		else
		{
			fcolor = BLACK;
		}
		LCD_PutBmp(117-24,169+39,gImage_door_l_24x26[2],gImage_door_l_24x26[4],&gImage_door_l_24x26[6],fcolor,BLACK);
	}	
	if (temp & 0x10)
	{
		if (door & 0x10)
		{
			fcolor = RED;
		}
		else
		{
			fcolor = BLACK;
		}
		LCD_PutBmp(117,169,bmp_car_39x130[2],bmp_car_39x130[4],&bmp_car_39x130[6],fcolor,BLACK);
	}	
	
}
#define LineSpacing		5
void AreaDisplayString(U16 x,U16 y,U16 dx,U16 dy,U8 *str,U16 fColor,U16 bColor)
{
	U16 u16temp;
	U16 ex,ey;
	U16 len_max;
	len_max = dx-x;
	len_max = (len_max)/12;
	u16temp = strlen(str);
	GUI_box(0,y,271,dy,BLACK);
	if (u16temp<len_max)
	{
		ex = dx-x;
		ex = ex - u16temp * 12;
		ex /= 2;
		ex += x;
		ey = dy-y - 24;
		ey /= 2;
		ey += y;
		LCD_Put24String(ex,ey,str,fColor,bColor);
		
	}
	else
	{
		U8 buf[25];
		memcpy(buf,str,len_max);
		buf[len_max] = 0;
		ex = dx-x-len_max*12;
		ex /= 2;
		ex += x;
		ey = dy-y - (24*2+LineSpacing);
		ey /= 2;
		ey += y;
		LCD_Put24String(ex,ey,buf,fColor,bColor);
		u16temp = u16temp - len_max+1;
		ex = 272;
		ex = ex - u16temp * 12;
		ex /= 2;
		ey += 24 + LineSpacing;
		LCD_Put24String(ex,ey,&str[len_max],fColor,bColor);
	}
}
#define ShowDisplayStr(str)		AreaDisplayString(10,154,262,280,str,YELLOW,BLACK)
void ShowMotorSpeed(void)
{
	U16 temp;
	U8 buf[20];
	if (s_display_tack_a != 1)
	{
		GUI_box(0,154,271,280,BLACK);
		LCD_PutBmp(70 - 60,190 - 30,Bmp036[0],Bmp036[1],&Bmp036[3],WHITE,BLACK);
		s_display_tack_a = 1;
	}
	temp = PAGE0_PAGINATION0_6;
	
	if (temp<15000)
	{
		temp = 15000- temp;
		sprintf(buf," %5u rpm",temp);
		for(temp = 0;temp<20;temp++)
		{
			if (buf[temp+1] != ' ')
			{
				buf[temp] = '-';
				break;
			}
		}
	}
	else
	{
		temp = temp - 15000;
		sprintf(buf," %5u rpm",temp);
	}

	if(IfClean_ID0CFF0008 >= TIMEOUT_RANGE_MIN){
		memset(buf, 0, sizeof(buf));
		sprintf(buf," ----- rpm");
	}
	LCD_Put24String(85 + 50 - 25,250 - 90,buf,WHITE,BLACK);
}

void ShowRemainingMile(void){
	U16 temp;
	U8 buf[20];
	if(s_display_tack_a2!= 1)
	{
		//GUI_box(0,180,271,329,BLACK);
		LCD_PutBmp(70 - 60,190 + 5,RemainingMilPic[0],RemainingMilPic[1],&RemainingMilPic[3],BLACK,WHITE);
		s_display_tack_a2= 1;
	}
	temp = PAGE0_PAGINATION0_9 * 2;
	sprintf(buf," %3u KM",temp);
	LCD_Put24String(85 + 50 ,250 - 30 - 10 - 5,buf,WHITE,BLACK);
}
void showAveragePower(void)
{
	U16 temp;
	U8 buf[20];
	if(s_display_tack_a3!= 1)
	{
		LCD_PutBmp(70 - 60,190 + 10 + 50,AveragePower[0],AveragePower[1],&AveragePower[3],WHITE,BLACK);
		LCD_PutBmp(70 - 60 + 185,190 + 10 + 50,AveragePowerUnit[0],AveragePowerUnit[1],&AveragePowerUnit[3],WHITE,BLACK);
		s_display_tack_a3 = 1;
	}
	temp = PAGE0_PAGINATION0_10;
	temp = (temp * 10)/2;
	sprintf(buf," %3u.%u",temp/10,temp%10);
	LCD_Put24String(85 + 50 - 20,250 - 30 + 30,buf,WHITE,BLACK);
}

void ShowWarning(void)
{
	U16 temp;
	FAULT_TYPE *warnig;
	U8 buffer[20];
	
	if (warning_show_time)
	{
		return;
	}
	if(IfClean_ID041000A0 >= TIMEOUT_RANGE_MIN){
		CleanMessageBuffer();
	}
	temp = IsQueueEmpty(&warning_fifo);
	if(temp == 0)
	{
		s_display_tack_a = 0;
		s_display_tack_a2 = 0;
		s_display_tack_a3 = 0;
		warning_show_time = 32;
		warnig = ReadFifo(&warning_fifo);
		if (beep_info.temp <= 1)
		{
			beep_info.temp = 1;
			AlarmSong(100, 200, 1);
		}

		switch(warnig->ID)
		{

			case 0:ShowDisplayStr(warning_string_1);break;
			case 1:ShowDisplayStr(warning_string_2);break;
			case 2:ShowDisplayStr(warning_string_3);break;
			case 3:ShowDisplayStr(warning_string_4);break;
			case 5:ShowDisplayStr(warning_string_5);break;
			case 6:ShowDisplayStr(warning_string_6);break;
			case 8:ShowDisplayStr(warning_string_7);break;
			case 9:ShowDisplayStr(warning_string_8);break;
			case 10:ShowDisplayStr(warning_string_9);break;
			case 11:ShowDisplayStr(warning_string_10);break;
			case 12:ShowDisplayStr(warning_string_11);break;
			case 13:ShowDisplayStr(warning_string_12);break;
			case 14:ShowDisplayStr(warning_string_13);break;
			case 15:ShowDisplayStr(warning_string_14);break;
			case 16:ShowDisplayStr(warning_string_15);break;
			case 17:ShowDisplayStr(warning_string_16);break;
			case 18:ShowDisplayStr(warning_string_17);break;
			case 19:ShowDisplayStr(warning_string_18);break;
			case 20:ShowDisplayStr(warning_string_19);break;
		}
	}
	else
	{
		ShowMotorSpeed();
		ShowRemainingMile();
		showAveragePower();
	}
}

unsigned char GetDoorFlag(void)
{
	unsigned char temp = 0;
	if (!CHECKBIT(ReadH,B4))
	{
		temp = 0X01;
	}
	temp <<=1;
	if (PTIM_PTIM3 != 1)
	{
		temp |= 1;
	}
	temp <<=1;
	if(!CHECKBIT(ReadL,B5))
	{
		temp |= 1;
	}
	temp <<=1;
	if (!CHECKBIT(ReadL,B4))
	{
		temp |= 1;
	}
	return temp;
}

void ShowFaultPic(void)
{
	flag[0] = can_signal.ID_1810A6A0.LED.bit.LED5;
	flag[1] = can_signal.ID_1811A6A0.MotorDriverFault;
	flag[2] = can_signal.ID_1811A6A0.PowerBatteryTemp;
	flag[3] = can_signal.ID_1811A6A0.TimingCharge;
	flag[4] = can_signal.ID_1811A6A0.VehicleLowSpeed;
	flag[5] = can_signal.ID_1811A6A0.DriverPowerLimit;
	flag[6] = can_signal.ID_1811A6A0.LED5;
	if(old_flag[0] != flag[0]) 
	{
		if(flag[0] !=0)
		{
			LCD_PutBmp(200,19,SOCLow[0],SOCLow[1],&SOCLow[3],YELLOW,BLACK);
		}
		else
		{
			LCD_PutBmp(200,19,SOCLow[0],SOCLow[1],&SOCLow[3],GRAY,BLACK);
		}
		old_flag[0] = flag[0];
	}
	if(old_flag[2] != flag[2]) 
	{
		if(flag[2] != 0)
		{
			LCD_PutBmp(200,94,BatteryTempHigh[0],BatteryTempHigh[1],&BatteryTempHigh[3],RED,BLACK);
		}
		else
		{
			LCD_PutBmp(200,94,BatteryTempHigh[0],BatteryTempHigh[1],&BatteryTempHigh[3],GRAY,BLACK);
		}
		old_flag[2] = flag[2];
	}
	if(old_flag[1] != flag[1]) 
	{
		if(flag[1] != 0)
		{
			LCD_PutBmp(3,287,MotorFault[0],MotorFault[1],&MotorFault[3],RED,BLACK);
		}
		else
		{
			LCD_PutBmp(3,287,MotorFault[0],MotorFault[1],&MotorFault[3],GRAY,BLACK);
		}
		old_flag[1] = flag[1];
	}
	if(old_flag[3] != flag[3]) 
	{
		if(flag[3] != 0)
		{
			LCD_PutBmp(58,288,TimingCharge[0],TimingCharge[1],&TimingCharge[3],GREEN,BLACK);
		}
		else
		{
			LCD_PutBmp(58,288,TimingCharge[0],TimingCharge[1],&TimingCharge[3],GRAY,BLACK);
		}
		old_flag[3] = flag[3];
	}
	if(old_flag[4] != flag[4]) 
	{
		if(flag[4] != 0)
		{
			LCD_PutBmp(111,287,VehicleLowSpeed[0],VehicleLowSpeed[1],&VehicleLowSpeed[3],YELLOW,BLACK);
		}
		else
		{
			LCD_PutBmp(111,287,VehicleLowSpeed[0],VehicleLowSpeed[1],&VehicleLowSpeed[3],GRAY,BLACK);
		}
		old_flag[4] = flag[4];
	}
	if(old_flag[5] != flag[5]) 
	{
		if(flag[5] != 0)
		{
			LCD_PutBmp(164,287,DriverPowerLimit[0],DriverPowerLimit[1],&DriverPowerLimit[3],YELLOW,BLACK);
		}
		else
		{
			LCD_PutBmp(164,287,DriverPowerLimit[0],DriverPowerLimit[1],&DriverPowerLimit[3],GRAY,BLACK);
		}
		old_flag[5] = flag[5];
	}
	if(old_flag[6] != flag[6]) 
	{
		if(flag[6] != 0)
		{
			LCD_PutBmp(218+2,287,AutoDriver[0],AutoDriver[1],&AutoDriver[3],GREEN,BLACK);
		}
		else
		{
			LCD_PutBmp(218+2,287,AutoDriver[0],AutoDriver[1],&AutoDriver[3],GRAY,BLACK);
		}
		old_flag[6] = flag[6];
	}
}

void AreaDisplayA(void)
{
	static char old_sta = 0;
	U16 temp;
	
//	static U8 old_flag_1810A6A0 = 0x00;
//	static U8 old_flag_1811A6A0 = 0x00;
//	U8 flag_1810A6A0;
//	U8 flag_1811A6A0;


//	flag_1810A6A0 = can_signal.ID_1810A6A0.LED.byte;
//	flag_1811A6A0 = can_signal.ID_1811A6A0.LED2;
//	if (flag_1810A6A0 != old_flag_1810A6A0 || flag_1811A6A0 != old_flag_1811A6A0)
//	{
//		old_flag_1810A6A0 = flag_1810A6A0;
//		old_flag_1811A6A0 = flag_1811A6A0;
//		if(flag_1810A6A0&0x58 || flag_1811A6A0&0x01){
//			if(beep_info.cont == 0 || beep_info.temp < 5){
//				alarm_msg = 0;
//				beep_info.temp = 5;
//				AlarmSong(100, 200, 5);
//			}
//		}
//	}
//	
	static U8 old_flag_1810A6A0 = 0x00;
	static U8 old_flag1_1810A6A0 = 0x00;
	static U8 old_flag_1811A6A0_MotorDriverFault= 0x00;
	static U8 old_flag_1811A6A0_PowerBatteryTemp= 0x00;
	static U8 old_flag_1811A6A0_READY = 0x00;
	static U8 old_flag_1811A6A0_LED2 = 0x00;
	static U8 old_flag_1811A6A0_LED4= 0x00;
	static U8 old_flag_1811A6A0_LED6= 0x00;
	static U8 old_flag_1811A6A0_LED7= 0x00;
	
	U8 flag_1810A6A0;
	U8 flag1_1810A6A0;
	U8 flag_1811A6A0_MotorDriverFault;
	U8 flag_1811A6A0_PowerBatteryTemp;
	U8 flag_1811A6A0_READY;
	U8 flag_1811A6A0_LED2;
	U8 flag_1811A6A0_LED4;
	U8 flag_1811A6A0_LED6;
	U8 flag_1811A6A0_LED7;
	
	

	flag_1810A6A0 = can_signal.ID_1810A6A0.LED.byte&0x70;
	flag1_1810A6A0 = can_signal.ID_1810A6A0.LED.byte&0x08;
	flag_1811A6A0_MotorDriverFault = can_signal.ID_1811A6A0.MotorDriverFault;
	flag_1811A6A0_PowerBatteryTemp = can_signal.ID_1811A6A0.PowerBatteryTemp;
	flag_1811A6A0_READY = can_signal.ID_1811A6A0.LED1;
	flag_1811A6A0_LED2 = can_signal.ID_1811A6A0.LED2;
	flag_1811A6A0_LED4 = can_signal.ID_1811A6A0.LED4;
	flag_1811A6A0_LED6 = can_signal.ID_1811A6A0.LED6;
	flag_1811A6A0_LED7 = can_signal.ID_1811A6A0.LED7;
	
	if (flag_1810A6A0 != old_flag_1810A6A0 
		|| flag_1811A6A0_MotorDriverFault != old_flag_1811A6A0_MotorDriverFault
		|| flag_1811A6A0_LED4 != old_flag_1811A6A0_LED4
		|| flag_1811A6A0_LED7 != old_flag_1811A6A0_LED7)
	{
		old_flag_1810A6A0 = flag_1810A6A0;
		old_flag_1811A6A0_MotorDriverFault = flag_1811A6A0_MotorDriverFault;
		old_flag_1811A6A0_LED4 = flag_1811A6A0_LED4;
		old_flag_1811A6A0_LED7 = flag_1811A6A0_LED7;
		if(flag_1810A6A0 || flag_1811A6A0_MotorDriverFault&0x01
			|| flag_1811A6A0_LED4&0x01 || flag_1811A6A0_LED7&0x01){
			if(beep_info.cont == 0 || beep_info.temp < 10){
				alarm_msg = 0;
				beep_info.temp = 10;
				AlarmSong(500, 700, 29);
			}
		}
	}
	if(flag1_1810A6A0 != old_flag1_1810A6A0 || flag_1811A6A0_PowerBatteryTemp != old_flag_1811A6A0_PowerBatteryTemp
		|| flag_1811A6A0_LED2 != old_flag_1811A6A0_LED2)
	{
		old_flag1_1810A6A0 = flag1_1810A6A0;
		old_flag_1811A6A0_PowerBatteryTemp = flag_1811A6A0_PowerBatteryTemp;
		old_flag_1811A6A0_LED2 = flag_1811A6A0_LED2;
		if(flag1_1810A6A0 || flag_1811A6A0_PowerBatteryTemp&0x01 || flag_1811A6A0_LED2&0x01)
		{
			if(beep_info.cont == 0 || beep_info.temp < 20){
				alarm_msg = 0;
				beep_info.temp = 20;
				AlarmSong(200, 400, 75);
			}
		}
	}
	if(flag_1811A6A0_LED6)
	{
			if(beep_info.cont == 0 || beep_info.temp < 5){
				alarm_msg = 0;
				beep_info.temp = 5;
				AlarmSong(500,1000, 10);
			}
	}
	if(flag_1811A6A0_READY == 0)
	{
		old_flag_1811A6A0_READY = flag_1811A6A0_READY;
	}
	else if(flag_1811A6A0_READY == 1 && old_flag_1811A6A0_READY != flag_1811A6A0_READY)
	{
		old_flag_1811A6A0_READY = flag_1811A6A0_READY;
		if(flag_1811A6A0_READY & 0x01)
		{
			if(beep_info.cont == 0 || beep_info.temp < 1){
					alarm_msg = 0;
					beep_info.temp = 1;
					AlarmSong(1500, 1500, 1);
			}
		}
	}
//	temp = GetDoorFlag();
//	if (temp != 0)
//	{
//		ShowOpenDoor(temp);
//		return ;
//	}
	ShowFaultPic();

	Door_Flag = 0;
	temp = PAGE0_PAGINATION0_7;
	if ((temp != old_sta)||(soc_low_time_long == 0))
	{
		//!<显示电池电量低
		old_sta = temp;
		if (temp)
		{
			U16 x,s;
			soc_low_time = 100;
			//beep_info.temp = 3;
			//AlarmSong(100, 200, 3);
			GUI_box(0,154,271,280,BLACK);
			s = strlen(main_page_para0);
 			s = s*8;
			x = 272 - s;
			x = x/2+5;
			LCD_PutString16(x,210,main_page_para0,YELLOW,BLACK);
			s = strlen(main_page_para1);
 			s = s*8;
			x = 272 - s;
			x = x/2;
			LCD_PutString16(x,231,main_page_para1,YELLOW,BLACK);
			s = strlen(main_page_para2);
 			s = s*8;
			x = 272 - s;
			x = x/2;
			LCD_PutString16(x,252,main_page_para2,YELLOW,BLACK);
			s_display_tack_a = 0;
			s_display_tack_a2 = 0;
			s_display_tack_a3 = 0;
			soc_low_time_long = 360;
		}
		else
		{
			soc_low_time = 0;
		}
		
	}

	
	if (soc_low_time == 0)
	{
		ShowWarning();
	}

}

/**
 * @
 * }
 */
/**
 * @ 区域B
 * @ {
 */
#define ShowDisplayStrB1(str)		AreaDisplayString(0,335,271,393,str,RED,BLACK)
#define ShowDisplayStrB2(str)		AreaDisplayStringB(0,335,271,393,str,RED,BLACK)

void AreaDisplayStringB(U16 x,U16 y,U16 dx,U16 dy,U8 *str,U16 fColor,U16 bColor)
{
	U16 u16temp;
	U16 ex,ey;
	
	u16temp = strlen(str);
	
	GUI_box(0,y,271,dy,BLACK);
	{
		ex = dx-x;
		ex = ex - u16temp * 8;
		ex /= 2;
		ex += x;
		ey = dy-y - 16;
		ey /= 2;
		ey += y;
		LCD_PutString16(ex,ey,str,fColor,bColor);
	}
}

void ShowFault(void)
{
	U16 u16temp;
	static U16 old_fault;
	if (fault_show_time)
	{
		return;
	}
	if(IfClean_ID041000A0 >= TIMEOUT_RANGE_MIN){
		CleanMessageBuffer();
	}
	u16temp = GetFaulID();
	if (u16temp != 0)
	{
		fault_config = 1;
		fault_show_time = BEEP_DURATION;
		if ((old_fault != u16temp) || (old_fault != 1)){
			if (beep_info.temp<5)
			{
				beep_info.temp = 5;
				AlarmSong(500,1000,5);
			}
			old_fault = u16temp;
		}
		
		
		switch(u16temp)
		{
			case 1:ShowDisplayStrB2(main_page_para4);break;
			case 2:ShowDisplayStrB1(vcu_diag_15s);break;
			case 3:ShowDisplayStrB1(vcu_diag_8);break;
			case 4:ShowDisplayStrB1(vcu_diag_6);break;
			case 5:ShowDisplayStrB1(vcu_diag_7);break;
			case 6:ShowDisplayStrB1(vcu_diag_5);break;
			case 7:ShowDisplayStrB1(vcu_diag_14);break;
			case 8:ShowDisplayStrB1(vcu_diag_9);break;
			case 9:ShowDisplayStrB1(vcu_diag_10);break;
			case 10:ShowDisplayStrB1(vcu_diag_13s);break;
			case 11:ShowDisplayStrB1(vcu_diag_16s);break;
			case 12:ShowDisplayStrB1(vcu_diag_17);break;
			case 13:ShowDisplayStrB1(vcu_diag_18);break;
			case 14:ShowDisplayStrB1(vcu_diag_19);break;
			case 15:ShowDisplayStrB1(vcu_diag_1s);break;
			case 16:ShowDisplayStrB1(vcu_diag_2s);break;
			case 17:ShowDisplayStrB1(vcu_diag_3s);break;
			case 18:ShowDisplayStrB1(vcu_diag_4s);break;
			case 19:ShowDisplayStrB1(vcu_diag_11s);break;
			case 20:ShowDisplayStrB1(vcu_diag_12s);break;
			case 21:ShowDisplayStrB1(vcu_diag_21);break;
			case 22:ShowDisplayStrB1(vcu_diag_22);break;
		}
	}
	else
	{
		if (fault_config){
			fault_config = 0;
			if(IfClean_ID041000A0 < TIMEOUT_RANGE_MIN){
				ShowDisplayStrB2(main_page_para3);
			}
		}
	}
}
void ShowReady(void)
{
	U16 temp;
	temp = PAGE0_PAGINATION0_8;
	if(beep_info.temp != 20 || can_signal.ID_1811A6A0.LED2 == 1){
    	if (ready_flag == 0)
    	{
    		ready_flag = 1;
    		GUI_box(0,335,271,393,BLACK);
    	}
    	
    	if(IfClean_ID1811A6A0 < TIMEOUT_RANGE_MIN){
    		if (temp == 0)
    		{
    			LCD_Put24CHStringMultiply(76,340,"READY",YELLOW,BLACK);
    		}
    		else
    		{
    			LCD_Put24CHStringMultiply(76,340,"READY",GREEN,BLACK);
    		}
    	} else {
    		LCD_Put24CHStringMultiply(76,340,"       ",GREEN,BLACK);
    	}   
	}
}
//void ShowReady(void)
//{
//	S8 temp;
//	static S8 old_temp = 0x00;
//	temp = PAGE0_PAGINATION0_8;
//	
//	if(IfClean_ID1811A6A0 < TIMEOUT_RANGE_MIN){
//	    if((old_temp != temp) || (ready_flag == 0)){
//            ready_flag = 1;
//    		if (temp == 0)
//    		{
//    			LCD_Put24CHStringMultiply(76,340,"READY",BLACK,BLACK);
//    		}
//    		else
//    		{
//    			LCD_Put24CHStringMultiply(76,340,"READY",GREEN,BLACK);
//    		}
//    		old_temp = temp;
//	    }
//	} else {
//	    if(old_temp != -1){
//	        
//		    LCD_Put24CHStringMultiply(76,340,"READY",BLACK,BLACK);
//	    }
//		old_temp = -1;
//	}
//}

void AreaDisplayB(void)
{
	U16 temp;
	temp = IsFaultNormal();
	if (temp && fault_config == 0)
	{
		ShowReady();
	}
	else
	{
		ready_flag = 0;
		ShowFault();
	}
}
/**
 * @ }
 */
static const char *driving_mode_str[] = 
{
	"Normal","Eco   ","Sport ","DH    ","Snow  ","Lim   ","Cc    ",
	"EcoPro","Limp  "
};


void AreaDisplayC(void)
{
	U16 temp;
	static char drive_flag = 0;
	if(IfClean_ID08F200A0 >= TIMEOUT_RANGE_MIN){
		DangWei = 0;
		driving_mode = 0xFE;
		GUI_box(11,412,61,462,BLACK);
		LCD_PutBmp(23,420,24,32,"",BLACK,BLACK);
		LCD_Put24String(75,441,"      ",GREEN,BLACK);
		GUI_rectangle(10,411,62,463,BLACK);
		return;
	}
	temp = PAGE0_PAGINATION0_3;
	GUI_rectangle(10,411,62,463,GREEN);
	switch(temp)
	{
		case 0:
			if(DangWei != 'N')
			{
				DangWei = 'N';
				GUI_box(11,412,61,462,BLACK);
				LCD_PutBmp(23,420,24,32,BmpN,GREEN,BLACK);
			}
			break;
		case 1:
			if(DangWei != 'P')
			{
				DangWei = 'P';
				GUI_box(11,412,61,462,BLACK);
				LCD_PutBmp(23,420,24,32,BmpP,GREEN,BLACK);
			}
			break;
		case 2:
			if(DangWei != 'S')
			{
				DangWei = 'S' ;
				GUI_box(11,412,61,462,BLACK);
				LCD_PutBmp(23,420,24,32,BmpS,GREEN,BLACK);
			}
			break;
		case 3:
			if(DangWei != 'E')
			{
				DangWei = 'E'  ;
				GUI_box(11,412,61,462,BLACK);
				LCD_PutBmp(23,420,24,32,BmpE,GREEN,BLACK);
			}
			break;
		case 4:
			if(DangWei != 'e')
			{
				DangWei = 'e' ;
				GUI_box(11,412,61,462,BLACK);
				LCD_PutBmp(12,420,47,32,BmpE_,GREEN,BLACK);
			}
			break;
		case 5:
			if(DangWei != 'R')
			{
				DangWei = 'R' ;
				GUI_box(11,412,61,462,BLACK);
				LCD_PutBmp(23,420,24,32,BmpR,YELLOW,BLACK);
			}
			break;
		case 10:
			if(DangWei != 'D')
			{
				DangWei = 'D' ;
				GUI_box(11,412,61,462,BLACK);
				LCD_PutBmp(23,420,24,32,BmpD,GREEN,BLACK);
			}
			break;
	}
	temp = PAGE0_PAGINATION0_4;
	if (driving_mode!=temp || drive_flag == 0)
	{
		driving_mode = temp;
		drive_flag = 1;
		if (temp == 0x08)
		{
			temp = 7;
		}
		else if (temp == 0x0F)
		{
			temp = 8;
		}
		if (temp<=0x08)
		{
			LCD_Put24String(75,441,driving_mode_str[temp],GREEN,BLACK);
		}
	}
}
void ShowMainPage(void)
{
	U16 u16temp;
	U8 u8_20[20];
	memset(u8_20,0,20);
	/**
	 * @TODO:按键处理；
	 */
	{
		KEY_TYPE_e key;
		key = ReadKey();
		if (ENTER_KEY == key)
		{
			//!<进入下一级菜单
			if (ready_flag == 1)
			{
				SetShowMenuPage(FAULT_PAGINATION);
			}
			else if (fault_config)
			{
				fault_show_time = 0;
			}
			else
			{
				pagination = 0;
				SetShowMenuPage(FAULT_PAGINATION);
			}
			return ;
		}
		else if (key == (LONG_KEY|BACK_KEY))
		{
			//!<TODO:清除里程表
			DisableInterrupts;
			KmTotalShort = 0;
			KmTotalShortFlag = 1;
			EnableInterrupts;
		}
		else if (key == (LONG_KEY|ENTER_KEY|UP_KEY|DOWN_KEY))
		{
			//!<进入调试界面；
			SetShowMenuPage(DEBUG_PAGINATION);
			return;
		}
	}
	switch(subsection)
	{
		case 0:
			subsection =1;
			WarningInit();
			GUI_clearscreen(BLACK);
			break;
		case 1:
			subsection =2;
			main_page();
			break;
		case 2:
			subsection++;
			ShowBattVoltINS();
			break;
		case 3:
			subsection++;
			ShowBattCurrentINS();
			break;
		case 4:
			subsection++;
			ShowMileage();
			break;
		case 5:
			subsection++;
			AreaDisplayA();
			break;
		case 6:
			subsection++;
			AreaDisplayB();
			break;
		case 7:
			subsection++;
			AreaDisplayC();
			break;
		default:
			subsection = 2;
			break;
		}
}

void CleanMessageBuffer(void){
	char i;
	
	if(IfClean_ID1810A6A0 >= TIMEOUT_RANGE_MIN){
	    DisableInterrupts;
		memset(&can_signal.ID_1810A6A0,0,sizeof(can_signal.ID_1810A6A0));
		EnableInterrupts;
	}
	if(IfClean_ID1811A6A0 >= TIMEOUT_RANGE_MIN){
	    DisableInterrupts;
		memset(&can_signal.ID_1811A6A0,0,sizeof(can_signal.ID_1811A6A0));
		EnableInterrupts;
	}
	if(IfClean_ID08F200A0 >= TIMEOUT_RANGE_MIN){
		DisableInterrupts;
		memset(&can_signal.ID_08F200A0,0,sizeof(can_signal.ID_08F200A0));
		can_signal.ID_08F200A0.Vehicle_Speed = 0x32;
		EnableInterrupts;
	}
	if(IfClean_ID041000A0 >= TIMEOUT_RANGE_MIN && (warning_show_time==0 || fault_show_time==0)){
		DisableInterrupts;
		memset(&can_signal.ID_041000A0,0,sizeof(can_signal.ID_041000A0));
		FaultInit();
		WarningInit();
		EnableInterrupts;
	}
	if(IfClean_ID0CFF0008 >= TIMEOUT_RANGE_MIN){
		DisableInterrupts;
		memset(&can_signal.ID_0CFF0008,0,sizeof(can_signal.ID_0CFF0008));
		EnableInterrupts;
	}
	
}

