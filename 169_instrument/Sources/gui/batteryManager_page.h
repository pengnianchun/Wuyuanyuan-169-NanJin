#ifndef BATTERYMANAGER_PAGE_H
#define BATTERYMANAGER_PAGE_H



#define PAGE1_PAGINATION0_1		(can_signal.ID_18FF217B.TotalVol[1] * 256 + can_signal.ID_18FF217B.TotalVol[0])
#define PAGE1_PAGINATION0_2		(can_signal.ID_18FF217B.TotalCurrent[1] *256 + can_signal.ID_18FF217B.TotalCurrent[0])
#define PAGE1_PAGINATION0_3		(can_signal.ID_18FF217B.SOC)
#define PAGE1_PAGINATION0_4		(can_signal.ID_18FF217B.HighVolOfBattCharge[1]*256+can_signal.ID_18FF217B.HighVolOfBattCharge[0])
#define PAGE1_PAGINATION0_5		(can_signal.ID_18FF227B.CarStoreEnergyType)
#define PAGE1_PAGINATION0_6		(can_signal.ID_18FF227B.NumOfHighestVolSubSys)
#define PAGE1_PAGINATION0_7		(can_signal.ID_18FF227B.NumOfLowestVolSubSys)
#define PAGE1_PAGINATION0_8		(can_signal.ID_18FF247B.BattSingleAverageVolValue[1]*256+can_signal.ID_18FF247B.BattSingleAverageVolValue[0])
#define PAGE1_PAGINATION0_9		(can_signal.ID_18FF257B.HighestTempValue)
#define PAGE1_PAGINATION0_a		(can_signal.ID_18FF257B.LowestTempValue)
#define PAGE1_PAGINATION0_b		(can_signal.ID_18FF257B.SubSysAverageTempValue)
#define PAGE1_PAGINATION0_c		(can_signal.ID_18FF257B.CodeOfSubSysHighestTemp)
#define PAGE1_PAGINATION0_d		(can_signal.ID_18FF257B.CodeOfSubSysLowestTemp)
#define PAGE1_PAGINATION0_e		(can_signal.ID_18FF247B.BattSingleVolHighValue[1]*256 + can_signal.ID_18FF247B.BattSingleVolHighValue[0])
#define PAGE1_PAGINATION0_f		(can_signal.ID_18FF247B.BattSingleVolLowValue[1]*256 + can_signal.ID_18FF247B.BattSingleVolLowValue[0])



#define PAGE1_PAGINATION1_1  (can_signal.ID_18FF257B.IndexOfDetectHighTemp)
#define PAGE1_PAGINATION1_2  (can_signal.ID_18FF257B.IndexOfDetectLowTemp)
#define PAGE1_PAGINATION1_3  (can_signal.ID_18FFA97B.TableOfFaultCode)
#define PAGE1_PAGINATION1_4  (can_signal.ID_13CC16B2.HighestChargeVol[1]*256 + can_signal.ID_13CC16B2.HighestChargeVol[0])
#define PAGE1_PAGINATION1_5  (can_signal.ID_13CC16B2.ShiJiYaoQiuChargeCurrent[1]*256 + can_signal.ID_13CC16B2.ShiJiYaoQiuChargeCurrent[0])
#define PAGE1_PAGINATION1_6  (can_signal.ID_13CC16B2.Control)
#define PAGE1_PAGINATION1_7  (can_signal.ID_13CC16B2.SingleNum)
#define PAGE1_PAGINATION1_8  (can_signal.ID_104C1991.DanTiDianYaBaoJingShangXian[1]*256+can_signal.ID_104C1991.DanTiDianYaBaoJingShangXian[0])
#define PAGE1_PAGINATION1_9  (can_signal.ID_104C1991.DanTiDianYaQieDuanShangXian[1]*256 + can_signal.ID_104C1991.DanTiDianYaQieDuanShangXian[0])
#define PAGE1_PAGINATION1_a  (can_signal.ID_104C1991.DanTiDianYaBaoJingXiaXian[1]*256+can_signal.ID_104C1991.DanTiDianYaBaoJingXiaXian[0])
#define PAGE1_PAGINATION1_b  (can_signal.ID_104C1991.DanTiDianYaQieDuanXiaXian[1]*256+can_signal.ID_104C1991.DanTiDianYaQieDuanXiaXian[0])
#define PAGE1_PAGINATION1_c  (can_signal.ID_104C1992.EDingZuiDaChongDianDianLiu[1]*256+can_signal.ID_104C1992.EDingZuiDaChongDianDianLiu[0])
#define PAGE1_PAGINATION1_d  (can_signal.ID_104C1992.EDingZuiDaFangDianDianLiu[1]*256+can_signal.ID_104C1992.EDingZuiDaFangDianDianLiu[0])
#define PAGE1_PAGINATION1_e  (can_signal.ID_104C1992.EDingRongLiang[1]*256+can_signal.ID_104C1992.EDingRongLiang[0])
#define PAGE1_PAGINATION1_f  (can_signal.ID_18FF217B.BMSSysWorkStatus)

#define PAGE1_PAGINATION2_1  (can_signal.ID_18FFA97B.DianJiaReJieChuQiControl)
#define PAGE1_PAGINATION2_2  (can_signal.ID_18FFA97B.ChargeJieChuQiControl)




extern void ShowBatteryManager(void);

#endif
