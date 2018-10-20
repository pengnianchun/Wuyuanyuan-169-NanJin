/**
  ******************************************************************************
  * @file:      app_flash.c
  * @author:    shfangyan
  * @version:   
  * @date:      2018-6-5 
  * @brief:           用于详细说明此程序文件完成的主要功能，与其他模块
  *                    或函数的接口，输出值、取值范围、含义及参数间的控
  *                    制、顺序、独立或依赖等关系
  ******************************************************************************
  * @attention:      修改历史记录列表，每条修改记录应包括修改日期、修改
  *                   者及修改内容简述
  *    1. 时间: 2018-6-5
  *       修订者: shfangyan
  *       修订内容: 创建
  *    2.
  ******************************************************************************
  */



/* Includes ------------------------------------------------------------------*/
#include <hidef.h>      /* common defines and macros */
#include <stdio.h>
#include "derivative.h"      /* derivative-specific definitions */

#include "app_flash.h"
#include "global.h"
#include "gui.h"
#include "bmp.h"
/* Private define ------------------------------------------------------------*/
#define FRAE  (0xAA)
#define FOOTER (0x55)

#define FLASH_MEMORY_SIZE         (0x100000UL)
#define DATA_SECTION_SIZE         (0x100)
#define DATA_BLOCK_SIZE           (2*DATA_SECTION_SIZE)
#define SECTION_ELEMENT_CAPACITY  (20000UL) //2000公里
#define SECTION_ELEMENT_NUM       (500)     //100万公里
const U32 DICT_STORE_BASE = 0;
const U32 DATA_STORE_BASE = DATA_BLOCK_SIZE;

/* Private constants ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private types -------------------------------------------------------------*/
/**
  * @brief   System_DistanceInfo_Def
  *          定义参数结构
  */
struct System_DistanceInfo_Def
{
	U32 Trip1;    //!<小计里程 100m/bit
	U32 Trip2;    //!<总里程 100m/bit
	U32 sub_total_temp;//总里程计数
};

/**
  * @brief   App_FlashHandler_Def
  *          定义flash句柄
  */

struct App_FlashHandler_Def
{
	U8 is_init;
	U16 dict;//!偏移
	struct System_DistanceInfo_Def info;
};

/**
  * @brief   App_StorageStructure_Def
  *          定义数据存储结构
  */
struct App_StorageStructure_Def
{
	U8 frae;
	struct System_DistanceInfo_Def distance;
	U8 check;
	U8 footer;
};

/**
  * @brief   App_StorageDict_Def
  *          定义字典存储类型
  */
struct App_StorageDict_Def
{
	U8 frae;
	U16 dict;
	U8 check;
	U8 footer;
};

/* Private function prototypes -----------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
volatile struct App_FlashHandler_Def s_FlashHandler;

/* Exported functions --------------------------------------------------------*/

/**
  * @brief   check_data
  *          数据校验
  * @param   
  * @retval  
  */
U8 check_data(void *data,U8 len)
{
	U8 * para = (U8 *)data;
	U8 temp;
	unsigned int i;
	temp = 1;
	for (i=0;i<len;i++)
	{
		temp = temp ^ para[i];
	}
	return temp;
}

/**
  * @brief   SaveInfo
  *          保存参数,更新字典值
  * @param   none
  * @retval  none
  */
void SaveInfo(void)
{
	struct App_StorageStructure_Def buffer;
	U16 element_id;
	U32 addr;
	memset(&buffer,0,sizeof(buffer));
	
	//!设定存储数据
	buffer.frae = FRAE;
	memcpy(&buffer.distance,&s_FlashHandler.info,sizeof(buffer.distance));
	buffer.check = check_data(&buffer.distance,sizeof(buffer.distance));
	buffer.footer = FOOTER;

	//计算存储位置 
	element_id = buffer.distance.Trip2 / SECTION_ELEMENT_CAPACITY;
	addr = element_id * DATA_BLOCK_SIZE + DATA_STORE_BASE;
	
	//保存参数
	clear_mem( addr,sizeof(buffer));
	Write_mem( addr, &buffer, sizeof(buffer));
	
	clear_mem( addr+DATA_SECTION_SIZE, sizeof(buffer));
	Write_mem( addr+DATA_SECTION_SIZE, &buffer, sizeof(buffer));
	
	//更新字典
	if ((element_id != s_FlashHandler.dict) || (s_FlashHandler.dict == 0xFFFF))
	{
		struct App_StorageDict_Def dict_buffer;
		dict_buffer.frae = FRAE;
		dict_buffer.dict = element_id;
		dict_buffer.check = check_data(&dict_buffer.dict,sizeof(dict_buffer.dict));
		dict_buffer.footer = FOOTER;

		//保存字典值
		clear_mem( DICT_STORE_BASE,sizeof(dict_buffer));
		Write_mem( DICT_STORE_BASE,&dict_buffer,sizeof(dict_buffer));

		clear_mem( DICT_STORE_BASE+DATA_SECTION_SIZE,sizeof(dict_buffer));
		Write_mem( DICT_STORE_BASE+DATA_SECTION_SIZE,&dict_buffer,sizeof(dict_buffer));

		//更新静态变量
		s_FlashHandler.dict = element_id;
	}
}

/**
  * @brief   CheckDictData
  *          校验数据是否有效
  * @param   dict 源数据
  * @retval  0:正常;非零:异常
  */
U8 CheckDictData(struct App_StorageDict_Def *dict)
{
	if ((dict->frae != FRAE) || (dict->footer != FOOTER))
	{
		return 1;
	}
	else
	{
		U8 check;
		check = check_data(&dict->dict,sizeof(dict->dict));
		if (check != dict->check)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
}


/**
  * @brief   LoadDict
  *          获取字典数据
  * @param   
  * @retval  
  */
void LoadDict(void)
{
	struct App_StorageDict_Def dict_buffer;
	U8 check;
	//读取字典
	read_mem(DICT_STORE_BASE,&dict_buffer,sizeof(dict_buffer));
	if (CheckDictData(&dict_buffer) == 0)
	{
		struct App_StorageDict_Def backups_buffer;
		
		//数据正常;
		s_FlashHandler.dict = dict_buffer.dict;
		
		//校验备用数据是否正常
		read_mem(DICT_STORE_BASE + DATA_SECTION_SIZE,&backups_buffer,sizeof(backups_buffer));
		if (CheckDictData(&backups_buffer) != 0)
		{
			//备份区数据异常,将主存储区数据写入到备份区
			clear_mem( DICT_STORE_BASE+DATA_SECTION_SIZE,sizeof(dict_buffer));
			Write_mem( DICT_STORE_BASE+DATA_SECTION_SIZE,&dict_buffer,sizeof(dict_buffer));
		}
	}
	else  //主存储区数据异常
	{
		//读取备份区数据
		read_mem(DICT_STORE_BASE+DATA_SECTION_SIZE,&dict_buffer,sizeof(dict_buffer));
		if (CheckDictData(&dict_buffer) == 0)
		{
			//备份区数据正常,更新字典
			s_FlashHandler.dict = dict_buffer.dict;
			
			//更新主存储区数据
			clear_mem( DICT_STORE_BASE,sizeof(dict_buffer));
			Write_mem( DICT_STORE_BASE, &dict_buffer, sizeof(dict_buffer));
		}
		else
		{
			//数据异常,参数清零
			memset(&s_FlashHandler,0,sizeof(s_FlashHandler));
			s_FlashHandler.dict = 0xFFFF;//强制更新字典值
			SaveInfo();
		}
	}
}


/**
  * @brief   CheckStorageStructure
  *          校验数据是否有效
  * @param   dict 源数据
  * @retval  0:正常;非零:异常
  */
U8 CheckStorageStructure(struct App_StorageStructure_Def *distance)
{
	if ((distance->frae != FRAE) || (distance->footer != FOOTER))
	{
		return 1;
	}
	else
	{
		U8 check;
		check = check_data(&distance->distance,sizeof(distance->distance));
		if (check != distance->check)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
}


/**
  * @brief   LoadStorageStructure
  *          数据存储操作
  * @param   none
  * @retval  none
  */
void LoadStorageStructure(void)
{
	struct App_StorageStructure_Def buffer;
	U32 addr;
	
	addr = s_FlashHandler.dict * DATA_BLOCK_SIZE + DATA_STORE_BASE;//获取数据地址

	//获取主存储区数据
	read_mem( addr, &buffer, sizeof(buffer));
	if (CheckStorageStructure(&buffer) == 0)
	{
		//主存储区数据正常
		struct App_StorageStructure_Def backups;
		
		//更新数据
		memcpy(&s_FlashHandler.info,&buffer.distance,sizeof(s_FlashHandler.info));

		//校验备份数据区
		read_mem( addr + DATA_SECTION_SIZE, &backups, sizeof(backups));
		if (CheckStorageStructure(&backups) != 0)
		{
			//备份区数据异常
			clear_mem( addr+DATA_SECTION_SIZE, sizeof(buffer));
			Write_mem( addr+DATA_SECTION_SIZE, &buffer, sizeof(buffer));
		}
	}
	else
	{
		//主存储区数据异常

		//读取备份区数据
		read_mem( addr + DATA_SECTION_SIZE, &buffer, sizeof(buffer));
		if (CheckStorageStructure(&buffer) == 0)
		{
			//备份区数据正常
			
			//更新数据
			memcpy(&s_FlashHandler.info,&buffer.distance,sizeof(s_FlashHandler.info));

			//更新主存储区数据
			clear_mem( addr, sizeof(buffer));
			Write_mem( addr, &buffer, sizeof(buffer));
		}
		else
		{
			//数据错误,更新为默认数据
			s_FlashHandler.info.Trip1 = 0;
			s_FlashHandler.info.sub_total_temp = 0;
			s_FlashHandler.info.Trip2 = s_FlashHandler.dict * DATA_BLOCK_SIZE;
			SaveInfo();
		}
	}

}

/**
  * @brief   LoadInfo
  *          载入数据
  * @param   none
  * @retval  none
  */
void LoadInfo(void)
{
	LoadDict();
	LoadStorageStructure();
	s_FlashHandler.is_init = 1;
	KmTotalShort = s_FlashHandler.info.Trip1;
	KmTotalLong  = s_FlashHandler.info.Trip2;
	KmTotal_T1 = s_FlashHandler.info.sub_total_temp;
}
/**
  * @brief   app_flash_task
  *          flash 任务
  * @param   none
  * @retval  none
  */
void app_flash_task(void)
{
	if (s_FlashHandler.info.Trip2 != KmTotalLong)
	{
		DisableInterrupts;
		s_FlashHandler.info.Trip1 = KmTotalShort;
		s_FlashHandler.info.Trip2 = KmTotalLong;
		s_FlashHandler.info.sub_total_temp = KmTotal_T1;
		EnableInterrupts;
		SaveInfo();
	}
}
/**
  * @brief   app_flash_save
  *          保存参数
  * @param   none
  * @retval  none
  */
void app_flash_save(void)
{
	//!< KmTotalLong 100m更新一次
	if ((s_FlashHandler.info.Trip2 != KmTotalLong)||(s_FlashHandler.info.sub_total_temp != KmTotal_T1))
	{
		DisableInterrupts;
		s_FlashHandler.info.Trip1 = KmTotalShort;
		s_FlashHandler.info.Trip2 = KmTotalLong;
		s_FlashHandler.info.sub_total_temp = KmTotal_T1;
		EnableInterrupts;
		SaveInfo();
	}
}
void Flash_test(void)
{
	U16 y;
	U16 x;
	U8 buffer[50];
	U16 temp,d_temp;
	U32 u32Temp;
	static U16 save_max_time=0,load_max_time=0,err_cont=0;;
	switch(subsection)
	{
		case 0:
			subsection = 4;
			GUI_clearscreen(BLACK);
			break;
		case 4:
			subsection = 5;
			y=0;
			LCD_PutString16(0,y,">> init para: ",WHITE,BLACK);y +=20;
			LoadInfo();
			sprintf(buffer,"dict = %u",s_FlashHandler.dict);
			LCD_PutString16(0,y,buffer,WHITE,BLACK);y +=20;
			sprintf(buffer,"Trip2 = %lu",s_FlashHandler.info.Trip2);
			LCD_PutString16(0,y,buffer,WHITE,BLACK);y +=20;
		case 5:
			y = 100;
			LCD_PutString16(0,y,">> save para: ",WHITE,BLACK);y +=20;
			KmTotalLong+=100000;
			temp = TCNT;
			app_flash_task();
			d_temp = TCNT - temp;
			if (save_max_time<d_temp)
			{
				save_max_time = d_temp;
			}
			sprintf(buffer,"dict = %u      ",s_FlashHandler.dict);
			LCD_PutString16(0,y,buffer,WHITE,BLACK);y +=20;
			sprintf(buffer,"Trip2 = %lu         ",s_FlashHandler.info.Trip2);
			LCD_PutString16(0,y,buffer,WHITE,BLACK);y +=20;
			sprintf(buffer,"time = %u      ",d_temp);
			LCD_PutString16(0,y,buffer,WHITE,BLACK);y +=20;
			sprintf(buffer,"time max= %u     ",save_max_time);
			LCD_PutString16(0,y,buffer,WHITE,BLACK);y +=20;
			LCD_PutString16(0,y,">> load para:      ",WHITE,BLACK);y +=20;
			u32Temp = s_FlashHandler.info.Trip2;
			temp = TCNT;
			LoadInfo();
			d_temp = TCNT - temp;
			if (load_max_time<d_temp)
			{
				load_max_time = d_temp;
			}
			sprintf(buffer,"dict = %u      ",s_FlashHandler.dict);
			LCD_PutString16(0,y,buffer,WHITE,BLACK);y +=20;
			sprintf(buffer,"Trip2 = %lu         ",s_FlashHandler.info.Trip2);
			LCD_PutString16(0,y,buffer,WHITE,BLACK);y +=20;
			sprintf(buffer,"time = %u      ",d_temp);
			LCD_PutString16(0,y,buffer,WHITE,BLACK);y +=20;
			sprintf(buffer,"time max= %u     ",load_max_time);
			LCD_PutString16(0,y,buffer,WHITE,BLACK);y +=20;
			LCD_PutString16(0,y,">> err para: ",WHITE,BLACK);y +=20;
			if (u32Temp != s_FlashHandler.info.Trip2)
			{
				err_cont++;
			}
			sprintf(buffer,"err cnt= %u     ",err_cont);
			LCD_PutString16(0,y,buffer,WHITE,BLACK);y +=20;
			if (s_FlashHandler.dict >= SECTION_ELEMENT_NUM)
			{
				
				subsection = 6;
			}
			break;
		case 6:break;
		default :subsection = 0;break;
	}
}
