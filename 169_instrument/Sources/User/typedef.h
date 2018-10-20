#ifndef TYPEDEF_H
#define TYPEDEF_H

#define BIT(x)	           (1 << (x))
#define SETBIT(x, y)   	   (x |= y)
#define CLEARBIT(x, y) 	   (x &= ~y)
#define CHECKBIT(x, y) 	   (x & y)

#define BCD2BIN(val)  (((val) & 0x0f) + ((val)>>4)*10)
#define BIN2BCD(val)  ((((val)/10)<<4) + (val)%10)

// ***** Define I/O pins *****
#define B7 0x80
#define B6 0x40
#define B5 0x20
#define B4 0x10
#define B3 0x08
#define B2 0x04
#define B1 0x02
#define B0 0x01

/*Warning Disable*/
#pragma MESSAGE DISABLE C1106		//Non-Standard Bitfields

/******************************************************************************
Standard Type Definitions

These macros allow for easier porting to other compilers. If porting change
these defines to the required values for the chosen compiler.
******************************************************************************/
typedef unsigned char   tU08;   /*unsigned 8 bit definition */
typedef unsigned int    tU16;   /*unsigned 16 bit definition*/
typedef unsigned long   tU32;   /*unsigned 32 bit definition*/

typedef signed char     tS08;   /*signed 8 bit definition */
typedef signed int      tS16;   /*signed 16 bit definition*/
typedef signed long     tS32;   /*signed 32 bit definition*/

/******************************************************************************
Macros FOR legacy compatibility.
******************************************************************************/
typedef tU08   UINT8,U8;      /* unsigned 8-bit  */
typedef tU16   UINT16,U16;     /* unsigned 16-bit */
typedef tU32   UINT32,U32;     /* unsigned 32-bit */
typedef tS08   INT8,S8;       /* signed 8-bit    */
typedef tS16   INT16,S16;      /* signed 16-bit   */
typedef tS32   INT32,S32;      /* signed 32-bit   */

/******************************************************************************
Macros to allow generic register / bit access.
******************************************************************************/
typedef union uREG08    /*8 bit register with byte and bit access*/
  {
  tU08  byte;           /*access whole register e.g. var.byte   = 0xFF;*/
  struct                /*access bit at a time  e.g. var.bit._7 = 1;   */
    {
    tU08 _0 :1;
    tU08 _1 :1;
    tU08 _2 :1;
    tU08 _3 :1;
    tU08 _4 :1;
    tU08 _5 :1;
    tU08 _6 :1;
    tU08 _7 :1;  
    }bit;
  }tREG08;

typedef union uREG16    /*16 bit register with word and byte access*/
  {
  tU16  word;           /*access whole word    */
  struct                /*access byte at a time or individual bits in the bytes */
    {
    tREG08  msb;
    tREG08  lsb;
    }byte;
  }tREG16;
  
typedef union uWORD    /*16 bit word with byte access*/
  {
  tU16  word;           /*access whole word    */
  struct                /*access byte at a time*/
    {
    tU08  msb;
    tU08  lsb;
    }byte;
  }tWORD;

/******************************************************************************
Common Bit masks
******************************************************************************/

#define BIT_0    0x01    
#define BIT_1    0x01 << 1
#define BIT_2    0x01 << 2
#define BIT_3    0x01 << 3
#define BIT_4    0x01 << 4
#define BIT_5    0x01 << 5
#define BIT_6    0x01 << 6
#define BIT_7    0x01 << 7
#define BIT_8    0x01 << 8
#define BIT_9    0x01 << 9
#define BIT_A    0x01 << 10
#define BIT_B    0x01 << 11
#define BIT_C    0x01 << 12
#define BIT_D    0x01 << 13
#define BIT_E    0x01 << 14
#define BIT_F    0x01 << 15

#define BIT_10 BITA
#define BIT_11 BITB
#define BIT_12 BITC
#define BIT_13 BITD
#define BIT_14 BITE
#define BIT_15 BITF

/******************************************************************************
State Macros 
******************************************************************************/

/* NOTE: definitions for TRUE and FALSE can be found in Metrowerks STDTYPES.H*/

#ifndef CLEAR
#define CLEAR 0u
#endif

#ifndef SET
#define SET 1u
#endif

#ifndef FAIL
#define FAIL 0u
#endif
                        
#ifndef PASS
#define PASS 1u
#endif

/******************************************************************************
Macros for setting / clearing bits
******************************************************************************/
#define BITSETM(port,bit)  (port |= bit)
                        /* bit is value */
#define BITSET(port,bit)   (port |= (UINT8)1 << bit)
                        /* bit is mask */
#define BITCLRM(port,bit)  (port &= (UINT8)~bit)
                        /* bit is value */
#define BITCLR(port,bit)   (port &= (UINT8)~(1 << bit))

#endif
