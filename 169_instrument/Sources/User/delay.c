

#include "config.h"
/*----------------------------------------------------------------------- 
��ʱ���� 
ϵͳʱ�ӣ�8M 
-----------------------------------------------------------------------*/ 
void delay_1us(void)                 //1us��ʱ���� 
  { 
   _FEED_COP(); 
  } 
  
void delay_nus(unsigned int n)       //N us��ʱ���� 
  { 
   unsigned int nus_i=0; 
   for (nus_i=0;nus_i<n;nus_i++) 
   delay_1us(); 
  }  
	
void delay_1ms(void)                 //1ms��ʱ���� 
  { 
   unsigned int ms_i; 
   for (ms_i=0;ms_i<1440;ms_i++) 
   {   
   _FEED_COP();
   }  
  } 
void delay_nms(unsigned int n)       //N ms��ʱ���� 
  { 
   unsigned int nms_i=0; 
   for (nms_i=0;nms_i<n;nms_i++) 
   delay_1ms(); 
  }