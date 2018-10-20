#include "include.h"
/**
 * @file: warning
 */

/**
 * 需要显示的字符
 */
static const unsigned char *warning_string[] = 
{
	warning_string_1,warning_string_2,warning_string_3,warning_string_4,warning_string_5,
	warning_string_6,warning_string_7,warning_string_8,warning_string_9,warning_string_10,
	warning_string_11,warning_string_12,warning_string_13,warning_string_14,warning_string_15,
	warning_string_16,warning_string_17,warning_string_18,warning_string_19,
};

#define WARNING_TEXBOX_X          0   
#define WARNING_TEXBOX_Y          0
#define WARNING_TEXBOX_DX         272
#define WARNING_TEXBOX_DY         480



int  ShowWarningStirng(unsigned char *str)
{
	U16 u16temp,len;
	U16 line,i;
	GUI_box(WARNING_TEXBOX_X,WARNING_TEXBOX_Y,WARNING_TEXBOX_DX,WARNING_TEXBOX_DY);
	len = strlen(str) * 12;//!<获取字符串显示长度
	line = (len+(WARNING_TEXBOX_DX-WARNING_TEXBOX_X) + (WARNING_TEXBOX_DX-WARNING_TEXBOX_X-1)) / 272;
	for (i = 0;i<line;i++)
	{
		len = strlen(str);//!<获取字符串显示长度
		
	}
}


#ifdef DEBUG_WARNING

void DebugShowWarning(void)
{
	
}

#endif



