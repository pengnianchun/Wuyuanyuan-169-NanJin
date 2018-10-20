#include <hidef.h>      /* common defines and macros */
#include <string.h>

#include "derivative.h"      /* derivative-specific definitions */
#include "global.h"
//#include "bmp.h"
#include "Show.h"
//#include "str.h"
#include "config.h"


#include "include.h"
/**
 * 菜单显示:
 */

static unsigned char  DangWeiUpdateFlag=0;


/**
 * @ DigitToString_flot
 * @ para: dest[out] 输出字符串
 * @ para: data :转化数字
 * @ para: idx :偏移
 * @ para: precision :精度
 * @例:
     DigitToString_flot(buffer,1000,2000,1000);
     结果:buffer = "-1.0";
 */
void DigitToString_flot(unsigned char *dest,unsigned int data,int idx,unsigned int precision)
{
	if (0 == precision)
	{
		precision = 1;
	}
	idx = precision * idx;
	if (idx>data)
	{
		data = idx - data;
		switch(precision){
		  case 100:
				sprintf(dest,"-%u.%02u",data/precision,data%precision);
			break;
		  case	1000:
				sprintf(dest,"-%u.%03u",data/precision,data%precision);
			break;
		  default:
			sprintf(dest,"-%u.%u",data/precision,data%precision);
			break;
		}
	
	}
	else
	{
		data = data - idx;
		switch(precision){
		  case 100:
				sprintf(dest,"%u.%02u",data/precision,data%precision);
			break;
		  case	1000:
				sprintf(dest,"%u.%03u",data/precision,data%precision);
			break;
		  default:
			sprintf(dest,"%u.%u",data/precision,data%precision);
			break;
		}
	}
}

/**
 * @ DigitToString_int
 * @ para: dest[out] 输出字符串
 * @ para: data :转化数字
 * @ para: idx :偏移
 */

void DigitToString_int(unsigned char *dest,unsigned int data,int idx)
{
	if (idx>data)
	{
		data = idx - data;
		sprintf(dest,"-%u",data);
	}
	else
	{
		data = data - idx;
		sprintf(dest,"%u",data);
	}
}





ShowMenuFun ShowMenu[] = {ShowMainPage,ShowDebugPage,FaultMenu};
//{ShowMainPage,ShowDebugPage,ShowSwtich,ShowBatteryManager,ShowControl/*整车控制器*/,
//	      ShowAuxiliary/*电机控制器*/,ShowAir/*辅助系统信息*/,FaultMenu};

unsigned int GetShowSize(void)
{
	unsigned int temp;
	temp = sizeof(ShowMenu)/sizeof(ShowMenu[0]);
	return temp;
}

void SetShowMenuPage(unsigned int page)
{
	unsigned int temp;
	temp = GetShowSize();
	if (page < temp)
	{
		MenuPage = page;
		subsection = 0;
	}
}


