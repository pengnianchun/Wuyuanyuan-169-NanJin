#ifndef __SPI25LC1024_h
#define __SPI25LC1024_h



#define READ 0x03
#define WRITE 0x02
#define WREN 0x06
#define WRDI 0x04
#define RDSR 0x05
#define WRSR 0x01
#define PE 0x42
#define SE 0xd8
#define CE 0xc7
#define RDID 0xab
#define DPD 0xb9

  

#define USER_HARDWARE_SPI   1
void spi_init(void);
unsigned int  SPI2_byte_read(void);
void EnableWriteOperations(void);
void Write_mem(unsigned long Addr,void *data,unsigned char len);
void read_mem(unsigned long Addr,void *data,unsigned char len);
void clear_mem(unsigned long Addr,unsigned int len);
#endif