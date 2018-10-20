#ifndef __stepper_h
#define __stepper_h

#define R_DIAL_PLATE_CLOCKWISE		do{CWB = 1;}while(0)
#define R_DIAL_PLATE_ANTICLOCKWISE  do{CWB = 0;}while(0)

#define L_DIAL_PLATE_CLOCKWISE		do{CWA = 1;}while(0)
#define L_DIAL_PLATE_ANTICLOCKWISE  do{CWA = 0;}while(0)

extern void smProcess(void); //1ms中断一次
extern void smUpdates(void);   // 中断函数
extern unsigned int IsPointerMakeZero(void);
extern void PointerMakeZero(void);
extern void ClaerPointerMakeZero(void);

#endif