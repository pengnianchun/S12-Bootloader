#ifndef GLOBAL_H__
	#define GLOBAL_H__
	
#ifdef GLOBAL_EXTERN
#define EXTERN
#else
#define EXTERN extern
#endif
#include "S12_COMMON.h"

EXTERN volatile BOOL CAN_CanRxMsgFlag;//���յ�CAN���ݺ�ı�־
EXTERN volatile  char TimeOutConfig;
EXTERN volatile  unsigned int RunTime;
EXTERN volatile char CanStop;

#endif