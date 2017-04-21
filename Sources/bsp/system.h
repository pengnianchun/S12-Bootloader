#ifndef SYSTEM_H__
	#define SYSTEM_H__

//PLLCLK=2¡ÁOSCCLK¡Á(SYNDIV+1)/(REFDIV+1), fbus=PLLCLK/2
#define CLOCK_OSC		(8000000ul)
#define CLOCK_REFDIV	(0x01)
#define CLOCK_SYNDIV	(0x05)
#define CLOCK_BUS		(CLOCK_OSC*(CLOCK_SYNDIV+1)/(CLOCK_REFDIV+1))


extern void SystemClockInit(void);
extern void initialize_TIM(void);
extern void delay1ms(unsigned int n);

#endif