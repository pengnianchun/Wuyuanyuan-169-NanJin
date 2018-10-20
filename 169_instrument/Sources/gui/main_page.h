#ifndef MAIN_PAGE_H__
#define MAIN_PAGE_H__

#define PAGE0_PAGINATION0_1 (can_signal.ID_1810A6A0.Batt_Volt_INS[0]+can_signal.ID_1810A6A0.Batt_Volt_INS[1]*256)
#define PAGE0_PAGINATION0_2 (can_signal.ID_1810A6A0.Batt_Current_INS[0]+can_signal.ID_1810A6A0.Batt_Current_INS[1]*256)
#define PAGE0_PAGINATION0_3 (can_signal.ID_08F200A0.Shift)
#define PAGE0_PAGINATION0_4 (can_signal.ID_08F200A0.Driving_Mode)
#define PAGE0_PAGINATION0_5 (100)

#define PAGE0_PAGINATION0_6 (can_signal.ID_0CFF0008.motor_speed[0] + can_signal.ID_0CFF0008.motor_speed[1]*256)
#define PAGE0_PAGINATION0_7 (can_signal.ID_1810A6A0.LED.bit.LED5)
#define PAGE0_PAGINATION0_8 (can_signal.ID_1811A6A0.LED1)
#define PAGE0_PAGINATION0_9 (can_signal.ID_1811A6A0.Remaining_Mil)
#define PAGE0_PAGINATION0_10 (can_signal.ID_1811A6A0.AV_EleCconsume)



extern void ShowMainPage(void);
extern void CleanMessageBuffer(void);

#endif


