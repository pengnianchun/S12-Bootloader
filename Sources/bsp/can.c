#include <hidef.h>
#include <stdio.h>
#include <string.h>
#include "derivative.h" /* include peripheral declarations */
#include "S12_COMMON.h"
#include "global.h"
#include "can.h"
#include "config.h"
#include "pflash.h"

typedef struct     //Can报文结构
{
    unsigned long id;
    BOOL RTR;
    unsigned char data[8];
    unsigned char len;
    unsigned char prty;         
}can_msg;
can_msg msg_get;                  

/*************************************************************/
/*                        初始化CAN                         */
/*************************************************************/

void CanInit(void) 
{
	//相关变量初始化
	CAN_CanRxMsgFlag = 0;
	CanStop = 0;
	memset(&msg_get,0,sizeof(can_msg));
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
 // CANBTR0_SJW = 0;            //设置同步
 // CANBTR0_BRP = 3;            //设置波特率 
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
 //CANBTR1 = 0x1c;
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

/*************************************************************/
/*                       CAN发送                            */
/*************************************************************/
unsigned char CAN0SendFrame(unsigned long id, unsigned char priority, unsigned char length, unsigned char *txdata )
{

	unsigned char index;
	unsigned char txbuffer = {0};

	if (!CANTFLG)              /* Is Transmit Buffer full?? */
		return 0;

	CANTBSEL = CANTFLG;       /* Select lowest empty buffer */
	txbuffer = CANTBSEL;		/* Backup selected buffer */

	/* Load Id to IDR Registers */
	*((unsigned long *) ((unsigned long)(&CANTXIDR0)))= id;


	for (index=0; index<length; index++)
	{
		*(&CANTXDSR0 + index) = txdata[index];  /* Load data to Tx buffer Data Segment Registers*/
	}

	CANTXDLR = length;                          /* Set Data Length Code */
	CANTXTBPR = priority;                       /* Set Priority */

	CANTFLG = txbuffer;	                     /* Start transmission */
	// while ( (CANTFLG & txbuffer) != txbuffer);  /* Wait for Transmission completion */
	return 0;
}
Bool MSCANSendMsg(can_msg msg)
{
  unsigned char send_buf, sp;
  
  // 检查数据长度
  if(msg.len > 8)
    return(FALSE);

  // 检查总线时钟
  if(CANCTL0_SYNCH==0)
    return(FALSE);

  send_buf = 0;
  do
  {
    // 寻找空闲的缓冲器
    CANTBSEL=CANTFLG;
    send_buf=CANTBSEL;
  }
  
  while(!send_buf); 
  
  // 写入标识符
  //CANTXIDR0 = (unsigned char)(msg.id>>3);
  //CANTXIDR1 = (unsigned char)(msg.id<<5);
  //*((unsigned long *) ((unsigned long)(&CANTXIDR0)))= msg.id;
  CANTXIDR3_ID =  msg.id&0x0000007F;
  CANTXIDR2 = (msg.id>>7)&0x000000FF;
  CANTXIDR1_ID_15 = (msg.id>>15)&0x00000007;
  CANTXIDR1_ID_18 = (msg.id>>18)&0x00000007;
  CANTXIDR0 = (msg.id>>21)&0x000000FF;
  CANTXIDR1_IDE =1;//设置成扩展帧模式
  CANTXIDR3_RTR = 0;//设置为数据帧
  if(msg.RTR)
    // RTR = 阴性
    CANTXIDR1 |= 0x10;
    
  // 写入数据
  for(sp = 0; sp < msg.len; sp++)
    *((&CANTXDSR0)+sp) = msg.data[sp];
    
  // 写入数据长度
  CANTXDLR = msg.len; 
  
  // 写入优先级
  CANTXTBPR = msg.prty;
  //CANTXIDR1_IDE =1;
  // 清 TXx 标志 (缓冲器准备发送)
  CANTFLG = send_buf;
  
  return(TRUE);
  
}
/*************************************************************/
/*                       CAN接收                            */
/*************************************************************/
static Bool MSCANGetMsg(can_msg *msg)
{
  unsigned char sp2;
  unsigned char IDtemp[4];
  // 检测接收标志
  if(!(CANRFLG_RXF))
    return(FALSE);
  
  // 检测 CAN协议报文模式 （一般/扩展） 标识符
  if(CANRXIDR1_IDE)
    // IDE = Recessive (Extended Mode)
    //return(FALSE);

  // 读标识符
  //msg->id = (unsigned int)(CANRXIDR0<<3) | 
  //          (unsigned char)(CANRXIDR1>>5);
  //msg->id = *((unsigned long *) ((unsigned long)(&CANRXIDR0))) ;
  IDtemp[0]=CANRXIDR0;
  IDtemp[1]=CANRXIDR1;
  IDtemp[2]=CANRXIDR2;
  IDtemp[3]=CANRXIDR3;


	  
	  msg->id=(((unsigned long)IDtemp[2])<<7)|(((unsigned long)IDtemp[3])>>1);
	  msg->id=msg->id|(((unsigned long)(IDtemp[1]&0x07))<<15);
	  msg->id=msg->id|(((unsigned long)((IDtemp[1]&0xE0)>>5))<<18);
	  msg->id=msg->id|(((unsigned long)(IDtemp[0]))<<21);
  if(CANRXIDR1&0x10)
    msg->RTR = TRUE;
  else
    msg->RTR = FALSE;
  
  // 读取数据长度 
  msg->len = CANRXDLR_DLC;
  
  // 读取数据
  for(sp2 = 0; sp2 < msg->len; sp2++)
    msg->data[sp2] = *((&CANRXDSR0)+sp2);

  // 清 RXF 标志位 (缓冲器准备接收)
  CANRFLG = 0x01;

  return(TRUE);
}

/*************************************************************/
/*                      中断接收函数                         */
/*************************************************************/

#pragma CODE_SEG __NEAR_SEG NON_BANKED
void interrupt CAN_receive(void) 
{
      if(MSCANGetMsg(&msg_get)) 
      {
        // 接收新信息
        unsigned long can_addr;
		can_addr = msg_get.id>>CMD_WIDTH;//ID的bit4~bit15位为节点地址)
		if(CAN_TX_ID != can_addr)
			return ;
        	CAN_CanRxMsgFlag = 1;
      }
      else 
      {
       //for(;;);
      }
}
#pragma CODE_SEG DEFAULT
/*************************************************************************************/

#define EraseFlashID        0x03//擦出APP储存扇区数据
#define WriteBlockFlashID   0x06//以多字节形式写数据
#define ReadBlockFlashID    0x08//以多字节形式读数据
#define BlockWriteInfoID    0x05//设置多字节写数据相关参数（写起始地址，数据量）
#define BlockReadInfoID     0x07//设置多字节数据读相关参数（读起始地址，数据量）
#define OnlineCheckID       0x01//检测节点是否在线
#define CmdSuccessID        0x0A//命令执行成功
#define CmdFaildID          0x00//命令执行失败
#define SetBaudRateID       0x04//设置节点波特率
#define ExcuteAppID         0x09//执行应用程序


#define BUFFER_SIZE		0x400
typedef struct 
{
	char buf[BUFFER_SIZE];
	int r;
	int w;
}
CAN_DATA_FIFO;


typedef void (*fCommandHandle)(can_msg *pRxMessage);
typedef struct _ExecutiveCommandType
{
	unsigned int ID;
	fCommandHandle fHandle;
}
ExecutiveCommandType;

volatile CAN_DATA_FIFO rx_buf;
void CAN_BOOT_ExecutiveCommandHandle(can_msg *pRxMessage,ExecutiveCommandType *Table,int size)
{
	int i;
	 
	for (i = 0; i<size; i++)
	{
		if ((pRxMessage->id&CMD_MASK) == Table[i].ID)
		{
			Table[i].fHandle(pRxMessage);
			return ;
		}
	}
}
/**
 * 校验函数，返回版本信息，停止自动跳转到APP
 */
void ExecutiveCheckHandle(can_msg *pRxMessage)
{
	can_msg tx_msg;
	TIE   = 0;//关定时中断取消计时
	tx_msg.id = (CAN_TX_ID<<4) | OnlineCheckID;
	tx_msg.data[0] = VERSIONS_MAJOR>>8;
	tx_msg.data[1] = VERSIONS_MAJOR;
	tx_msg.data[2] = VERSIONS_MINOR>>8;
	tx_msg.data[3] = VERSIONS_MINOR;
	tx_msg.data[4] = 0;
	tx_msg.data[5] = 0;
	tx_msg.data[6] = 0;
	tx_msg.data[7] = CAN_BL_BOOT;
	tx_msg.len = 8;
	(void)MSCANSendMsg(tx_msg);
}
/**
 * 接收过程不执行烧写防止中断影响flash操作
 */
int IsRxEmpty(void)
{
  _FEED_COP();
	if (CanStop == 0){
		return 1;
	}
	return rx_buf.w == rx_buf.r;
}
UINT8 Getchar(void)
{
	can_msg tx_msg;
	while(IsRxEmpty())
	{
		if (1 == CanStop){
			tx_msg.id = (CAN_TX_ID<<4) | WriteBlockFlashID;
			tx_msg.len = 0;
			(void)MSCANSendMsg(tx_msg);
			CanStop = 0;
		}
		CAN_BOOT_ExecutiveCommand();
	}
	return rx_buf.buf[(rx_buf.r++)&(BUFFER_SIZE-1)];
}

void GetRxBuffer(unsigned  char * buffer, int len)
{
	int i;
	i= 0;
	while(i<len) 
	{
		buffer[i++] = Getchar();
	}
}

void ExecutiveEraseFlashHandle(can_msg *pRxMessage)
{
	unsigned long addr;
	ERROR_TYPE err = EraseFlashID;
	can_msg tx_msg;
	tx_msg.id = CAN_TX_ID<<4;
	tx_msg.id |= EraseFlashID;
	tx_msg.len = 0;
	
	for (addr = APP_STAR_ADDR;addr<APP_MAX_ADDR;){
		err = PFlash_EraseSector(addr);
		if(err != noErr)
			break;
		addr += 0x200;
		_FEED_COP();
	}
	(void)MSCANSendMsg(tx_msg);
	
}
static unsigned long data_index = 0,data_size = 0;
void ExecutiveBlockWriteInfoHandle(can_msg *pRxMessage)
{
	can_msg tx_msg;
	data_index = 0;
	data_size = pRxMessage->data[4];
	data_size <<=8;
	data_size = pRxMessage->data[5];
	data_size <<=8;
	data_size = pRxMessage->data[6];
	data_size <<=8;
	data_size += pRxMessage->data[7];
	tx_msg.id = (CAN_TX_ID<<4) | BlockWriteInfoID;
	tx_msg.len = 0;
	(void)MSCANSendMsg(tx_msg);
}
void ExecutiveWriteBlockFlashHandle(can_msg *pRxMessage)
{
	int i;
	char len;
	len = pRxMessage->len;
	
	if(data_index<data_size)         
	{
		for (i=0;i<pRxMessage->len;i++){
			data_index++;
			if(data_index+2<=data_size){
				rx_buf.buf[(rx_buf.w++) & (BUFFER_SIZE-1)] = pRxMessage->data[i];
			}
		}
	}
	if(data_index>=data_size){
		CanStop = 1;
	}
}

UINT8 CheckApp(void)
{
	UINT8   out;
	UINT8 *Src;
	int i;
	unsigned char tmp[8];
	Src = (UINT8 *)0xEE00;
	for(i=0;i<8;i++){
		tmp[i] = Src[i];
	}
	
	out = strncmp(APP_CHECK_STRING,Src,8);
	return out;
}
void ExecutiveAppHandle(can_msg *pRxMessage) {
	UINT8 tmp;
	tmp = CheckApp();
	if (tmp == 0){
     DisableInterrupts;
	  asm call 0xC000,00;
	}
}
static ExecutiveCommandType commandTable[]=
{
	{OnlineCheckID,ExecutiveCheckHandle},
	{EraseFlashID,ExecutiveEraseFlashHandle},
	{BlockWriteInfoID,ExecutiveBlockWriteInfoHandle},
	{WriteBlockFlashID,ExecutiveWriteBlockFlashHandle},
	{ExcuteAppID,ExecutiveAppHandle},
};

void CAN_BOOT_ExecutiveCommand(void)
{
	if (CAN_CanRxMsgFlag){
		CAN_BOOT_ExecutiveCommandHandle(&msg_get,commandTable,sizeof(commandTable)/sizeof(ExecutiveCommandType));
		CAN_CanRxMsgFlag = 0;
	}
}
