#ifndef GUI_H
#define GUI_H



/*GUI����*/
void GUI_clearscreen(unsigned int b_color);//����
void GUI_clearscreen_part1(unsigned int b_color);
void GUI_Point(unsigned int x, unsigned int y, unsigned int color);//����
void GUI_sprintf_chartobit(unsigned int x, unsigned int y,unsigned char dat, unsigned int color,unsigned int b_color);//�޷����ַ������Զ�������ʽ��ʾ
void GUI_sprintf_chartohex(unsigned int x, unsigned int y,unsigned char dat, unsigned int color,unsigned int b_color);//�޷����ַ�������ʮ��������ʽ��ʾ
void GUI_sprintf_chartodec(unsigned int x,unsigned int y,unsigned char dat,unsigned int color,unsigned int b_color);//�޷����ַ�������ʮ������ʽ��ʾ
void GUI_sprintf_nu(unsigned int x, unsigned int y,unsigned char nu, unsigned int color,unsigned int b_color);//��ʾ1λ16������
void GUI_HLine(unsigned int x, unsigned int y, unsigned char length, unsigned int color);//������
void GUI_RLine(unsigned int x, unsigned int y, unsigned int high, unsigned int color);//������
void GUI_line(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2,unsigned int color);//��ֱ��
//void GUI_DisPicture(unsigned int x, unsigned int y, unsigned char length, unsigned int high);//��ʾͼƬ(ͼ��)
void GUI_DisPicture(unsigned int x, unsigned int y, unsigned char length, unsigned int high ,const unsigned char *pic);
void GUI_sprintf_char(unsigned int x, unsigned int y,unsigned char c, unsigned int color,unsigned int b_color);//��ʾӢ�Ļ������ַ�
void GUI_sprintf_string(unsigned int x, unsigned int y,char  *s, unsigned int color,unsigned int b_color);//��ʾӢ���ַ���
void GUI_sprintf_HZ(unsigned int x, unsigned int y, unsigned int color,unsigned int b_color);//��ʾԤ���庺���ַ���
void GUI_box(unsigned int sx,unsigned int sy,unsigned int ex,unsigned int ey,unsigned int color);//��ʵ�ľ���
void GUI_rectangle( unsigned int sx,unsigned int sy,unsigned int ex,unsigned int ey,unsigned int color);//�����ľ���
void GUI_wrul(unsigned int x, unsigned int y, unsigned long num, unsigned int color,unsigned int b_color);//��ʮ������ʽ��ʾ�޷��ų�������
void GUI_wrlval(unsigned int x, unsigned int y,unsigned long num,unsigned char bits,unsigned char dp,unsigned int color,unsigned int b_color);//��ʮ������ʽ��ʾ������
unsigned int RGB(unsigned char R,unsigned char G,unsigned char B);//RGB��ɫ���

void PutGB1616(unsigned int x, unsigned int  y, unsigned char c[2], unsigned int fColor,unsigned int bColor);
void PutGB2424(unsigned int x, unsigned int  y, unsigned char c[2], unsigned int fColor,unsigned int bColor);
void PutGB2412(unsigned int x, unsigned int  y, unsigned char c,    unsigned int fColor,unsigned int bColor);

void Fig6464(unsigned int x, unsigned int  y, unsigned char *fig, unsigned int fColor,unsigned int bColor);
unsigned int LCD_PutString16(unsigned int x, unsigned int y, unsigned char *s, unsigned int fColor, unsigned int bColor);
unsigned int LCD_PutBmp(unsigned int x, unsigned int y, unsigned int w,unsigned int h,const unsigned char * __far data, unsigned int fColor, unsigned int bColor);

/*���峣����ɫ����ɫ��*/
#define RED 0xf800	//��
#define YELLOW 0xffe0	//��
#define GREEN 0x07e0	//��
#define CYAN 0x07ff	//��
#define BLUE 0x001f	//��
#define PURPLE 0xf81f	//��
#define BLACK 0x0000	//��
#define WHITE 0xffff	//��
#define GRAY 0x7bef	//��
#define LOGO_X_START 0x10	//x_pos
#define LOGO_Y_START 0xB0	//y_pos



#endif













