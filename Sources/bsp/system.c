#include <MC9S12G128.h>                /* I/O map for MC9S12G128CLL */
#include "global.h"
#include "system.h"

void SystemClockInit(void)
{
	/* CPMUPROT: PROT=0 */
	CPMUPROT = 0x26U;                    /* Disable protection of clock configuration registers */
	/* CPMUCLKS: PSTP=0 */
	CPMUCLKS &= (unsigned char)~(unsigned char)CPMUCLKS_PSTP_MASK;                     
	/* CPMUCLKS: PLLSEL=1 */
	CPMUCLKS |= (unsigned char)CPMUCLKS_PLLSEL_MASK;    /* Enable the PLL to allow write to divider registers */
	/* CPMUREFDIV: REFFRQ1=0,REFFRQ0=1,REFDIV3=0,REFDIV2=0,REFDIV1=0,REFDIV0=1 */
	CPMUREFDIV_REFDIV = CLOCK_REFDIV;
	CPMUREFDIV_REFFRQ = 0X01; /* Set the divider register */                
	/* CPMUSYNR: VCOFRQ1=0,VCOFRQ0=0,SYNDIV5=0,SYNDIV4=0,SYNDIV3=0,SYNDIV2=1,SYNDIV1=0,SYNDIV0=1 */
	CPMUSYNR_SYNDIV = CLOCK_SYNDIV; /* Set the multiplier register */
	/* CPMUPOSTDIV: POSTDIV4=0,POSTDIV3=0,POSTDIV2=0,POSTDIV1=0,POSTDIV0=0 */
	CPMUPOSTDIV = 0x00U;                 /* Set the post divider register */
	/* CPMUOSC: OSCE=1,OSCBW=0,OSCPINS_EN=0,OSCFILT=0 */
	CPMUOSC = 0x80U;                     /* Enable the oscillator */
	/* CPMUPLL: FM1=0,FM0=0 */
	CPMUPLL = 0x00U;                     /* Set the PLL frequency modulation */
	while(CPMUFLG_UPOSC == 0U) {         /* Wait until the oscillator is qualified by the PLL */
	}
	/* CPMUPROT: PROT=0 */
	CPMUPROT = 0x00U;                    /* Enable protection of clock configuration registers */  
	CPMUCOP = 0x00;//使能看门狗
}

/************************************************************/
/*                    初始化TIM模块                         */
/************************************************************/
void initialize_TIM(void)
{
  TimeOutConfig = 0;
  RunTime = 0;
  TSCR1_TFFCA = 1;  // 定时器标志位快速清除
  TSCR1_TEN = 1;    // 定时器使能位. 1=允许定时器正常工作; 0=使主定时器不起作用(包括计数器)
  TIOS  = 0xff;      //指定所有通道为输出比较方式
  TCTL1 = 0x00;	    // 后四个通道设置为定时器与输出引脚断开
  TCTL2 = 0x00;     // 前四个通道设置为定时器与输出引脚断开
  TIE   = TIE_C1I_MASK; 		// 开启中断1
  TSCR2 = 0x06;	    // 预分频系数pr2-pr0:110,时钟周期为4us,
  TFLG1 = 0xff;	    // 清除各IC/OC中断标志位
  TFLG2 = 0xff;     // 清除自由定时器中断标志位
  //TC1 = TCNT + 375;
}
/*************************************************************/
/*                         延时函数                          */
/*************************************************************/
void delay2ms(unsigned int n) 
{
    unsigned int i;
    for(i=0;i<n;i++) 
    {
        TFLG1_C0F = 1;              //清除标志位
        TC0 = TCNT + 375;           //设置输出比较时间为1ms
        while(TFLG1_C0F == 0);      //等待，直到发生输出比较事件
    }
}
/*************************************************************/
/*                      计时中断函数                         */
/*************************************************************/

#pragma CODE_SEG __NEAR_SEG NON_BANKED
interrupt void T1_inter(void)
{
  if(TFLG1_C1F == 1)
  {
    TFLG1_C1F = 1;
    TC1 = TCNT + 375;         //设置输出比较时间为0.001s
  }
  TimeOutConfig = 1;
  RunTime++;
  
}
#pragma CODE_SEG DEFAULT