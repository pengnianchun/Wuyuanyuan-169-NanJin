#include "can_msg_handle.h"
#include "Global.h"
#include <string.h>
CAN_SIGNAL_TYPE_S can_signal;

void CanReceivedMsgHandle(unsigned long ID,unsigned char* rxdata)
{
	g_power_down_time = 0;
	switch (ID)
	{
		case OnlineCheckID:
			OnlineCheckConfig = 1;
			break;
		case ExcuteAppID:
			ExecutiveEraseFlashConfig = 1;
			break;
		case 0x1810A6A0:
			IfClean_ID1810A6A0 = TIMEOUT_COUNT_CLEAN;
			memcpy(&can_signal.ID_1810A6A0, &rxdata[0], 8);
			break;
		case 0x1811A6A0:
			IfClean_ID1811A6A0 = TIMEOUT_COUNT_CLEAN;
			memcpy(&can_signal.ID_1811A6A0, &rxdata[0], 8);
			break;
		case 0x08F200A0:
			IfClean_ID08F200A0 = TIMEOUT_COUNT_CLEAN;
			memcpy(&can_signal.ID_08F200A0, &rxdata[0], 8);
			break;
		case 0x041000A0:
			IfClean_ID041000A0 = TIMEOUT_COUNT_CLEAN;
			memcpy(&can_signal.ID_041000A0, &rxdata[0], 8);
			break;
		case 0x0CFF0008:
			IfClean_ID0CFF0008 = TIMEOUT_COUNT_CLEAN;
			memcpy(&can_signal.ID_0CFF0008, &rxdata[0], 8);
			break;
	}
}

