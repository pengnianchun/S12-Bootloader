#ifndef CAN_H__
    #define   CAN_H__      
#include "S12_COMMON.h"



#define CMD_WIDTH   4         //��Ҫ�޸�
#define CMD_MASK    0x0F       //��Ҫ�޸�

extern int IsRxEmpty(void);
extern UINT8 Getchar(void);
extern void CAN_BOOT_ExecutiveCommand(void);
extern UINT8 CheckApp(void);
extern void CanInit(void); 
#endif