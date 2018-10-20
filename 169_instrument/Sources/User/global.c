#define GLOBAL_EXTERN
#include <stdio.h>
#include <string.h>
#include "global.h"
#include "can_msg_handle.h"
#include "fault.h"

void GlobalInit(void)
{
	alarm_msg = 0;
	MotorInputVoltage = 0;
	MotorInputCurrent = 0;
	MotorSpeed = 0;
	MotorTemp = 0;
	MotorDriverTemp = 0;
	FaultCode = 0;
	FaultLevel = 0;
	WholeVehicleMode = 0;
	BatteryTotalVoltagePNSign=1;
	BatteryTotalVoltageUpdateFlag = 1;
	ChargeDischargeCurrentPNSign = 1;
	ChargeDischargeCurrentFlag = 1;
	BatterySOCUpdateFlag=1;
	memset(CellVoltage,0,sizeof(CellVoltage));
	g_pulse.time_on = 0;
	Select=0,Select_old=0;
	memset(&can_signal,0,sizeof(can_signal));
}

