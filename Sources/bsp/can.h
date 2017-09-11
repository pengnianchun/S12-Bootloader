#ifndef CAN_H__
    #define   CAN_H__      
#include "S12_COMMON.h"



#define CAN_EN				      PORTAB_PA3
#define CAN_BTS             PTP_PTP3
#define CAN_ERR             PTP_PTP6

typedef enum{
	NORMAL_MODE = 0,
	STANDBY_MODE = 1,
	GO_TO_SLEEP_MODE = 2,
}can_mode_t;

#define CMD_WIDTH   4         //不要修改
#define CMD_MASK    0x0F       //不要修改

extern int IsRxEmpty(void);
extern UINT8 Getchar(void);
extern void CAN_BOOT_ExecutiveCommand(void);
extern UINT8 CheckApp(void);
extern void CanInit(void); 
extern void can_chip_mode_switch(can_mode_t mode);
#endif