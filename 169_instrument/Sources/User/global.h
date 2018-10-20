#ifndef GLOBAL_H_
  #define GLOBAL_H_

#include "show_string.h"
#include "Typedef.h"

#ifdef GLOBAL_EXTERN
#define EXTERN
#else
#define EXTERN extern
#endif
typedef struct 
{
	unsigned int cont;
	unsigned int time_on;
	unsigned int time_off;
	unsigned int temp;
}
BEEP_INFO;
typedef struct 
{
	unsigned int time_on;
	unsigned int time_off;
}
PulseWidth;
EXTERN unsigned char MotorInputCurrentPNSign,MotorTempPNSign,MotorDriverTempPNSign;//电机输入电流符号标志;=1为正,=0;为负 略...
//!<电机驱动信息

EXTERN unsigned int  MotorInputVoltage,MotorInputCurrent;//电机输入电压,电流 单位:0.1V/bit;0.1A/bit
EXTERN unsigned int  MotorSpeed;//电机速度 单位 1 r/bit
EXTERN unsigned int  MotorTemp,MotorDriverTemp;//电机温度,电机控制器温度 单位:1℃/bit
//整车控制器
EXTERN unsigned char Version1,Version2,Version3;//版本号
EXTERN unsigned char FaultCode,FaultLevel,WholeVehicleMode,WholeVehicleLife;//错误代码,错误等级,整车模式:55-自检;101-车载充电器;102-外接充电器;
																			//整车控制器 LIFE;
EXTERN unsigned char DCDCHeaterTempPNSign,DCACHeaterTempPNSign;
EXTERN unsigned char ContactorStatus1,ContactorStatus2;//整车控制器状态量 位驱动
EXTERN unsigned char DCDCHeaterTemp,DCDCFaultCode;//DC/DC 散热器温度 1℃/bit;DC/DC 故障代码
EXTERN unsigned char DCACHeaterTemp,DCACFaultCode;
EXTERN unsigned char SwitchStatus1,SwitchStatus2,SwitchStatus3,SwitchStatus4;//整车控制器状态
EXTERN unsigned char AcceleratorPedal1,AcceleratorPedal2,FootPedal1,FootPedal2;//加速踏板1,2;制动踏板1,2,单位:1 %/bit
EXTERN unsigned int  P2GndRes,N2GndRes,InsulationWaring;//正端对地绝缘电阻,负端对地绝缘电阻,整车绝缘报警;单位:1KΩ/ bit;
                                                         //报警:0xAA：合格， 0x55：不合格
//!<电池管理
EXTERN unsigned char BatteryTotalVoltagePNSign,ChargeDischargeCurrentPNSign,MaxAllowChargeCurrentPNSign;
EXTERN unsigned char MaxAllowDischargeCurrentPNSign,MinCellTempPNSign;
EXTERN unsigned char BatteryTotalVoltageUpdateFlag,ChargeDischargeCurrentFlag,BatterySOCUpdateFlag;
EXTERN unsigned int  BatteryTotalVoltage,ChargeDischargeCurrent;//电池总电压,充放电电流; 单位:0.1V/bit,0.1A/bit;
EXTERN unsigned char BatterySOC;//电池模块 SOC 单位:1%/bit
EXTERN unsigned char BatteryStatus1,BatteryStatus2,BatteryStatus3;//电池组状态
EXTERN unsigned int  MaxAllowChargeCurrent,MaxAllowDischargeCurrent;//当前最大允许充电电流,当前最大允许放电电流 单位:0.1V/bit,0.1A/bit
EXTERN unsigned char BatteryFaultLevel;//锂电池系统故障等级
EXTERN unsigned char MinCellTemp;//单体最高温度 单位: 1℃/bit
EXTERN unsigned int  PTotalInsulationRes,NTotalInsulationRes;//总正绝缘电阻值,总负绝缘电阻值 单位:1kΩ/bit
EXTERN unsigned int  MaxCellVoltage,MinCellVoltage;//单体最高电压,单体最低; 单位:1V/ bit
EXTERN unsigned int  CellVoltage[11];//单体电压 单位: 0.01V/ bit
EXTERN int           CellTemp[11];//单体温度:1℃/bit

EXTERN unsigned int  Readint;//开关量读取
EXTERN unsigned long KmTotalShort,KmTotalLong,KmTotalLong2,KmTotal_T1;//里程数 100m/bit
EXTERN unsigned int  Speed,MotorSpeedReal,VehicleSpeed;
EXTERN unsigned char KmTotalShortFlag,KmTotalLongFlag,WarningP2;

EXTERN volatile unsigned int  Runtime;//每1ms自增1
EXTERN volatile unsigned char MsConfig;

EXTERN char MenuPage,subsection;//显示标志
EXTERN unsigned int BatteryAD[40],BatteryAD_Cont;
EXTERN unsigned int  Show_AD;

EXTERN unsigned char Door_Flag,Door_updata;//车门状态
EXTERN unsigned char Select,Select_old;

EXTERN unsigned char PanelUpdateFlag;
EXTERN unsigned char pagination;   //子界面分页页码
EXTERN unsigned int fault_show_time,warning_show_time,soc_low_time,soc_low_time_long;

EXTERN volatile char start_lock;//<!程序启动过程中避免中断和轮询中对外设操作
EXTERN char OnlineCheckConfig,ExecutiveEraseFlashConfig;//!<can升级相关变量
EXTERN BEEP_INFO beep_info;
EXTERN unsigned char alarm_msg;
EXTERN char panel_reserved;
EXTERN char panel_pulsation;
EXTERN char ready_flag;
EXTERN PulseWidth g_pulse;
EXTERN char g_reset_mcu;
EXTERN char g_safety_belt;
EXTERN char g_safety_belt_config;
EXTERN char g_safety_belt_timeout;
EXTERN void GlobalInit(void);
EXTERN unsigned char s_fault_cont[24];
EXTERN U8 fault_config;
EXTERN volatile unsigned int  g_power_down_time;
#endif