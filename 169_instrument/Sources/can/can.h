#ifndef CAN_H_
  #define CAN_H_

typedef enum{
	NORMAL_MODE = 0,
	STANDBY_MODE = 1,
	GO_TO_SLEEP_MODE = 2,
}can_mode_t;
extern void CANInit(void);
extern unsigned char CAN0SendFrame(unsigned long id, unsigned char priority, unsigned char length, unsigned char *txdata );
extern void can_chip_mode_switch(can_mode_t mode);
#endif