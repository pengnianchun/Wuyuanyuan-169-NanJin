#ifndef __stepper_h
#define __stepper_h

#define R_DIAL_PLATE_CLOCKWISE		do{CWB = 1;}while(0)
#define R_DIAL_PLATE_ANTICLOCKWISE  do{CWB = 0;}while(0)

#define L_DIAL_PLATE_CLOCKWISE		do{CWA = 1;}while(0)
#define L_DIAL_PLATE_ANTICLOCKWISE  do{CWA = 0;}while(0)

extern void smProcess(void); //1ms�ж�һ��
extern void smUpdates(void);   // �жϺ���
extern unsigned int IsPointerMakeZero(void);
extern void PointerMakeZero(void);
extern void ClaerPointerMakeZero(void);

#endif