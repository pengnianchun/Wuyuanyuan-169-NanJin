
#include "config.h"

#if USER_HARDWARE_SPI == 0

void SPI_byte_write( unsigned char tmp);



void SPI_Write( unsigned long Addr,unsigned char c) ;  
unsigned char SPI_Read(unsigned long Addr);
void spi_init(void)
{
}

unsigned char EWriting(void)
{
	unsigned char c;
	SPI_CS25 = 0;
	SPI_byte_write(0x05);
	c = SPI_byte_read();
	SPI_CS25 = 1;
	return c & 1;
}

void SPI_byte_write(unsigned char data)
{
	unsigned char localtemp = 0;

	MPSCK = 0;
	while(localtemp < 8)
	{
		if(data & 0b10000000)
		{
			MPMOSI = 1;
		}
		else
		{
			MPMOSI = 0;
		}
		delay_nus(1);
		MPSCK = 1;
		delay_nus(1);
		MPSCK = 0;
		data <<=1;
		localtemp++;
	}
}


unsigned char SPI_byte_read(void)
{
	unsigned char localtemp = 0;
	unsigned char data = 0;

	MPSCK = 0;
	while(localtemp < 7)
	{
		delay_nus(1);
		MPSCK = 1;
		if(MPMISO)
		{
			data += 1;
		}
		delay_nus(1);
		MPSCK = 0;
		data <<=1;
		localtemp++;
	}

	delay_nus(1);
	MPSCK = 1;
	if(MPMISO)
	{
		data += 1;
	}
	delay_nus(1);
	MPSCK = 0;

	return data;
}




void SPI_Write( unsigned long Addr,unsigned char c)
{
	SPI_CS25=1;
	delay_nus(1) ;
	SPI_CS25=0;
	delay_nus(1) ;
	SPI_byte_write(0x06);
	SPI_CS25=1;

	delay_nus(10) ;

	SPI_CS25=0;
	SPI_byte_write(0x02);

	SPI_byte_write(Addr>>16);
	SPI_byte_write(Addr>>8);
	SPI_byte_write((unsigned char) Addr);

	SPI_byte_write(c);
	while(EWriting()) ;
	SPI_CS25=1;
	SPI_CS25=0;
}
unsigned char SPI_Read(unsigned long Addr)
{
	unsigned char   i=0,c;

	SPI_CS25=1;
	delay_nus(1) ;

	SPI_CS25=0;
	SPI_byte_write(0x03);

	SPI_byte_write(Addr>>16);
	SPI_byte_write(Addr>>8);
	SPI_byte_write((unsigned char) Addr);

	c=SPI_byte_read();

	SPI_CS25=1;
	return c;
}

void Write_mem(unsigned long Addr,void *data,U8 len)
{
	U8 i;
	U8 *para=(U8*)data;
	SPI_CS25=1;
	SPI_CS25=0;
	SPI_byte_write(0x06);
	SPI_CS25=1;
	delay_nus(10) ;
	SPI_CS25=0;
	SPI_byte_write(0x02);
	SPI_byte_write(Addr>>16);
	SPI_byte_write(Addr>>8);
	SPI_byte_write((unsigned char) Addr);
	for(i=0;i<len;i++)
	{
		SPI_byte_write(para[i]);
	}
	SPI_CS25=1;
	while(EWriting());
}
void clear_mem(unsigned long Addr,U16 len)
{
	U16 i;
	SPI_CS25=1;
	SPI_CS25=0;
	SPI_byte_write(0x06);
	SPI_CS25=1;
	delay_nus(10) ;
	SPI_CS25=0;
	SPI_byte_write(0x02);
	SPI_byte_write(Addr>>16);
	SPI_byte_write(Addr>>8);
	SPI_byte_write((unsigned char) Addr);
	for(i=0;i<len;i++)
	{
		SPI_byte_write(0xFF);
	}
	SPI_CS25=1;
	while(EWriting());
}
void read_mem(unsigned long Addr,void *data,U8 len)
{
	U8 i;
	U8 *para=(U8*)data;
	SPI_CS25=1;
	SPI_CS25=0;
	SPI_byte_write(0x03);
	SPI_byte_write(Addr>>16);
	SPI_byte_write(Addr>>8);
	SPI_byte_write((unsigned char) Addr);
	for(i=0;i<len;i++)
	{
		para[i] = SPI_byte_read();
	}
	SPI_CS25=1;
}
#else
/**
  * @brief   spi_init
  *          ��ʼ��SPI
  * @param   none
  * @retval  none
  */
void spi_init(void)
{
  /* �˿��������״̬�趨  */
  /* SPI1CR1: SPIE=0,SPE=0,SPTIE=0,MSTR=0,CPOL=0,CPHA=0,SSOE=0,LSBFE=0 */
  SPI1CR1 = 0x00U;					   /* Disable the SPI1 module and clearing flags in SPISR register */
  /* SPI1CR2: XFRW=0,MODFEN=1,BIDIROE=0,SPISWAI=0,SPC0=0 */
  SPI1CR2 = 0x00U;										
  /* SPI1BR: SPPR2=1,SPPR1=0,SPPR0=0,SPR2=0,SPR1=1,SPR0=0 */
  //�����ʲ�������߷��߻��������;
  SPI1BR_SPR = 2;
  SPI1BR_SPPR = 1;			// BaudRateDivisor = (SPPR + 1) * 2^(SPR + 1)		  
  							// Baud Rate = BusClock / BaudRateDivisor
  /* SPI1CR1: SPIE=0,SPE=1,SPTIE=0,MSTR=1,CPOL=1,CPHA=0,SSOE=1,LSBFE=0 */
  SPI1CR1 = 0x50;		//	  SSOE��Ҫ���ó�0 ����PJ2�޷����õ�ƽ							
  /* ### */
  /* Initial interrupt priority */
  /*lint -save	-e950 Disable MISRA rule (1.1) checking. */
 }
/**
  * @brief   SPI_Byte
  *          SPI��д
  * @param   
  * @retval  
  */
U8  SPI_Byte(U8 value)
{
  	while(!(SPI1SR_SPTEF));
	SPI1DR = value;
	while(!(SPI1SR_SPIF));
  	return SPI1DRL;
}
/**
  * @brief   EWriting
  *          Write-In-Process
  * @param   none
  * @retval  ����д��״̬;��Ϊ���ʾ����д��
  */
unsigned char EWriting(void)
{
	unsigned char c;
	SPI_CS25 = 0;
	SPI_Byte(RDSR);
	c = SPI_Byte(0);
	SPI_CS25 = 1;
	return c & 1;
}

void EnableWriteOperations(void)
{
	SPI_CS25=1;
	SPI_CS25=0;
	SPI_Byte(WREN);
	SPI_CS25=1;
	delay_nus(10) ;
}

void Write_mem(unsigned long Addr,void *data,U8 len)
{
	U8 i;
	U8 *para=(U8*)data;
	EnableWriteOperations();
	SPI_CS25=0;
	SPI_Byte(WRITE);
	SPI_Byte(Addr>>16);
	SPI_Byte(Addr>>8);
	SPI_Byte((unsigned char) Addr);
	for(i=0;i<len;i++)
	{
		SPI_Byte(para[i]);
	}
	SPI_CS25=1;
	while(EWriting());
}
void clear_mem(unsigned long Addr,U16 len)
{
	U8 i;
	SPI_CS25=0;
	SPI_Byte(WRITE);
	SPI_Byte(Addr>>16);
	SPI_Byte(Addr>>8);
	SPI_Byte((unsigned char) Addr);
	for(i=0;i<len;i++)
	{
		SPI_Byte(0xFF);
	}
	SPI_CS25=1;
	while(EWriting())Polling();
}
void read_mem(unsigned long Addr,void *data,U8 len)
{
	U8 i;
	U8 *para=(U8*)data;
	SPI_CS25=1;
	SPI_CS25=0;
	SPI_Byte(READ);
	SPI_Byte(Addr>>16);
	SPI_Byte(Addr>>8);
	SPI_Byte((unsigned char) Addr);
	for(i=0;i<len;i++)
	{
		para[i] = SPI_Byte(0);
	}
	SPI_CS25=1;
}

#endif
unsigned int  SPI2_byte_read(void)
{
	unsigned char tmp1 = 0,tmp2=0, i,bit;
	unsigned int temp;

	HEF4021_PL=0;
	delay_nus(1);
	HEF4021_PL=1;
	delay_nus(1);
	HEF4021_PL=0;

	for (bit = 0x80; bit; bit >>= 1)
	{
		delay_nus(1);
		HEF4021_CLOCK = 1;
		if(HEF4021_MISO==1) //�������λ
			tmp1|= bit;

		delay_nus(1);
		HEF4021_CLOCK = 0;//MPSCKΪ�߽���bit
	}

	for (bit = 0x80; bit; bit >>= 1)
	{
		delay_nus(1);
		HEF4021_CLOCK = 1;
		if(HEF4021_MISO==1) //�������λ
			tmp2|= bit;
		delay_nus(1);
		HEF4021_CLOCK = 0;//MPSCKΪ�߽���bit
	}
	temp=(unsigned int)tmp1*256+tmp2;
	return temp;
}

