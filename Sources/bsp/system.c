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
	CPMUCOP = 0x00;//ʹ�ܿ��Ź�
}

/************************************************************/
/*                    ��ʼ��TIMģ��                         */
/************************************************************/
void initialize_TIM(void)
{
  TimeOutConfig = 0;
  RunTime = 0;
  TSCR1_TFFCA = 1;  // ��ʱ����־λ�������
  TSCR1_TEN = 1;    // ��ʱ��ʹ��λ. 1=����ʱ����������; 0=ʹ����ʱ����������(����������)
  TIOS  = 0xff;      //ָ������ͨ��Ϊ����ȽϷ�ʽ
  TCTL1 = 0x00;	    // ���ĸ�ͨ������Ϊ��ʱ����������ŶϿ�
  TCTL2 = 0x00;     // ǰ�ĸ�ͨ������Ϊ��ʱ����������ŶϿ�
  TIE   = TIE_C1I_MASK; 		// �����ж�1
  TSCR2 = 0x06;	    // Ԥ��Ƶϵ��pr2-pr0:110,ʱ������Ϊ4us,
  TFLG1 = 0xff;	    // �����IC/OC�жϱ�־λ
  TFLG2 = 0xff;     // ������ɶ�ʱ���жϱ�־λ
  //TC1 = TCNT + 375;
}
/*************************************************************/
/*                         ��ʱ����                          */
/*************************************************************/
void delay2ms(unsigned int n) 
{
    unsigned int i;
    for(i=0;i<n;i++) 
    {
        TFLG1_C0F = 1;              //�����־λ
        TC0 = TCNT + 375;           //��������Ƚ�ʱ��Ϊ1ms
        while(TFLG1_C0F == 0);      //�ȴ���ֱ����������Ƚ��¼�
    }
}
/*************************************************************/
/*                      ��ʱ�жϺ���                         */
/*************************************************************/

#pragma CODE_SEG __NEAR_SEG NON_BANKED
interrupt void T1_inter(void)
{
  if(TFLG1_C1F == 1)
  {
    TFLG1_C1F = 1;
    TC1 = TCNT + 375;         //��������Ƚ�ʱ��Ϊ0.001s
  }
  TimeOutConfig = 1;
  RunTime++;
  
}
#pragma CODE_SEG DEFAULT