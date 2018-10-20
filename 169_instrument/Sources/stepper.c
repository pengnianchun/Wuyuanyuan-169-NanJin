
#include "include.h"

/**
 * ����������Ϊ3000��;
 */
#define MAX_STEP_NUM			3000
#define MAX_SHOW_MotorSpeed		5000//��λ:r/min
#define MAX_SHOW_VehicleSpeed   220// ��λkm/h

//!<0-�ұ���;1-�����
unsigned int  sm_steps[2] = {0, 0};
unsigned int  sm_new_value[2] = {0, 0};
unsigned int  sm_old_value[2] = {0, 0};
unsigned char sm_speed[2] = {0, 0};

static volatile char PointerMakeZeroConfig = 0;
void PointerMakeZero(void)
{
    PointerMakeZeroConfig = 1;
}
void ClaerPointerMakeZero(void)
{
    PointerMakeZeroConfig = 0;
}
//!< ����1��ʾָ���ѹ���
unsigned int IsPointerMakeZero(void)
{
	unsigned int t0 = sm_old_value[0];
	unsigned int t1 = sm_old_value[1];

	if ( (t0 == 0 ) && (t1 == 0 ) ) 
	{
		return 1;
	}
	return 0;  
}
void smUpdate0(void) ;
void smUpdate1(void) ;
typedef struct _SPEED_DIVER_TABLE
{
	unsigned int lowerbound;
	unsigned int time;
}
SPEED_DIVER_TABLE;
//�����Խ������У���{0,xx}������
static const SPEED_DIVER_TABLE speedDiverTable[] = 
{
	{480,0},{360,1},{240,2},{180,3},{120,4},{80,5},{60,6},{45,7},
	{30,8},{20,10},{12,15},{6,25},{0,35},    
};
/**
 * @para steps:ָ��ƫ�Ʋ�ֵ
 * @para tab:  ���ݱ�
 * @para tableSize: ���С
 * @return :������Ϊ-1ʱ��ʾ�����ڣ�������ʾ�ٶ�ֵ
 */
static unsigned int InquireSpeed(unsigned int steps,SPEED_DIVER_TABLE *tab,unsigned int tableSize)
{
	int i;
	i = 0;
	while (i < tableSize)
	{
		if (steps < tab[i].lowerbound)
		{
			i++;
		}
		else
		{
			return tab[i].time;
		}
	}
	return -1;//�쳣���
}

void smUpdates()
{
	unsigned int  temp;
	
	if ((1 == PointerMakeZeroConfig)||(J1_1 == 0))
	{
		sm_new_value[0] = 0;
		sm_new_value[1] = 0;
	}
	else
	{
		temp = can_signal.ID_1810A6A0.Batt_SOC_INS;
		if (temp>100)
		{
			temp = 100;
		}
		sm_new_value[0] = temp * 30;

		temp = can_signal.ID_08F200A0.Vehicle_Speed;
		
		if (temp<50)
		{
			temp = 50 - temp;
		}
		else
		{
			temp = temp - 50;
		}
		temp = temp+ (temp+5)/10;
		VehicleSpeed = temp;
		
		sm_new_value[1] = VehicleSpeed * 50 / 3;
		if (sm_new_value[1]>3000)
		{
			sm_new_value[1] = 3000;
		}
		 
	}
	smUpdate0();
	smUpdate1();
}

void smUpdate0(void) {
    if (sm_new_value[0] > sm_old_value[0]) {
        sm_steps[0] = sm_new_value[0] - sm_old_value[0];
        R_DIAL_PLATE_CLOCKWISE; //˳ʱ���ƶ�
    } else {
        sm_steps[0] = sm_old_value[0] - sm_new_value[0];
        R_DIAL_PLATE_ANTICLOCKWISE; //��ʱ���ƶ�
    }
	
	sm_speed[0] = InquireSpeed(sm_steps[0],speedDiverTable,sizeof(speedDiverTable)/sizeof(SPEED_DIVER_TABLE));
}


void smUpdate1(void) {
    if (sm_new_value[1] > sm_old_value[1]) {
        sm_steps[1] = sm_new_value[1] - sm_old_value[1];
        L_DIAL_PLATE_CLOCKWISE; //˳ʱ���ƶ�
    } else {
        sm_steps[1] = sm_old_value[1] - sm_new_value[1];
        L_DIAL_PLATE_ANTICLOCKWISE; //��ʱ���ƶ�
    }
    sm_speed[1] = InquireSpeed(sm_steps[1],speedDiverTable,sizeof(speedDiverTable)/sizeof(SPEED_DIVER_TABLE));
}


void smProcess(void) {
	
	static unsigned char speed[6] = {0, 0, 0, 0, 0, 0};
	if (sm_steps[0] > 0) 
	{
		if (speed[0] >= sm_speed[0]) {
			FSCB = 1;
	        speed[0] = 0;
	        
			if (CWB) {
				sm_old_value[0]++;
			} else {
	                
			    if (sm_old_value[0] > 0) sm_old_value[0]--;
			}
			FSCB = 0;
		} 
		else speed[0]++;
	} 
	else speed[0] = 0;

	if (sm_steps[1] > 0) {
		if (speed[1] >= sm_speed[1]) {
			FSCA = 1;
			speed[1] = 0;
			
			if (CWA) {
				sm_old_value[1]++;
			} else {
				if (sm_old_value[1] > 0) sm_old_value[1]--;
			}
			FSCA = 0;
		}
		else {
			speed[1]++;
		}
	}
	else {
		speed[1] = 0;
	}
	
}
