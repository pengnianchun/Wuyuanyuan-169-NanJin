#ifndef AUXILIARY_PAGE_H
#define AUXILIARY_PAGE_H


#define PAGE4_PAGINATION0_1		(can_signal.ID_18F501F0.QuDongDianJiIndex)
#define PAGE4_PAGINATION0_2		(can_signal.ID_18F501F0.QuDongDianJiStatus)
#define PAGE4_PAGINATION0_3		(can_signal.ID_18F501F0.QuDongDianJiTemp)
#define PAGE4_PAGINATION0_4		(can_signal.ID_18F501F0.QuDongDianJiControlTemp)
#define PAGE4_PAGINATION0_5		(can_signal.ID_18F501F0.DianJiKongZhiQiShuRuDianYaLowBit + can_signal.ID_18F501F0.DianJiKongZhiQiShuRuDianYaHighBit * 256)
#define PAGE4_PAGINATION0_6		(can_signal.ID_18F501F0.DianJiKongZhiQiZhiLiuMuXianDianLiuLowBit + can_signal.ID_18F501F0.DianJiKongZhiQiZhiLiuMuXianDianLiuHighBit*256)
#define PAGE4_PAGINATION0_7		(can_signal.ID_18F502F0.QuDongDianJiZhuanSuLowBit + can_signal.ID_18F502F0.QuDongDianJiZhuanSuHighBit * 256)
#define PAGE4_PAGINATION0_8		(can_signal.ID_18F502F0.QuDongDianJiZhuanJuLowBit + can_signal.ID_18F502F0.QuDongDianJiZhuanJuHighBit * 256)
#define PAGE4_PAGINATION0_9		(can_signal.ID_18F503F0.QuDongDianJiFaultTotalNum)	
#define PAGE4_PAGINATION0_a		(can_signal.ID_18F503F0.QuDongDianJiFaultCodeTable)


extern void ShowAuxiliary(void);

#endif
