#ifndef GUI_H
#define GUI_H



/*GUI函数*/
void GUI_clearscreen(unsigned int b_color);//清屏
void GUI_clearscreen_part1(unsigned int b_color);
void GUI_Point(unsigned int x, unsigned int y, unsigned int color);//画点
void GUI_sprintf_chartobit(unsigned int x, unsigned int y,unsigned char dat, unsigned int color,unsigned int b_color);//无符号字符型数以二进制形式显示
void GUI_sprintf_chartohex(unsigned int x, unsigned int y,unsigned char dat, unsigned int color,unsigned int b_color);//无符号字符型数以十六进制形式显示
void GUI_sprintf_chartodec(unsigned int x,unsigned int y,unsigned char dat,unsigned int color,unsigned int b_color);//无符号字符型数以十进制形式显示
void GUI_sprintf_nu(unsigned int x, unsigned int y,unsigned char nu, unsigned int color,unsigned int b_color);//显示1位16进制数
void GUI_HLine(unsigned int x, unsigned int y, unsigned char length, unsigned int color);//画横线
void GUI_RLine(unsigned int x, unsigned int y, unsigned int high, unsigned int color);//画竖线
void GUI_line(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2,unsigned int color);//画直线
//void GUI_DisPicture(unsigned int x, unsigned int y, unsigned char length, unsigned int high);//显示图片(图标)
void GUI_DisPicture(unsigned int x, unsigned int y, unsigned char length, unsigned int high ,const unsigned char *pic);
void GUI_sprintf_char(unsigned int x, unsigned int y,unsigned char c, unsigned int color,unsigned int b_color);//显示英文或数字字符
void GUI_sprintf_string(unsigned int x, unsigned int y,char  *s, unsigned int color,unsigned int b_color);//显示英文字符串
void GUI_sprintf_HZ(unsigned int x, unsigned int y, unsigned int color,unsigned int b_color);//显示预定义汉字字符串
void GUI_box(unsigned int sx,unsigned int sy,unsigned int ex,unsigned int ey,unsigned int color);//画实心矩形
void GUI_rectangle( unsigned int sx,unsigned int sy,unsigned int ex,unsigned int ey,unsigned int color);//画空心矩形
void GUI_wrul(unsigned int x, unsigned int y, unsigned long num, unsigned int color,unsigned int b_color);//以十进制形式显示无符号长整型数
void GUI_wrlval(unsigned int x, unsigned int y,unsigned long num,unsigned char bits,unsigned char dp,unsigned int color,unsigned int b_color);//以十进制形式显示长变量
unsigned int RGB(unsigned char R,unsigned char G,unsigned char B);//RGB颜色混合

void PutGB1616(unsigned int x, unsigned int  y, unsigned char c[2], unsigned int fColor,unsigned int bColor);
void PutGB2424(unsigned int x, unsigned int  y, unsigned char c[2], unsigned int fColor,unsigned int bColor);
void PutGB2412(unsigned int x, unsigned int  y, unsigned char c,    unsigned int fColor,unsigned int bColor);

void Fig6464(unsigned int x, unsigned int  y, unsigned char *fig, unsigned int fColor,unsigned int bColor);
unsigned int LCD_PutString16(unsigned int x, unsigned int y, unsigned char *s, unsigned int fColor, unsigned int bColor);
unsigned int LCD_PutBmp(unsigned int x, unsigned int y, unsigned int w,unsigned int h,const unsigned char * __far data, unsigned int fColor, unsigned int bColor);

/*定义常用颜色的颜色码*/
#define RED 0xf800	//红
#define YELLOW 0xffe0	//黄
#define GREEN 0x07e0	//绿
#define CYAN 0x07ff	//青
#define BLUE 0x001f	//蓝
#define PURPLE 0xf81f	//紫
#define BLACK 0x0000	//黑
#define WHITE 0xffff	//白
#define GRAY 0x7bef	//灰
#define LOGO_X_START 0x10	//x_pos
#define LOGO_Y_START 0xB0	//y_pos



#endif













