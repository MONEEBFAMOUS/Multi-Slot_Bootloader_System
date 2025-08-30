/*
 * timebase.c
 *
 *  Created on: Aug 24, 2025
 *      Author: Engr_Moneeb
 */

#include <timebase_min.h>
#include "stm32f4xx.h"

#define CTRL_ENABLE (1U<<0)
#define CTRL_TICKINT (1U<<1)
#define CTRL_CLCKSRC (1U<<2)
#define CTRL_COUNTFLAG (1U<<16)

#define ONE_SEC_LOAD 16000000 //Change this value to 16000 sixteen thousand in order to convert the systick in milli second.

#define ONE_MSEC_LOAD 16000

#define MAX_DELAY 0xFFFFFFFF

#define TICK_FREQ 1

volatile uint32_t g_curr_tick;
volatile uint32_t g_curr_tick_p;

//Delay in seconds
void delay(uint32_t delay)
{
	uint32_t tickstart = get_tick();
	uint32_t wait = delay;

	if (wait<MAX_DELAY)
	{
		wait += (uint32_t) TICK_FREQ;
	}
	while((get_tick() - tickstart) < wait){}

}

uint32_t get_tick(void)
{
	__disable_irq();
	g_curr_tick_p = g_curr_tick;
	__enable_irq();

	return g_curr_tick += TICK_FREQ;
}

static void tick_increment(void)
{
	g_curr_tick += TICK_FREQ;

}

void SysTick_Handler(void)
{
	tick_increment();
}
