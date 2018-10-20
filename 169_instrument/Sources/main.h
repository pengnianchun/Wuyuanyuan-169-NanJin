#ifndef __main_h
#define __main_h


#define VERSION		"WP-169v1.0 2018-06-08"
#define VERSIONS_MAJOR	(1u)
#define VERSIONS_MINOR	(0u)
#define CAN_BL_APP		(1u)





#define BEEP                       PT01AD_PT0AD4

#define SPI_CSPCA    PORTB_PB0
#define SPI_CS25     PTJ_PTJ3
#define MPSCK        PTJ_PTJ2
#define MPMOSI       PTJ_PTJ1
#define MPMISO       PTIJ_PTIJ0  


#define HEF4021_CLOCK    PTJ_PTJ6 
#define HEF4021_PL       PTJ_PTJ7 
#define HEF4021_MISO     PTIJ_PTIJ4 


#define KEY_1                PT01AD_PT0AD2
#define KEY_2                PT01AD_PT1AD3
#define KEY_3                PTT_PTT7
#define KEY_4                PTT_PTT6


#define J1_27                PTP_PTP3
#define J1_32                PTP_PTP6             
#define J1_33                PORTB_PB5
#define J1_34                PORTB_PB6
#define J1_35                PTT_PTT1
#define J1_36                PTT_PTT0

#define J1_1                 PORTAB_PB2
#define U1_26                PORTAB_PB1

#define POW_EN				 do{PORTAB_PB1 = 1;}while(0)
#define POW_DIS				 do{PORTAB_PB1 = 0;}while(0)

/*
CWA=0;CWB=0;��ת
*/
#define CWA                 PT01AD_PT1AD0
#define CWB                 PT01AD_PT0AD1
#define FSCB                PT01AD_PT1AD2
#define FSCA                PT01AD_PT0AD0

//#define TM_ON  {TSCR2_PR=2; TSCR2_TOI=1; TSCR1_TEN=1;}
//#define TM_OFF {TSCR2_PR=2; TSCR2_TOI=1; TSCR1_TEN=0;}

#define AlarmSong(on,off,C)			do{if(C<beep_info.temp){break;}beep_info.time_on = on;beep_info.time_off = off;beep_info.cont = C;}while(0)

/* ID Definition */
/* #define ST_ID_100 0x20000000    Standard Id 0x100 formatted to be loaded 
                                 * in IDRx Registers in Tx Buffer
                                 */
                                 
#define MCU_SLEEP_DELAY_TIME (1000)
#define CAN_EN				PORTAB_PA3
#define CAN_BTS             PTP_PTP3
#define CAN_ERR             PTP_PTP6

/* Acceptance Code Definitions */ 
#define ACC_CODE_ID100 0x8000
#define ACC_CODE_ID100_HIGH ((ACC_CODE_ID100&0xFF00)>>8)
#define ACC_CODE_ID100_LOW (ACC_CODE_ID100&0x00FF)


/* Mask Code Definitions */
#define MASK_CODE_ST_ID 0x0000
#define MASK_CODE_ST_ID_HIGH ((MASK_CODE_ST_ID&0xFF00)>>8)
#define MASK_CODE_ST_ID_LOW (MASK_CODE_ST_ID&0xFF)

/* Error Flags Definition */
#define NO_ERR 0x00
#define ERR_BUFFER_FULL 0x80 

#define TIMEOUT_RANGE_MAX 200 //��ֹU8����Խ��
#define TIMEOUT_RANGE_MIN 30  //��100msһ�ε���ѯ���棬����3s,ʵ��5s���ң�Ҫ��5s��
#define BEEP_DURATION 50  //����������ʱ����ʵ��5s���ң�Ҫ��5s��
#define TIMEOUT_COUNT_CLEAN 0

extern void ShowControl();
extern unsigned char ReadH,ReadL;
extern unsigned char  BatteryStatus1,BatteryStatus2,BatteryStatus3;
char* itoa(int value, char* string, int radix) ;
void Hex2String(unsigned char hex,unsigned char *p);

unsigned char read_min(void);

void AD_Init(void) ;
unsigned int ReadATD();

  
unsigned char CAN0SendFrame(unsigned long id, unsigned char priority, unsigned char length, unsigned char *txdata );
void CANInit(void);

void main_page_update(void);
void main_page(void);
void menu_page(void);
void control_page(void);
void control_page_update(void);
void auxiliary_page(void);
void auxiliary_page_update(void);
void Drive_page(void);
void Drive_page_update(void);
void Battery_Manager_page(unsigned char *name,unsigned char **line);
void Battery_Manager_page_update(void);
void Air_page(void);

void Battery_Info_page(void);
void PageHandle(void);

void Door_FL(unsigned char onoff);
void Door_RL(unsigned char onoff);
void Door_FR(unsigned char onoff);
void Door_RR(unsigned char onoff);
void Door_R(unsigned char onoff);




/*********************************************************************************/
/*
�޸ļ�¼:
  2018-6-8 15:34:11
    1.�����µ�ͼ���(7��)
    2.���ӱ���Ƶ�ʣ�ԭ��Ƶ��Ϊ5s�����ڰ�Э��Ҫ�����Ƶ��
    3.���ӹ�����Ϣ
    4.�޸�ҳ���Ű棬��ʾת�٣�ʣ��������ͼ���ƽ�����
  2018-6-6 11:21:53:
  	1.�޸���̱������;
  	2.�޸�SPIΪӲ��SPI
  2017-5-5 17:35:11:
  	ADC�����쳣: Ϊadc���ô���,�³����ܶ�adc�������ݻ�ȡ��ʽ���е���;
  	��������ʾ��ʽ�޸�;
  	led�쳣��˸Ϊspi��дʱ�����жϸ���,���жϺ��ѱ���
  	������ʾ��������ǰ����ʾ
  	�޸������ʾ��ʽ
  	���Ź�δ����
  2017-5-9 09:32:00
    �޸�����ʱָ���λ�㷨,��ߵ���ٶ��Խ��ͱ�������
    �޸�can�����ٶ�ֵ����
  2017-5-12 09:45:35
    ����ϵͳ����(���ϴ���)��ʾ 
  2017-5-17 18:30:01
    ��̱���ֻ�ڹص�ʱ����,��ֹ��д�����������ڴ浥Ԫ
  2017-5-22 15:35:40
    �޸��Ӳ˵���Ӧ�ٶ�
  2017-5-24 14:34:40
    �޸�����,��ͼ����,����δ����  
  2017-5-26 09:26:50
  	��Ӱ����ӿڣ� ʹ�ð����ײ���ϲ��߼������
  2017-5-27 15:27:29
  	������page���
  2017-6-12 09:14:52
  	����һ���������,�������Ϣ�����;
  2017-6-12 13:20:56
  	���µ�����ʾ����
  2017-6-14 11:10:59
    ǰ�������ʱ����A13 A14�ӿڣ���Ϊ�߿�
    PTS7Ĭ��Ϊ��������ʱ��Ҫע�� ʹ��PERS_PERS7 = 0;���������
  2017-6-23 10:02:53
    �����Լ���Ϣ 
  2017-6-26 15:42:53
     1.�޸İ�������ʽ
  	 2.�޸�dcdc���ģ�������Ҫ����С��������
  2017-6-27 11:28:08
     1.�޸����ݽ�����ʽ ʵ��ֵ = ������ֵ X �ֱ��� + ƫ��
     2.�޸ĵ����ѹ������߼�
  2017-6-27 18:04:03
  	 1�����������ܣ��޸�prm�ļ���ֹ�������ݶ�ʧ
  2017-7-19 16:05:18
     1.��ջ�ռ䲻�㵼��ϵͳ�쳣��memcpy �쳣���¿��Ź��޷���λ
  2017-8-10 13:41:20
     1.����logo�����
     2.���ĳЩ����·�����������ʾ
     3.��ʾ��Ϣ�͹�����Ϣ���Ե��޸�
  2017-9-25 15:15:20
     1.���������޸�ui�Ͳ����߼�
  ================================================================================
���Լ�¼:
 2017-5-15 10:37:18
 	�̶�can���ͱ���ǰ�����ֽ�Ϊ0x08,0x21;�����ƶ��Ƿ���ʶ��;
 	�޸�Ĭ�����ֵ --> �ͻ���������
 2017-6-13 09:25:26
 	1.ǰ������Ҫ��Ϊ�߿�
 2017-6-27 11:45:20
 	����������Ϣ������Ҫ�Ϳͻ�ȷ���Ƿ���

*/

#endif

