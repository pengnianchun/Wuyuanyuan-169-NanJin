#ifndef CAN_MSG_HANDLE_H__
	#define CAN_MSG_HANDLE_H__
#include "Config.h"

typedef union {
  U8 Byte;
  struct {
    U8 bit0         :1;                                     
    U8 bit1         :1;                                     
    U8 bit2         :1;                                      
    U8 bit3         :1;                                       
    U8 bit4         :1;                                       
    U8 bit5         :1;                                       
    U8 bit6         :1;                                       
    U8 bit7         :1;                                       
  } Bits;
} multdata;



typedef struct 
{
	struct {
		U8 Batt_SOC_INS;
		U8 Batt_Current_INS[2];
		U8 Batt_Volt_INS[2];
		U8 Insul_Resistance;
		U8 Cell_Max_Temp;
		union{
			U8 byte;
			struct{
				U8 LED1 : 2;
				U8 LED2 : 1;
				U8 LED3 : 1;
				U8 LED4 : 1;
				U8 LED5 : 1;
				U8 LED6 : 1;
				U8 LED7 : 1;
			}bit;
		}LED;
	} ID_1810A6A0;
	struct{
		U8 MotorDriverFault : 1;
		U8 PowerBatteryTemp : 1;
		U8 TimingCharge		: 1;
		U8 VehicleLowSpeed  : 1;
		U8 DriverPowerLimit : 1;
		U8 :3;
		U8 LED1 : 1;
		U8 LED2 : 1;
		U8 LED3 : 1;
		U8 LED4 : 1;
		U8 LED5 : 1;
		U8 LED6 : 1;
		U8 LED7 : 1;
		U8 LED8 : 1;
		U8 Veh_Limit_Speed;
		U8 Remaining_Mil;
		U8 AV_EleCconsume;
		U8 Ins_EleCconsume;
		U8 :8;
	} ID_1811A6A0;
	/*
	struct{
		U8 
	} ID_08F000A0;
	*/
	struct{
		U8 Vehicle_Mode : 3;
		U8 :5;
		U8 Shift : 4;
		U8 Key_Status : 4;
		U8 Charging_Mode :2;
		U8 OBChargerPlug :1;
		U8 FastChargerPlug :1;
		U8  Driving_Mode :4;
		U8 :8;
		U8 :8;
		U8 Vehicle_Speed;
		U8 Pedal_State;
		U8 Brake_State;
	} ID_08F200A0;	
	struct{
		multdata VCU_Diag_Code1;
		multdata VCU_Diag_Code2;
		multdata VCU_Diag_Code3;
		U8 : 8;
		U8 : 8;
		multdata Warning_Code1;
		multdata Warning_Code2;
		multdata Warning_Code3;
	} ID_041000A0;
	struct{
		U8 motor_speed[2];
		U8 Reserved[6];
	} ID_0CFF0008;
	
}CAN_SIGNAL_TYPE_S;

extern CAN_SIGNAL_TYPE_S can_signal;
extern void CanReceivedMsgHandle(unsigned long ID, unsigned char* rxdata);
extern unsigned char IfClean_ID1810A6A0;
extern unsigned char IfClean_ID1811A6A0;
extern unsigned char IfClean_ID08F200A0;
extern unsigned char IfClean_ID041000A0;
extern unsigned char IfClean_ID0CFF0008;

#endif
