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
EXTERN unsigned char MotorInputCurrentPNSign,MotorTempPNSign,MotorDriverTempPNSign;//�������������ű�־;=1Ϊ��,=0;Ϊ�� ��...
//!<���������Ϣ

EXTERN unsigned int  MotorInputVoltage,MotorInputCurrent;//��������ѹ,���� ��λ:0.1V/bit;0.1A/bit
EXTERN unsigned int  MotorSpeed;//����ٶ� ��λ 1 r/bit
EXTERN unsigned int  MotorTemp,MotorDriverTemp;//����¶�,����������¶� ��λ:1��/bit
//����������
EXTERN unsigned char Version1,Version2,Version3;//�汾��
EXTERN unsigned char FaultCode,FaultLevel,WholeVehicleMode,WholeVehicleLife;//�������,����ȼ�,����ģʽ:55-�Լ�;101-���س����;102-��ӳ����;
																			//���������� LIFE;
EXTERN unsigned char DCDCHeaterTempPNSign,DCACHeaterTempPNSign;
EXTERN unsigned char ContactorStatus1,ContactorStatus2;//����������״̬�� λ����
EXTERN unsigned char DCDCHeaterTemp,DCDCFaultCode;//DC/DC ɢ�����¶� 1��/bit;DC/DC ���ϴ���
EXTERN unsigned char DCACHeaterTemp,DCACFaultCode;
EXTERN unsigned char SwitchStatus1,SwitchStatus2,SwitchStatus3,SwitchStatus4;//����������״̬
EXTERN unsigned char AcceleratorPedal1,AcceleratorPedal2,FootPedal1,FootPedal2;//����̤��1,2;�ƶ�̤��1,2,��λ:1 %/bit
EXTERN unsigned int  P2GndRes,N2GndRes,InsulationWaring;//���˶Եؾ�Ե����,���˶Եؾ�Ե����,������Ե����;��λ:1K��/ bit;
                                                         //����:0xAA���ϸ� 0x55�����ϸ�
//!<��ع���
EXTERN unsigned char BatteryTotalVoltagePNSign,ChargeDischargeCurrentPNSign,MaxAllowChargeCurrentPNSign;
EXTERN unsigned char MaxAllowDischargeCurrentPNSign,MinCellTempPNSign;
EXTERN unsigned char BatteryTotalVoltageUpdateFlag,ChargeDischargeCurrentFlag,BatterySOCUpdateFlag;
EXTERN unsigned int  BatteryTotalVoltage,ChargeDischargeCurrent;//����ܵ�ѹ,��ŵ����; ��λ:0.1V/bit,0.1A/bit;
EXTERN unsigned char BatterySOC;//���ģ�� SOC ��λ:1%/bit
EXTERN unsigned char BatteryStatus1,BatteryStatus2,BatteryStatus3;//�����״̬
EXTERN unsigned int  MaxAllowChargeCurrent,MaxAllowDischargeCurrent;//��ǰ������������,��ǰ�������ŵ���� ��λ:0.1V/bit,0.1A/bit
EXTERN unsigned char BatteryFaultLevel;//﮵��ϵͳ���ϵȼ�
EXTERN unsigned char MinCellTemp;//��������¶� ��λ: 1��/bit
EXTERN unsigned int  PTotalInsulationRes,NTotalInsulationRes;//������Ե����ֵ,�ܸ���Ե����ֵ ��λ:1k��/bit
EXTERN unsigned int  MaxCellVoltage,MinCellVoltage;//������ߵ�ѹ,�������; ��λ:1V/ bit
EXTERN unsigned int  CellVoltage[11];//�����ѹ ��λ: 0.01V/ bit
EXTERN int           CellTemp[11];//�����¶�:1��/bit

EXTERN unsigned int  Readint;//��������ȡ
EXTERN unsigned long KmTotalShort,KmTotalLong,KmTotalLong2,KmTotal_T1;//����� 100m/bit
EXTERN unsigned int  Speed,MotorSpeedReal,VehicleSpeed;
EXTERN unsigned char KmTotalShortFlag,KmTotalLongFlag,WarningP2;

EXTERN volatile unsigned int  Runtime;//ÿ1ms����1
EXTERN volatile unsigned char MsConfig;

EXTERN char MenuPage,subsection;//��ʾ��־
EXTERN unsigned int BatteryAD[40],BatteryAD_Cont;
EXTERN unsigned int  Show_AD;

EXTERN unsigned char Door_Flag,Door_updata;//����״̬
EXTERN unsigned char Select,Select_old;

EXTERN unsigned char PanelUpdateFlag;
EXTERN unsigned char pagination;   //�ӽ����ҳҳ��
EXTERN unsigned int fault_show_time,warning_show_time,soc_low_time,soc_low_time_long;

EXTERN volatile char start_lock;//<!�������������б����жϺ���ѯ�ж��������
EXTERN char OnlineCheckConfig,ExecutiveEraseFlashConfig;//!<can������ر���
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