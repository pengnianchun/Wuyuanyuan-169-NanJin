#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "config.h"
#include "panel.h"
#include "global.h"
#include "Show.h"
#include "stepper.h"
#include "key.h"
#include "include.h"



static const char _AppcheckString[32]  @0x4000= "S12G128 Bingo";


unsigned char txbuff[8] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

unsigned long int ST_ID_100=0x0C19A7A1,SendID=0x0C19A7A1;
//  00001100 00011001 10100111 10100001--- 0x0C19A7A1
//  01100000 11001011 01001111 01000010


unsigned char ReadH,ReadL;
unsigned long  KmTotal;
unsigned char IfClean_ID1810A6A0 = TIMEOUT_RANGE_MIN;
unsigned char IfClean_ID1811A6A0 = TIMEOUT_RANGE_MIN;
unsigned char IfClean_ID08F200A0 = TIMEOUT_RANGE_MIN;
unsigned char IfClean_ID041000A0 = TIMEOUT_RANGE_MIN;
unsigned char IfClean_ID0CFF0008 = TIMEOUT_RANGE_MIN;



void MCU_init(void); /* Device initialization function declaration */

static int Task = 0;
#define TASK_IDLE		0
#define TASK_RUN		1
#define TASK_DORMANT	2


#define SetTaskMode(mod)	do{Task = mod;}while(0)
                             
static void InputScan(void)
{
	if (J1_1 == 0)
	{
		return;
	}
	Readint=SPI2_byte_read();//~{6AH!?*9XA?~}
	ReadH=Readint/256;
	ReadL=Readint%256;
	PanelUpdateFlag = 1;
}
static void CANSend()
{
	unsigned int temp;
	volatile unsigned long u32temp;
	unsigned int u16temp1,u16temp2;
	static unsigned char life = 0;
	tREG08 u8reg;        
	memset(txbuff,0x00,sizeof(txbuff));

	txbuff[0] = life++;

	u8reg.bit._0 = L_PANEL_IN1()?1:0;
	u8reg.bit._1 = 0;
	u8reg.bit._2 = L_PANEL_IN5()?1:0;
	u8reg.bit._3 = GetDoorFlag()?1:0;
	u8reg.bit._4 = R_PANEL_IN4()?1:0;
	u8reg.bit._5 = 0;
	u8reg.bit._6 = 0;
	u8reg.bit._7 = !L_PANEL_IN3();
	txbuff[1] = u8reg.byte;
	u32temp = KmTotalLong;
	u32temp /=20;
	txbuff[2] = u32temp &0xff;
	u32temp /=256;
	txbuff[3] = u32temp &0xff;
	u32temp /=256;
	txbuff[4] = u32temp &0xff;
	if((J1_1==1) || (can_signal.ID_1810A6A0.LED.byte == 0x06)) {
	    CAN0SendFrame((0xC20A0A6UL), 0x03, sizeof(txbuff), txbuff);
	}


}
void ExecutiveCheckHandle(void)
{
	unsigned char data[8];
	data[0] = VERSIONS_MAJOR>>8;
	data[1] = VERSIONS_MAJOR;
	data[2] = VERSIONS_MINOR>>8;
	data[3] = VERSIONS_MINOR;
	data[4] = 0;
	data[5] = 0;
	data[6] = 0;
	data[7] = CAN_BL_APP;
	CAN0SendFrame(OnlineCheckID,0x03,8,data); 
}


/**
 * ~{BVQ/~}
 */

void Polling(void)
{
	unsigned int u16temp;
	static char cont_1MS=0,cont_10MS=0,cont_100MS = 0;
	if (1 == MsConfig)
	{
		MsConfig = 0;
		cont_1MS++;
		if (cont_1MS>=10){
			cont_10MS++;
			cont_1MS = 0;
			if (cont_10MS>=10){
				cont_10MS = 0;
				cont_100MS++;
				IfClean_ID1810A6A0++;
				IfClean_ID1811A6A0++;
				IfClean_ID08F200A0++;
				IfClean_ID041000A0++;
				IfClean_ID0CFF0008++;
				if(IfClean_ID1810A6A0 > TIMEOUT_RANGE_MAX)
					IfClean_ID1810A6A0= TIMEOUT_RANGE_MIN;
				if(IfClean_ID1811A6A0 > TIMEOUT_RANGE_MAX)
					IfClean_ID1811A6A0 = TIMEOUT_RANGE_MIN;
				if(IfClean_ID08F200A0 > TIMEOUT_RANGE_MAX)
					IfClean_ID08F200A0 = TIMEOUT_RANGE_MIN;
				if(IfClean_ID041000A0 > TIMEOUT_RANGE_MAX)
					IfClean_ID041000A0 = TIMEOUT_RANGE_MIN;
				if(IfClean_ID0CFF0008 > TIMEOUT_RANGE_MAX)
					IfClean_ID0CFF0008 = TIMEOUT_RANGE_MIN;
				if (cont_100MS>=10)
				{
					cont_100MS = 0;
				}
			}
		}
		switch(cont_1MS){
			//10ms÷¥––“Ï≥£
			case 0:
				ATDCTL5 = 0x01;    //∆Ù∂Ø≤…—˘
				break;
			case 1:
				if (BatteryAD_Cont<40){
					if(ATDSTAT0_SCF){
					BatteryAD[BatteryAD_Cont++] = ATDDR0L;
					}
				}            
				break;
			case 2:
				DetectKeyEvent();
				break;
			case 3:
				if (g_safety_belt == 1)
				{
					if (VehicleSpeed >= 20)
					{
						g_safety_belt_config = 1;
					}
				}
				else
				{
					g_safety_belt_config = 0;
				}
				break;
			case 4:
				//!~{<FKc35KY~}

				if(OnlineCheckConfig == 1)
				{
					OnlineCheckConfig = 0;
					ExecutiveCheckHandle();
				}
				break;
			case 5:
				DisableInterrupts;
				InputScan();
				EnableInterrupts;
				break;
			case 6:
				g_power_down_time++;
				if (g_power_down_time>=MCU_SLEEP_DELAY_TIME)
				{
					g_power_down_time = MCU_SLEEP_DELAY_TIME;
				}
				break;
			case 7:
				RegisterWarning();
				break;
			case 8:
				CleanMessageBuffer();
				break;
			default:
				switch(cont_10MS){
					//100ms÷¥––“ª¥Œ
					case 0:AlarmBeep();break;
					case 1:
						//!<∆µ¬ º∆À„
						{
							u16temp = VehicleSpeed;
							u16temp = u16temp * 15/10;
							if (u16temp== 0)
							{
								g_pulse.time_on = 0;
								g_pulse.time_off = 0;
							}
							else
							{
								g_pulse.time_off = 1000 / u16temp;
								g_pulse.time_on = g_pulse.time_off/2;
							}
							
						}
						break;
					case 2:
						CANSend();
						Warninganalysis();
						break;
					case 3:
						RegisterFaul();
						break;
					case 4:
						if((can_signal.ID_08F200A0.Shift) == 0x05)
						{
							PORTA_PA1 = 1;
						}
						else
						{
							PORTA_PA1 = 0;
						}
						break;
					case 5:AlarmBeep();break;
					case 6:
						if (warning_show_time)
						{
							warning_show_time--;
						}
						if (fault_show_time)
						{
							fault_show_time--;
						}
						if (soc_low_time)
						{
							soc_low_time--;
						}
						{
							u16temp = VehicleSpeed;
							u16temp = u16temp * 15/10;
							if (u16temp== 0)
							{
								g_pulse.time_on = 0;
								g_pulse.time_off = 0;
							}
							else
							{
								g_pulse.time_off = 1000 / u16temp;
								g_pulse.time_on = g_pulse.time_off/2;
							}
							
						}
						break;
					case 7:
						CANSend();
						Warninganalysis();
						break;
					case 8:
						RegisterFaul();
						break;
					default:
						switch(cont_100MS)
						{
							case 0:
								if (g_safety_belt_config)
								{
									if (g_safety_belt_timeout == 0)
									{
										g_safety_belt_timeout = 30;
										AlarmSong(100, 200, 10);
									}
									else
									{
										g_safety_belt_timeout--;
									}
								}
								else
								{
									g_safety_belt_timeout = 0;
								}
								break;
							case 1:
								break;
							case 2:
								break;
							case 3: panel_pulsation = !panel_pulsation;break;
							case 4:
								if (soc_low_time_long)
								{
									soc_low_time_long--;
								}
								break;
							case 5:break;
							case 6:break;
							case 7:break;
							case 8:panel_pulsation = !panel_pulsation;break;
							default:
								break;
						}
						break;
				}          
				break;			
		}
	}
}

/**
 * ~{HNNqW4L,~}:
 * 		1.TASK_IDLE:~{4&@mIO5gFt6/O`9XJBOn~}.~{VwR*0|@(3d5g;=PQ:MU}3#;=PQ~},~{3d5g;=PQ2;=xPPFdK{2YWw~}
 */

typedef enum
{
	DIRECTIO_CLOCKWISE=0,
	DIRECTIO_ANTICLOCKWISE,
}STEPPER_DIRECTION_TYPE;//!<‘À––∑ΩœÚ


#define MAX_STEP_NUM			3000
#define SELF_SPEED              (150)

//!<speed_max = 150
void SetPointerStep(STEPPER_DIRECTION_TYPE direction,U16 speed_max)
{
	U16 step;
	U16 speed,temp;
	if (DIRECTIO_CLOCKWISE == direction)
	{
		
		L_DIAL_PLATE_CLOCKWISE;
		R_DIAL_PLATE_CLOCKWISE;
	}
	else
	{
		L_DIAL_PLATE_ANTICLOCKWISE;
		R_DIAL_PLATE_ANTICLOCKWISE;
	}
	speed = 0;
	for (step = 0;step<MAX_STEP_NUM;step++)
	{
		FSCA=1;
		FSCB=1;
		delay_nus(200 - speed);
		FSCA=0;
		FSCB=0;
		delay_nus(200 - speed);
		temp = MAX_STEP_NUM - step;
		
		if (temp>speed_max)
		{
			temp = speed_max;
		}
		if (speed < temp)
		{
			speed++;
		}
		else
		{
			speed = temp;
		}
	}
}

static unsigned char reset = 0;

void main(void)
{
	unsigned int temp,temp2;
	IVBR = 0x7FU;    //÷ÿ∂®œÚ
	CPMUFLG_PORF = 1;//«Â≥˛…œµÁ∏¥Œª±Í÷æ;
	GlobalInit();
	MCU_init(); /* call Device Initialization */
	spi_init();
	DisableInterrupts;
	PanelInit();
	LED_EN=0;
	POW_EN;
	CANInit();
	AD_Init();
	
	LoadInfo(); 
	if (J1_1 != 0)
	{
		SetPointerStep(DIRECTIO_ANTICLOCKWISE,SELF_SPEED);//!<πÈ¡„
	}
	SetTaskMode(TASK_IDLE);
	ILI9481_initial();
	g_power_down_time = 0;
	can_signal.ID_08F200A0.Vehicle_Speed = 50;
	can_signal.ID_1810A6A0.Batt_Current_INS[0] = 0XA0;
	can_signal.ID_1810A6A0.Batt_Current_INS[1] = 0X0F;
	reset = 1;
	POW_EN;
	for(;;)
	{
		switch (Task){
			case TASK_IDLE:
				{
					LED_EN=0;
					delay_1ms();//ƒ⁄≤ø”–Œππ∑
					if (J1_1==1){
						//!<Todo:’˝≥£…œµÁœ‡πÿ≥ı ºªØ
						
						InputScan();
						start_lock = 1;//!<±‹√‚÷–∂œ¥¶¿Ìio◊¥Ã¨
						BEEP = 1;
						PanelTest();
						
						if (J1_1==1)//!<∑¿÷π¥À ±∂œµÁ∆¡ƒª…¡À∏
						{
						    
					    	POW_EN;
						}
						else
						{
							SetTaskMode(TASK_DORMANT);
							break;
						}
						start_lock = 0;
						if (reset == 1)
						{
							reset = 0;

                            DisableInterrupts;
							SetPointerStep(DIRECTIO_CLOCKWISE,SELF_SPEED);
							BEEP = 0;
							GUI_clearscreen(BLACK);
							main_page();
							delay_nms(100);
							MenuPage = 0;
							subsection=2;
							SetPointerStep(DIRECTIO_ANTICLOCKWISE,SELF_SPEED);
						}
						else
						{
							BEEP = 0;
							GUI_clearscreen(BLACK);
							main_page();
							MenuPage = 0;
							subsection=2;
						}
						//!<◊‘ºÏΩ· ¯
						EnableInterrupts;
						POW_EN;
						SetTaskMode(TASK_RUN);
						InputScan();
						WarningInit();
						FaultInit();
					
						if (J1_1 == 0)//!<∑¿÷π¥À ±∂œµÁ∆¡ƒª…¡À∏
						{
							SetTaskMode(TASK_DORMANT);
							break;
						}
						LED_EN=1;
						LIGHT_14White = 1;
						PORTA_PA2 = 1;//!<œµÕ≥◊º±∏ÕÍ±œ
						ClaerPointerMakeZero();
					}
					else{
						EnableInterrupts;
						Polling();
						if (g_power_down_time >= MCU_SLEEP_DELAY_TIME)
						{
							U16 time;
							can_chip_mode_switch(GO_TO_SLEEP_MODE);
							POW_EN;
							LED_EN=0; 
							time = Runtime;
							
							while((Runtime - time)<500)//!<µ»¥˝500ms
							{
								Polling();
							}
							g_power_down_time = MCU_SLEEP_DELAY_TIME;
							if (PTP_PTP6 == 1)
							{
								POW_DIS;
								delay_nms(100);
							}
							else
							{
								g_power_down_time = 0;
								can_chip_mode_switch(NORMAL_MODE);	//!<“Ï≥£
							}
						}	
						_FEED_COP();
					}
				}            
				
				break;
			case TASK_RUN:
				LED_EN=1;
				if(J1_1==0)//ºÏ≤‚ªΩ–—–≈∫≈
				{
					SetTaskMode(TASK_DORMANT);
					break;
				}
				Polling();				
				//FaultMenu();
				//±£¥Ê ˝æ›Â?
				app_flash_task();
				ShowMenu[MenuPage]();
				_FEED_COP();

				break;
			case TASK_DORMANT:
				PointerMakeZero();//÷∏’Î«Â¡„;
				PanelInit();
				LIGHT_14White = 0;
				LED_EN = 0;
				BEEP = 0;
				start_lock = 1;
				temp = Runtime;
				do{
					temp2 = IsPointerMakeZero();
					if ((Runtime-temp)>5000)
					{
						//÷∏’ÎπÈ¡„≥¨ ±
						break;
					}
					_FEED_COP();
					if(J1_1==1){
						goto wake_up;
					}
				}while(temp2 == 0);
				DisableInterrupts;
				PORTA_PA2 = 0;
				GlobalInit();
				app_flash_save();
wake_up:
				g_power_down_time = 0;
				ClaerPointerMakeZero();
				SetTaskMode(TASK_IDLE);

			default:
				break;
				
				
		}
		if (ExecutiveEraseFlashConfig == 1)
		{
			ExecutiveEraseFlashConfig = 0;
			PORTA_PA2 = 0;//!<œµÕ≥◊º±∏ÕÍ±œ
			//!< ’µΩ∏¸–¬≥Ã–Ú√¸¡Ó
			DisableInterrupts;
			LIGHT_14White = 0;
			LED_EN = 0;
			PanelInit();
			/* ### Init_API init code */
			/* CPMUAPICTL: APICLK=0,APIES=0,APIEA=0,APIFE=0,APIE=0,APIF=0 */
			CPMUAPICTL = 0x00U;
			/* CPMUAPIR: APIR15=1,APIR14=1,APIR13=1,APIR12=0,APIR11=1,APIR10=0,APIR9=1,APIR8=0,APIR7=0,APIR6=1,APIR5=1,APIR4=0,APIR3=0,APIR2=0,APIR1=0,APIR0=0 */
			CPMUAPIR = 0x00U; //Period = 2*(APIR[15:0] + 1) * Bus Clock period =  0.005s
			/* CPMUACLKTR: ACLKTR5=0,ACLKTR4=0,ACLKTR3=0,ACLKTR2=0,ACLKTR1=0,ACLKTR0=0 */
			CPMUACLKTR = 0x00U;
			/* CPMUAPICTL: APICLK=1,APIE=1,APIF=1 */
			CPMUAPICTL |= (unsigned char) 0x00U;
			/* CPMUAPICTL: APIFE=1 */
			CPMUAPICTL |= (unsigned char) 0x00U;
			asm JMP 0xf000
		}
	}
	
}


void AD_Init(void)
{
	//8¬∑Õ®µ¿


	 ATDCTL2 = 0x40;  //∆Ù∂ØA/Dƒ£øÈ,øÏÀŸ«Â¡„,Ω˚÷π÷–∂œ
	 ATDCTL1_SRES=0;  //—°”√8Œªƒ£ ˝◊™ªª
	 ATDCTL3 = 0x88;   //√ø¥Œ÷ª◊™ªª“ª∏ˆÕ®µ¿
	 ATDCTL4 = 0xff;   //ADƒ£øÈ ±÷”∆µ¬ Œ™2MHz
	 ATDDIEN=0xFFFF;
	 ATDDIENL_IEN1=0;
	 ATDCTL5 = 0x01;    //∆Ù∂Ø◊™ªªAD01

}

unsigned int ReadATD()
{
	unsigned int ad = 0;        //¥Ê∑≈≤…ºØµÁ—π÷µ
	ATDCTL5 = 0x01;    //◊™ªªAD01
    while(!ATDSTAT0_SCF);
    ad = ATDDR0L;
	return ad;
}

#if 0

static int Beep(struct pt *pt)
{

	PT_BEGIN(pt);

	while(1)
	{
		Task4_delay=0;
		PT_WAIT_UNTIL(pt, (Task4_delay++>10000)== 1);

	}
	PT_END(pt);
}


#endif




