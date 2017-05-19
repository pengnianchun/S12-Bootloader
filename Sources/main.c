#define GLOBAL_EXTERN
#include <hidef.h>      /* common defines and macros */
#include <stdio.h>
#include <string.h>

#include "derivative.h"      /* derivative-specific definitions */
#include "S12_COMMON.h"
#include "global.h"

#include "can.h"
#include "config.h"
#include "pflash.h"
#include "system.h"
#include "Srec.h"

const unsigned char flash_array[] @0xFF08 = {0xFF,0xFF,0xFF,0xFF,0xCF,0xFF,0xFF,0xFE};

#define  SPASS       0
#define  SERR        1
#define  SFileStart  2
#define  SFileEnd    3
#define  SInvalid    0xFF

#define __SEG_START_REF(a)  __SEG_START_ ## a
#define __SEG_END_REF(a)    __SEG_END_ ## a
#define __SEG_SIZE_REF(a)   __SEG_SIZE_ ## a
#define __SEG_START_DEF(a)  extern INT8 __SEG_START_REF (a) []
#define __SEG_END_DEF(a)    extern INT8 __SEG_END_REF   (a) []
#define __SEG_SIZE_DEF(a)   extern INT8 __SEG_SIZE_REF  (a) []

                             
__SEG_START_DEF (RAM_CODE);          
__SEG_END_DEF   (RAM_CODE);
__SEG_SIZE_DEF  (RAM_CODE);
/******************************************************************************/
static void CopyCodeToRAM(void)
{  
  UINT8 *Src;
  UINT8 *Dst;
  UINT16  SegSize;
  UINT16  x;
  
  //RAM code resides in Flash from 0xfc00 - 0xfeff
  Src = (UINT8 *)__SEG_START_REF(RAM_CODE);
  Dst = (UINT8 *)0x3D00;          //copied to RAM at 0x3D00
  SegSize = (UINT16)__SEG_SIZE_REF(RAM_CODE);
 
  for (x = 0; x < SegSize; x++)   //just copy a byte at a time
    *Dst++ = *Src++;
}



void main(void) {
    unsigned int  timeout;
	  int IsReset;
    DisableInterrupts;
    IVBR = 0xFFU; //设置中断映射 
    SystemClockInit();
  	Flash_Init();
  	CopyCodeToRAM();
    CanInit();
    initialize_TIM();
    EnableInterrupts;
	timeout = APP_TIMEOUT;
    if (CPMUFLG_PORF == 0) {
        IsReset = 1;
		timeout = 1000;
         //TIE   = 0;//关定时中断
         //ExecutiveEraseFlashHandle(NULL);//擦除程序区
    }
    
    
    for(;;){
		if(TimeOutConfig){
		   TimeOutConfig = 0;
		   timeout++;
		   if(timeout ==0){
		      UINT8 tmp;
		      TIE   = 0;//关定时中断
		        tmp = CheckApp();
		        if (tmp == 0){
		          DisableInterrupts;
		          asm call 0xC000,00;
		        }
		   }
		}
        CAN_BOOT_ExecutiveCommand();
		if (!IsRxEmpty())
		{
			ProgramFlash();
		}
    }
}
