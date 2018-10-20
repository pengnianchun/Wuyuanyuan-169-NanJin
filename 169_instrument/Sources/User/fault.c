#include "include.h"

#define FAULT_CODE_BOUNDARY		
/**
 * @warning_code
 * @�����������
 */
/**
 * @warning_color
 * @���������������Ӧ����ɫ
 */
 
/**
 * @warning_name
 * @��������
 */
const unsigned char *warning_name[] = {NULL};
/**
 * @warning_code_num
 * @��ͬ���϶�Ӧ���ϵȼ�,˳��Ϊ@warning_name˳��
 */

static unsigned char s_warning_new[3];
static unsigned char s_warning_old[3];

static unsigned char s_fault_new[3];
static unsigned char s_fault_old[3];
static unsigned char s_fault_cont[24];//!<���澯�����
/**
 * @block:���϶�������
 * @{
 */
 

/***************************** variable *****************************/
volatile FIFO_TYPEDEF warning_fifo;

/***************************** function *****************************/
/**
 * @WarningInit()
 * @���г�ʼ������
 */
void ClearFifo(FIFO_TYPEDEF *fifo)
{
	fifo->read = fifo->write;
}
void WarningInit(void)
{
	ClearFifo(&warning_fifo);
	warning_show_time = 0;
	//can_signal.ID_104C1992.DanTiDianYaHuChaBaoJing[0] = 0x01;
	memset(s_warning_old,0,sizeof(s_warning_old));
	//memset(s_fault_old,0,sizeof(s_fault_old));
}
void FaultInit(void)
{
	fault_show_time = 0;
	memset(s_fault_cont,0,sizeof(s_fault_cont));
	memset(s_fault_old,0,sizeof(s_fault_old));
}

/**
 * @IsQueueEmpty()
 * @return:1:����Ϊ��;0:���в�Ϊ��
 */

unsigned int IsQueueEmpty(FIFO_TYPEDEF *fifo)
{
	return (fifo->read == fifo->write); 
}
/**
 * @GetFifoFreeSpace()
 * @return:���ض���ʣ��ռ�
 */

unsigned int GetFifoFreeSpace(FIFO_TYPEDEF *fifo)
{
	unsigned int temp;
	temp = fifo->read + FIFO_SIZE;
	temp -= fifo->write;
	while(temp>(FIFO_SIZE))
	{
		temp -= FIFO_SIZE;
	}
	temp -=1;
	return temp;
}
/**
 * @ReadFifo()
 * @return:�������ݵ�ַ
 */

FAULT_TYPE *ReadFifo(FIFO_TYPEDEF *fifo)
{

	FAULT_TYPE * temp;
	temp = &(fifo->buffer[(fifo->read)]);
	fifo->read++;
	if (fifo->read>=FIFO_SIZE)
	{
		fifo->read = 0;
	}
	return temp;
}
void WriteFifo(FIFO_TYPEDEF *fifo,const FAULT_TYPE *pIn)
{
	fifo->buffer[fifo->write].ID= pIn->ID;
	fifo->write++;
	if (fifo->write >= FIFO_SIZE)
	{
		fifo->write = 0;
	}
}
/**
 * @}
 */
//!<������Ϣ����

void Warninganalysis(void)
{
	s_warning_new[0] = can_signal.ID_041000A0.Warning_Code1.Byte&0x6F;
	s_warning_new[1] = can_signal.ID_041000A0.Warning_Code2.Byte|0x80;//ɲ��Ƭĥ�𱨾�����
	s_warning_new[2] = can_signal.ID_041000A0.Warning_Code3.Byte&0x1F;

	s_fault_new[0] = can_signal.ID_041000A0.VCU_Diag_Code1.Byte&0xFF;
	s_fault_new[1] = can_signal.ID_041000A0.VCU_Diag_Code2.Byte&0x7F;
	s_fault_new[2] = can_signal.ID_041000A0.VCU_Diag_Code3.Byte&0x7F;
}
//!<������ע�ắ��;
void RegisterWarning(void)
{
	static unsigned int cont = 0;
	unsigned char idx_byte,idx_bit;
	unsigned int temp;
	unsigned char u8temp,temp_new,temp_old;
	//!<�ж϶����Ƿ�����
	temp = GetFifoFreeSpace(&warning_fifo);
	if (temp == 0)
	{
		return;
	}
	if (cont>=24)
	{
		cont = 0;
	}
	//!<����ô��ж�λ
	idx_byte = cont / 8;
	idx_bit = cont & 0x07;


	u8temp = 0x01<<idx_bit;
	temp_new = s_warning_new[idx_byte];
	temp_old = s_warning_old[idx_byte];
	
	temp_new &= u8temp;
	temp_old &= u8temp;

	if (temp_old != temp_new)
	{
		if (temp_new)
		{
			FAULT_TYPE warning;
			warning.ID = cont;
			WriteFifo(&warning_fifo,&warning);
		}
		s_warning_old[idx_byte] ^= u8temp;
	}
	cont++;
}
unsigned int IsWarningNormal(void)
{
	unsigned int i;
	for (i=0;i<sizeof(s_warning_old)/sizeof(s_warning_old[0]);i++)
	{
		if (s_warning_old[i])
		{
			return 0;
		}
	}
	return 1;
}
unsigned int IsFaultNormal(void)
{
	unsigned int i;
	for (i=0;i<sizeof(s_fault_old)/sizeof(s_fault_old[0]);i++)
	{
		if (s_fault_old[i])
		{
			return 0;
		}
	}
	return 1;

}
//!<�����ȼ����±���
const priority_id[] = {
	3,5,4,6,18,17,16,15,
	2,7,10,20,19,9,8,255,
	14,13,12,11,1,21,22,
};

void RegisterFaul(void)
{
	U8 u8temp[3];
	int i,j;
	unsigned char idx_byte,idx_bit;

	u8temp[0] = s_fault_new[0];
	u8temp[1] = s_fault_new[1];
	u8temp[2] = s_fault_new[2];


	u8temp[0] = u8temp[0] ^ s_fault_old[0];
	u8temp[1] = u8temp[1] ^ s_fault_old[1];
	u8temp[2] = u8temp[2] ^ s_fault_old[2];


	u8temp[0] &= s_fault_new[0];
	u8temp[1] &= s_fault_new[1];
	u8temp[2] &= s_fault_new[2];

	s_fault_old[0] = s_fault_new[0];
	s_fault_old[1] = s_fault_new[1];
	s_fault_old[2] = s_fault_new[2];
	s_fault_cont[0] = 0;

	for(i=0; i<24; i++)
	{
		idx_bit = i&0x07;
		idx_bit = 0x01<<idx_bit;
		idx_byte = i/8;
		if (idx_bit & u8temp[idx_byte])
		{
			j = priority_id[i];
			if (s_fault_cont[j]<10)
				s_fault_cont[j]++;
		}
	}
	if (s_fault_new[2]&B4)
	{
		//!<����¶��쳣���⴦��
		s_fault_cont[1] = 1;
	}
}


U16 GetFaulID(void)
{
	unsigned int i;
	for(i=0;i<24;i++)
	{
		
		if (s_fault_cont[i] != 0)
		{
			s_fault_cont[i]--;
			return (i);
		}
	}
	return 0;
}
