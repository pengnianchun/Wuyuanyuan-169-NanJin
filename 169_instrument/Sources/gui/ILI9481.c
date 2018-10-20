/*********************************************************************
 *
 *                ILI9325 TFT������������
 *
 *********************************************************************
 * �ļ���: ILI9325.c
 * ����:
 * ��˾: ��������
 * ����              		����         			ע��
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * ��ΰ��				2010/3/20				ԭʼ�ļ�
 ********************************************************************/


#include "config.h"

/*��ɫ��ֵ:��ɫ����ɫ����ɫ����ɫ����ɫ����ɫ������ɫ����ɫ*/
unsigned int color[]= {0xf800,0x07e0,0x001f,0xffe0,0x0000,0xffff,0x07ff,0xf81f};

//=============================================================
//TFT��ʼ��
//���ܣ��ú������ڳ�ʼ��TFT����ģ�顣
//��ڲ���: ��
//���ڲ���: ��
void ILI9481_initial(void)
{
	TFT_RST=1;        
	delay_nms(50);
	TFT_RST=0;
	delay_nms(50);
	TFT_RST=1;
	TFT_CS=1;
	TFT_RD=1;
	TFT_WR=1;
	delay_nms(50);

	TFT_CS =0;  //��Ƭѡʹ��

	write_cmd(0x00,0x11);
	delay_nms(20);

	write_cmd(0x00,0xD0);
	write_data(0x00,0x07);
	write_data(0x00,0x42);
	write_data(0x00,0x18);

	write_cmd(0x00,0xD1);
	write_data(0x00,0x00);
	write_data(0x00,0x07);//07
	write_data(0x00,0x10);

	write_cmd(0x00,0xD2);
	write_data(0x00,0x01);
	write_data(0x00,0x02);

	write_cmd(0x00,0xC0);
	write_data(0x00,0x10);
	write_data(0x00,0x3B);
	write_data(0x00,0x00);
	write_data(0x00,0x02);
	write_data(0x00,0x11);

	write_cmd(0x00,0xC5);
	write_data(0x00,0x03);

	write_cmd(0x00,0xC8);
	write_data(0x00,0x00);
	write_data(0x00,0x32);
	write_data(0x00,0x36);
	write_data(0x00,0x45);
	write_data(0x00,0x06);
	write_data(0x00,0x16);//16
	write_data(0x00,0x37);
	write_data(0x00,0x75);
	write_data(0x00,0x77);
	write_data(0x00,0x54);
	write_data(0x00,0x0c);
	write_data(0x00,0x00);

	write_cmd(0x00,0x36);
	write_data(0x00,0x0A);

	write_cmd(0x00,0x3A);
	write_data(0x00,0x55);

	write_cmd(0x00,0x2A);
	write_data(0x00,0x00);
	write_data(0x00,0x00);
	write_data(0x00,0x01);
	write_data(0x00,0x27);

	write_cmd(0x00,0x2B);
	write_data(0x00,0x00);
	write_data(0x00,0x00);
	write_data(0x00,0x01);
	write_data(0x00,0xDF);
	delay_nms(120);
	write_cmd(0x00,0x29);
	write_cmd(0x00,0x2C); //display on
	TFT_CS =1;  //�ر�Ƭѡʹ��
}


//=============================================================

void write_bus(unsigned char CH,unsigned char CL)
{
	Polling();
	//LCD_DataPortDDR=0xFFFF;
	LCD_DataPortH=CH;
	LCD_DataPortL=CL;
	TFT_WR=0;
	TFT_WR=1;
}

void write_cmd(unsigned char CH,unsigned char CL)
{
	TFT_CS =0;
	TFT_RS=0;
	write_bus(CH,CL);

	TFT_CS =1;
}

void write_data(unsigned char DH,unsigned char DL)
{
	TFT_CS =0;
	TFT_RS=1;
	write_bus(DH,DL);
	TFT_CS =1;
}

void write_bus16(unsigned int dat)
{
	
	PORTCD= dat;
	TFT_WR=0;
	TFT_WR=1;
}

void write_cmd16(unsigned int dat)
{
	TFT_CS =0;
	TFT_RS=0;
	write_bus16(dat);

	TFT_CS =1;
}

void write_data16(unsigned int dat)
{
	TFT_CS =0;
	TFT_RS=1;
	write_bus16(dat);
	TFT_CS =1;
}

//==============================================================
//д16λ����
//���ܣ� дһ�����ݵ�TFT��������
//��ڲ���: datΪҪд���16λ���ݡ�
//���ڲ���: ��

/*

void write_data_u16(unsigned int dat)
{
	unsigned char m,n;

	m=dat>>8;
	n=dat;
	write_data(m,n);

} */

void write_data_u16(unsigned int dat)
{
	TFT_CS =0;
	TFT_RS=1;
	write_bus16(dat);
	TFT_CS =1;
}


//===============================================================
//д��������
//���ܣ� д�������ݵ�TFT��������
//��ڲ���: cmdΪҪд��������ֽڣ�datΪҪд���16λ���ݡ�
//���ڲ���: ��
void write_cmd_data (unsigned char cmd,unsigned int dat)
{

	write_cmd16(cmd);
	write_data16(dat);

}


//===============================================================
//���ô���
//��ڲ���: x0 y0,Ϊ��ʾ�������Ͻ����ꣻx1,y1Ϊ��ʾ�������½����ꡣ
//���ڲ���: ��
//˵�����ú�������TFTģ�����ʾ���ڡ�
void LCD_setwindow(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2)
{
	x1=x1+24;
	x2=x2+24;
	write_cmd(0x00,0x2a);
	write_data(0x00,x1>>8);	    //��ʼX
	write_data(0x00,x1);	    //��ʼX
	write_data(0x00,x2>>8);	    //����X
	write_data(0x00,x2);	    //����X
	write_cmd(0x00,0x2b);
	write_data(0x00,y1>>8);		//��ʼY
	write_data(0x00,y1);		//��ʼY
	write_data(0x00,y2>>8);	    //����Y
	write_data(0x00,y2);	    //����Y
	write_cmd(0x00,0x2c);
	
	//LCD_setwindow(0,0,271,479);
}


//===============================================================
//�趨��ǰ��ʾ����
//��ڲ���: x,yΪ��ǰ��ʾ���ꡣ
//���ڲ���: ��
//˵����������ʵ������LCD_setwindow������һ����������ʾ����Ϊ��С������һ�����ص㡣
void LCD_setxy(unsigned int x,unsigned int y)
{
	LCD_setwindow(x,y,x,y);
}







