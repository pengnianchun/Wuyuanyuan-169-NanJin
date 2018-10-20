#ifndef ILI9481_H
#define ILI9481_H
//============================================================
//根据芯片资料定义
#define WINDOW_XADDR_START	0x0050 // Horizontal Start Address Set
#define WINDOW_XADDR_END	0x0051 // Horizontal End Address Set
#define WINDOW_YADDR_START	0x0052 // Vertical Start Address Set
#define WINDOW_YADDR_END	0x0053 // Vertical End Address Set

#define GRAM_XADDR		0x0020 // GRAM Horizontal Address Set
#define GRAM_YADDR		0x0021 // GRAM Vertical Address Set
#define GRAMWR 			0x0022 // memory write
#define GUI_LCM_YMAX 319
#define GUI_LCM_XMAX 239

//=============================================================
//定义TFT彩屏模块接口

#define TFT_CS        PTS_PTS3
#define TFT_RS        PTS_PTS2
#define TFT_WR        PTS_PTS1
#define TFT_RD        PTS_PTS0
#define TFT_RST       PT01AD_PT0AD7

#define LED_EN        PTP_PTP5
//#define TFT_DATA PTT	//数据口

#define LCD_DataPortDDR PORTCD

#define LCD_DataPortH PORTC
#define LCD_DataPortL PORTD

//=============================================================
//函数声明
void ILI9481_initial(void);//TFT初始化
void write_bus(unsigned char CH,unsigned char CL);
void write_cmd(unsigned char CH,unsigned char CL);//写命令
void write_data(unsigned char DH,unsigned char DL);//写数据
void write_data_u16(unsigned int dat);//写16位数据
void write_cmd_data (unsigned char cmd,unsigned int dat);//写命令数据
void LCD_setwindow(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2);//设置窗口
void LCD_setxy(unsigned int x,unsigned int y);//设定当前显示坐标



#endif











