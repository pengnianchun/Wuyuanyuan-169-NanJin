#ifndef AIR_PAGE_H
#define AIR_PAGE_H

#define PAGE6_PAGINATION0_1   (can_signal.ID_1801A79A.DianJiRunStatus)
#define PAGE6_PAGINATION0_2   (can_signal.ID_1801A79A.DianJiGongLv)
#define PAGE6_PAGINATION0_3   (can_signal.ID_1801A79A.DianJiWenDu)
#define PAGE6_PAGINATION0_4   (can_signal.ID_1801A79A.DianJiKongZhiQiWenDu)
#define PAGE6_PAGINATION0_5   (can_signal.ID_1801A79A.MuXianDianYaLowBit + can_signal.ID_1801A79A.MuXianDianYaHighBit * 256)

#define PAGE6_PAGINATION1_1	  (can_signal.ID_1801A79B.DianJiRunStatus)
#define PAGE6_PAGINATION1_2   (can_signal.ID_1801A79B.DianJiGongLv)
#define PAGE6_PAGINATION1_3   (can_signal.ID_1801A79B.DianJiWenDu)
#define PAGE6_PAGINATION1_4   (can_signal.ID_1801A79B.DianJiKongZhiQiWenDu)
#define PAGE6_PAGINATION1_5   (can_signal.ID_1801A79B.MuXianDianYaLowBit + can_signal.ID_1801A79B.MuXianDianYaHighBit * 256)
#define PAGE6_PAGINATION1_6   (can_signal.ID_1801A79B.ZhuanSuLowBit + can_signal.ID_1801A79B.ZhuanSuHighBit * 256)

#define PAGE6_PAGINATION2_1   (can_signal.ID_0901A6A7.OverOutputCurrent)
#define PAGE6_PAGINATION2_2   (can_signal.ID_0901A6A7.mode)
#define PAGE6_PAGINATION2_3   (can_signal.ID_0901A6A7.Derating)
#define PAGE6_PAGINATION2_4   (can_signal.ID_0901A6A7.OutputCurrent[0] + can_signal.ID_0901A6A7.OutputCurrent[1]*256)
#define PAGE6_PAGINATION2_5   (can_signal.ID_0901A6A7.Temp)   
#define PAGE6_PAGINATION2_6	  (can_signal.ID_0901A6A7.OutputVoltage)
#define PAGE6_PAGINATION2_7   (can_signal.ID_0901A6A7.InputVoltage)
#define PAGE6_PAGINATION2_8   (can_signal.ID_0901A6A7.Ver)

#define PAGE6_PAGINATION3_1   (can_signal.ID_1801A79D.JueYianDianZu[1]*256+can_signal.ID_1801A79D.JueYianDianZu[0])
#define PAGE6_PAGINATION3_2   (can_signal.ID_1801A79D.ZhengJiJueYuanZuZhi[1]*256 + can_signal.ID_1801A79D.ZhengJiJueYuanZuZhi[0])
#define PAGE6_PAGINATION3_3   (can_signal.ID_1801A79D.FuJiJueYuanZuZhi[1]*256 + can_signal.ID_1801A79D.FuJiJueYuanZuZhi[0])
#define PAGE6_PAGINATION3_4   (can_signal.ID_1801A79D.UintWorkStatus)








extern void ShowAir(void);

#endif
