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
CWA=0;CWB=0;倒转
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

#define TIMEOUT_RANGE_MAX 200 //防止U8类型越界
#define TIMEOUT_RANGE_MIN 30  //在100ms一次的轮询里面，代表3s,实测5s左右（要求5s）
#define BEEP_DURATION 50  //蜂鸣器报警时长，实测5s左右（要求5s）
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
修改记录:
  2018-6-8 15:34:11
    1.增加新的图标澹(7个)
    2.增加报警频率，原先频率为5s，现在按协议要求添加频率
    3.增加故障信息
    4.修改页面排版，显示转速，剩余里程添加图标和平均电耗
  2018-6-6 11:21:53:
  	1.修改里程保存策略;
  	2.修改SPI为硬件SPI
  2017-5-5 17:35:11:
  	ADC采样异常: 为adc配置错误,新程序框架对adc采样数据获取方式进行调整;
  	主界面显示方式修改;
  	led异常闪烁为spi读写时序受中断干扰,关中断后已避免
  	增加显示屏开左右前门显示
  	修改里程显示公式
  	看门狗未测试
  2017-5-9 09:32:00
    修改启动时指针归位算法,提高电机速度以降低表盘噪声
    修复can发送速度值错误
  2017-5-12 09:45:35
    增加系统代码(故障代码)显示 
  2017-5-17 18:30:01
    里程保存只在关电时保存,防止烧写次数过度损坏内存单元
  2017-5-22 15:35:40
    修改子菜单反应速度
  2017-5-24 14:34:40
    修改中文,画图驱动,程序未整理  
  2017-5-26 09:26:50
  	添加按键接口， 使得按键底层和上层逻辑解耦和
  2017-5-27 15:27:29
  	将各个page拆分
  2017-6-12 09:14:52
  	大连一汽程序设计,除电池信息外完成;
  2017-6-12 13:20:56
  	重新调整显示内容
  2017-6-14 11:10:59
    前后雾灯临时改用A13 A14接口，改为高控
    PTS7默认为上拉调试时需要注意 使用PERS_PERS7 = 0;来解除上拉
  2017-6-23 10:02:53
    增加自检信息 
  2017-6-26 15:42:53
     1.修改按键处理方式
  	 2.修改dcdc报文，具体需要看到小李代码后处理
  2017-6-27 11:28:08
     1.修改数据解析公式 实际值 = 网络数值 X 分辨率 + 偏移
     2.修改单体电压互差报警逻辑
  2017-6-27 18:04:03
  	 1增加升级功能，修改prm文件防止生成数据丢失
  2017-7-19 16:05:18
     1.堆栈空间不足导致系统异常。memcpy 异常导致看门狗无法复位
  2017-8-10 13:41:20
     1.开机logo的添加
     2.添加某些情况下蜂鸣器报警提示
     3.提示信息和故障信息策略的修改
  2017-9-25 15:15:20
     1.根据样表修改ui和部分逻辑
  ================================================================================
调试记录:
 2017-5-15 10:37:18
 	固定can发送报文前俩个字节为0x08,0x21;测试云端是否能识别;
 	修改默认里程值 --> 客户调试需求
 2017-6-13 09:25:26
 	1.前后雾需要改为高控
 2017-6-27 11:45:20
 	附件报文信息后续需要和客户确认是否发送

*/

#endif

