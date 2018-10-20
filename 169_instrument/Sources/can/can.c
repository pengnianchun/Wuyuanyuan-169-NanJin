#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

#include "can.h"
#include "main.h"
void CANInit(void)
{
	can_chip_mode_switch(NORMAL_MODE);//!<设置进入正常模式
	CANCTL0 = 0x01;           /* Enter Initialization Mode
                               *
                               *  0b00000001
                               *    ||||||||__ Enter Initialization Mode
                               *    |||||||___ Sleep Mode Request bit
                               *    ||||||____ Wake-Up disabled
                               *    |||||_____ Time stamping disabled
                               *    ||||______ Synchronized Status
                               *    |||_______ CAN not affected by Wait
                               *    ||________ Receiver Active Status bit
                               *    |_________ Received Frame Flag bit
                               */

	while (!(CANCTL1&0x01))
	{
		_FEED_COP();
	};	/* Wait for Initialization Mode acknowledge
                                             * INITRQ bit = 1
                                             */

	CANCTL1 = 0xC0;           /* Enable MSCAN module and LoopBack Mode
                               *
                               *  0b10100000
                               *    ||||||||__ Initialization Mode Acknowledge
                               *    |||||||___ Sleep Mode Acknowledge
                               *    ||||||____ Wake-up low-pass filter disabled
                               *    |||||_____ Unimplemented
                               *    ||||______ Listen Only Mode disabled
                               *    |||_______ Loop Back Mode enabled
                               *    ||________ Ext Osc/Xtal as Clock Source
                               *    |_________ MSCAN Module enabled
                               */

	CANBTR0 = 0xCF;           /* Synch Jump = 3 Tq clock Cycles
                               *
                               *  0b11000111
                               *    ||||||||__
                               *    |||||||___\
                               *    ||||||____ |
                               *    |||||_____ |_ CAN Clock Prescaler = 7
                               *    ||||______ |
                               *    |||_______ |
                               *    ||________/
                               *    |_________>- SJW = 3
                               */

	CANBTR1 = 0x12;	          /* Set Number of samples per bit, TSEG1 and TSEG2
                               *
                               *  0b00111010
                               *    ||||||||__
                               *    |||||||___|
                               *    ||||||____|- TSEG1 = 10
                               *    |||||_____|
                               *    ||||______
                               *    |||_______\_ TSEG2 = 3
                               *    ||________/
                               *    |_________ One sample per bit
                               */



	/* Acceptance Filters */
	CANIDAC = 0x00U;
	/* CANIDAR0: AC7=1,AC6=1,AC5=1,AC4=1,AC3=1,AC2=1,AC1=1,AC0=1 */
	CANIDAR0 = 0x00U;
	/* CANIDAR1: AC7=1,AC6=1,AC5=1,AC4=1,AC3=1,AC2=1,AC1=1,AC0=1 */
	CANIDAR1 = 0x00U;
	/* CANIDAR2: AC7=1,AC6=1,AC5=1,AC4=1,AC3=1,AC2=1,AC1=1,AC0=1 */
	CANIDAR2 = 0x00U;
	/* CANIDAR3: AC7=1,AC6=1,AC5=1,AC4=1,AC3=1,AC2=1,AC1=1,AC0=1 */
	CANIDAR3 = 0x00U;
	/* CANIDAR4: AC7=1,AC6=1,AC5=1,AC4=1,AC3=1,AC2=1,AC1=1,AC0=1 */
	CANIDAR4 = 0x00U;
	/* CANIDAR5: AC7=1,AC6=1,AC5=1,AC4=1,AC3=1,AC2=1,AC1=1,AC0=1 */
	CANIDAR5 = 0x00U;
	/* CANIDAR6: AC7=1,AC6=1,AC5=1,AC4=1,AC3=1,AC2=1,AC1=1,AC0=1 */
	CANIDAR6 = 0x00U;
	/* CANIDAR7: AC7=1,AC6=1,AC5=1,AC4=1,AC3=1,AC2=1,AC1=1,AC0=1 */
	CANIDAR7 = 0x00U;
	/* CANIDMR0: AM7=0,AM6=0,AM5=0,AM4=0,AM3=0,AM2=0,AM1=0,AM0=0 */
	CANIDMR0 = 0xFFU;
	/* CANIDMR1: AM7=0,AM6=0,AM5=0,AM4=0,AM3=0,AM2=0,AM1=0,AM0=0 */
	CANIDMR1 = 0xFFU;
	/* CANIDMR2: AM7=0,AM6=0,AM5=0,AM4=0,AM3=0,AM2=0,AM1=0,AM0=0 */
	CANIDMR2 = 0xFFU;
	/* CANIDMR3: AM7=0,AM6=0,AM5=0,AM4=0,AM3=0,AM2=0,AM1=0,AM0=0 */
	CANIDMR3 = 0xFFU;
	/* CANIDMR4: AM7=0,AM6=0,AM5=0,AM4=0,AM3=0,AM2=0,AM1=0,AM0=0 */
	CANIDMR4 = 0x00U;
	/* CANIDMR5: AM7=0,AM6=0,AM5=0,AM4=0,AM3=0,AM2=0,AM1=0,AM0=0 */
	CANIDMR5 = 0x00U;
	/* CANIDMR6: AM7=0,AM6=0,AM5=0,AM4=0,AM3=0,AM2=0,AM1=0,AM0=0 */
	CANIDMR6 = 0x00U;
	/* CANIDMR7: AM7=0,AM6=0,AM5=0,AM4=0,AM3=0,AM2=0,AM1=0,AM0=0 */
	CANIDMR7 = 0x00U;

	CANCTL0 = 0x00;            /* Exit Initialization Mode Request */
	while ((CANCTL1&0x01) != 0)
	{
		_FEED_COP();
	};	/* Wait for Normal Mode */

	while(!(CANCTL0&0x10))_FEED_COP();
	CANRFLG = 0xC3;
	CANRIER = 0x01;
}
unsigned char CAN0SendFrame(unsigned long id, unsigned char priority, unsigned char length, unsigned char *txdata )
{

	unsigned char index;
	unsigned char txbuffer = {0};

	if (!CANTFLG)              /* Is Transmit Buffer full?? */
		return ERR_BUFFER_FULL;

	CANTBSEL = CANTFLG;       /* Select lowest empty buffer */
	txbuffer = CANTBSEL;		/* Backup selected buffer */

	/* Load Id to IDR Registers */
	//*((unsigned long *) ((unsigned long)(&CANTXIDR0)))= id;
	CANTXIDR3_ID =	id&0x0000007F;
	CANTXIDR2 = (id>>7)&0x000000FF;
	CANTXIDR1_ID_15 = (id>>15)&0x00000007;
	CANTXIDR1_ID_18 = (id>>18)&0x00000007;
	CANTXIDR0 = (id>>21)&0x000000FF;
	CANTXIDR1_IDE =1;//设置成扩展帧模式
	CANTXIDR3_RTR = 0;//设置为数据帧


	for (index=0; index<length; index++)
	{
		*(&CANTXDSR0 + index) = txdata[index];  /* Load data to Tx buffer Data Segment Registers*/
	}

	CANTXDLR = length;                          /* Set Data Length Code */
	CANTXTBPR = priority;                       /* Set Priority */

	CANTFLG = txbuffer;	                     /* Start transmission */
	// while ( (CANTFLG & txbuffer) != txbuffer);  /* Wait for Transmission completion */
	return NO_ERR;
}

void can_chip_mode_switch(can_mode_t mode)
{
	switch(mode)
	{
		case NORMAL_MODE:
			CAN_EN = 1;
			CAN_BTS = 1;
			break;
		case STANDBY_MODE:
			CAN_EN = 0;
			CAN_BTS = 0;
			break;
		case GO_TO_SLEEP_MODE:
			CAN_EN = 1;
			CAN_BTS = 0;
			break;
		default:break;
	}
}

