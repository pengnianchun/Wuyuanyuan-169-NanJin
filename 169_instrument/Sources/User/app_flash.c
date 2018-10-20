/**
  ******************************************************************************
  * @file:      app_flash.c
  * @author:    shfangyan
  * @version:   
  * @date:      2018-6-5 
  * @brief:           ������ϸ˵���˳����ļ���ɵ���Ҫ���ܣ�������ģ��
  *                    �����Ľӿڣ����ֵ��ȡֵ��Χ�����弰������Ŀ�
  *                    �ơ�˳�򡢶����������ȹ�ϵ
  ******************************************************************************
  * @attention:      �޸���ʷ��¼�б�ÿ���޸ļ�¼Ӧ�����޸����ڡ��޸�
  *                   �߼��޸����ݼ���
  *    1. ʱ��: 2018-6-5
  *       �޶���: shfangyan
  *       �޶�����: ����
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
#define SECTION_ELEMENT_CAPACITY  (20000UL) //2000����
#define SECTION_ELEMENT_NUM       (500)     //100����
const U32 DICT_STORE_BASE = 0;
const U32 DATA_STORE_BASE = DATA_BLOCK_SIZE;

/* Private constants ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private types -------------------------------------------------------------*/
/**
  * @brief   System_DistanceInfo_Def
  *          ��������ṹ
  */
struct System_DistanceInfo_Def
{
	U32 Trip1;    //!<С����� 100m/bit
	U32 Trip2;    //!<����� 100m/bit
	U32 sub_total_temp;//����̼���
};

/**
  * @brief   App_FlashHandler_Def
  *          ����flash���
  */

struct App_FlashHandler_Def
{
	U8 is_init;
	U16 dict;//!ƫ��
	struct System_DistanceInfo_Def info;
};

/**
  * @brief   App_StorageStructure_Def
  *          �������ݴ洢�ṹ
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
  *          �����ֵ�洢����
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
  *          ����У��
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
  *          �������,�����ֵ�ֵ
  * @param   none
  * @retval  none
  */
void SaveInfo(void)
{
	struct App_StorageStructure_Def buffer;
	U16 element_id;
	U32 addr;
	memset(&buffer,0,sizeof(buffer));
	
	//!�趨�洢����
	buffer.frae = FRAE;
	memcpy(&buffer.distance,&s_FlashHandler.info,sizeof(buffer.distance));
	buffer.check = check_data(&buffer.distance,sizeof(buffer.distance));
	buffer.footer = FOOTER;

	//����洢λ�� 
	element_id = buffer.distance.Trip2 / SECTION_ELEMENT_CAPACITY;
	addr = element_id * DATA_BLOCK_SIZE + DATA_STORE_BASE;
	
	//�������
	clear_mem( addr,sizeof(buffer));
	Write_mem( addr, &buffer, sizeof(buffer));
	
	clear_mem( addr+DATA_SECTION_SIZE, sizeof(buffer));
	Write_mem( addr+DATA_SECTION_SIZE, &buffer, sizeof(buffer));
	
	//�����ֵ�
	if ((element_id != s_FlashHandler.dict) || (s_FlashHandler.dict == 0xFFFF))
	{
		struct App_StorageDict_Def dict_buffer;
		dict_buffer.frae = FRAE;
		dict_buffer.dict = element_id;
		dict_buffer.check = check_data(&dict_buffer.dict,sizeof(dict_buffer.dict));
		dict_buffer.footer = FOOTER;

		//�����ֵ�ֵ
		clear_mem( DICT_STORE_BASE,sizeof(dict_buffer));
		Write_mem( DICT_STORE_BASE,&dict_buffer,sizeof(dict_buffer));

		clear_mem( DICT_STORE_BASE+DATA_SECTION_SIZE,sizeof(dict_buffer));
		Write_mem( DICT_STORE_BASE+DATA_SECTION_SIZE,&dict_buffer,sizeof(dict_buffer));

		//���¾�̬����
		s_FlashHandler.dict = element_id;
	}
}

/**
  * @brief   CheckDictData
  *          У�������Ƿ���Ч
  * @param   dict Դ����
  * @retval  0:����;����:�쳣
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
  *          ��ȡ�ֵ�����
  * @param   
  * @retval  
  */
void LoadDict(void)
{
	struct App_StorageDict_Def dict_buffer;
	U8 check;
	//��ȡ�ֵ�
	read_mem(DICT_STORE_BASE,&dict_buffer,sizeof(dict_buffer));
	if (CheckDictData(&dict_buffer) == 0)
	{
		struct App_StorageDict_Def backups_buffer;
		
		//��������;
		s_FlashHandler.dict = dict_buffer.dict;
		
		//У�鱸�������Ƿ�����
		read_mem(DICT_STORE_BASE + DATA_SECTION_SIZE,&backups_buffer,sizeof(backups_buffer));
		if (CheckDictData(&backups_buffer) != 0)
		{
			//�����������쳣,�����洢������д�뵽������
			clear_mem( DICT_STORE_BASE+DATA_SECTION_SIZE,sizeof(dict_buffer));
			Write_mem( DICT_STORE_BASE+DATA_SECTION_SIZE,&dict_buffer,sizeof(dict_buffer));
		}
	}
	else  //���洢�������쳣
	{
		//��ȡ����������
		read_mem(DICT_STORE_BASE+DATA_SECTION_SIZE,&dict_buffer,sizeof(dict_buffer));
		if (CheckDictData(&dict_buffer) == 0)
		{
			//��������������,�����ֵ�
			s_FlashHandler.dict = dict_buffer.dict;
			
			//�������洢������
			clear_mem( DICT_STORE_BASE,sizeof(dict_buffer));
			Write_mem( DICT_STORE_BASE, &dict_buffer, sizeof(dict_buffer));
		}
		else
		{
			//�����쳣,��������
			memset(&s_FlashHandler,0,sizeof(s_FlashHandler));
			s_FlashHandler.dict = 0xFFFF;//ǿ�Ƹ����ֵ�ֵ
			SaveInfo();
		}
	}
}


/**
  * @brief   CheckStorageStructure
  *          У�������Ƿ���Ч
  * @param   dict Դ����
  * @retval  0:����;����:�쳣
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
  *          ���ݴ洢����
  * @param   none
  * @retval  none
  */
void LoadStorageStructure(void)
{
	struct App_StorageStructure_Def buffer;
	U32 addr;
	
	addr = s_FlashHandler.dict * DATA_BLOCK_SIZE + DATA_STORE_BASE;//��ȡ���ݵ�ַ

	//��ȡ���洢������
	read_mem( addr, &buffer, sizeof(buffer));
	if (CheckStorageStructure(&buffer) == 0)
	{
		//���洢����������
		struct App_StorageStructure_Def backups;
		
		//��������
		memcpy(&s_FlashHandler.info,&buffer.distance,sizeof(s_FlashHandler.info));

		//У�鱸��������
		read_mem( addr + DATA_SECTION_SIZE, &backups, sizeof(backups));
		if (CheckStorageStructure(&backups) != 0)
		{
			//�����������쳣
			clear_mem( addr+DATA_SECTION_SIZE, sizeof(buffer));
			Write_mem( addr+DATA_SECTION_SIZE, &buffer, sizeof(buffer));
		}
	}
	else
	{
		//���洢�������쳣

		//��ȡ����������
		read_mem( addr + DATA_SECTION_SIZE, &buffer, sizeof(buffer));
		if (CheckStorageStructure(&buffer) == 0)
		{
			//��������������
			
			//��������
			memcpy(&s_FlashHandler.info,&buffer.distance,sizeof(s_FlashHandler.info));

			//�������洢������
			clear_mem( addr, sizeof(buffer));
			Write_mem( addr, &buffer, sizeof(buffer));
		}
		else
		{
			//���ݴ���,����ΪĬ������
			s_FlashHandler.info.Trip1 = 0;
			s_FlashHandler.info.sub_total_temp = 0;
			s_FlashHandler.info.Trip2 = s_FlashHandler.dict * DATA_BLOCK_SIZE;
			SaveInfo();
		}
	}

}

/**
  * @brief   LoadInfo
  *          ��������
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
  *          flash ����
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
  *          �������
  * @param   none
  * @retval  none
  */
void app_flash_save(void)
{
	//!< KmTotalLong 100m����һ��
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
