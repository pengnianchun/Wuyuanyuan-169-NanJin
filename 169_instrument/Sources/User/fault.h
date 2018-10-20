#ifndef FAULT_H__
	#define FAULT_H__

#define FIFO_SIZE		(0x20)
/***************************** struct *****************************/
typedef struct
{
	unsigned int ID;   //¹ÊÕÏÃû³Æ @ 	fault_name
	//unsigned char code;//<!´íÎó´úÂë ²Î¿¼@fault_code_num
}FAULT_TYPE;

typedef struct
{
	unsigned int read;
	unsigned int write;
	FAULT_TYPE buffer[FIFO_SIZE];
}
FIFO_TYPEDEF;

extern volatile FIFO_TYPEDEF warning_fifo;

void WarningInit(void);
unsigned int IsQueueEmpty(FIFO_TYPEDEF *fifo);

void Warninganalysis(void);
extern FAULT_TYPE *ReadFifo(FIFO_TYPEDEF *fifo);
extern void RegisterWarning(void);

#endif
