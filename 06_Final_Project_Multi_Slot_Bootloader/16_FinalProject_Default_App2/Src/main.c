#include <stdio.h>
#include "stm32f4xx.h"
#include "fpu.h"
#include "uart.h"
#include "timebase.h"
#include "bsp.h"

/*
Module: DRIVERS
 * FPU = Floating Point Computation, Core peripheral of the arm architecture
 * UART
 * GPIO (BSP) =Board Support Package
 * TIMEBASE
 * ADC
*/


//0X08004000

#define VECT_TAB_BASE_ADDRESS FLASH_BASE
#define VECT_TAB_OFFSET 0x8000


bool btn_state;

int main(void)
{
    // Enable FPU
	fpu_enable();

	// Initialize UART
	debug_uart_init();

	//Initialize timebase
	timebase_init();

	//Initialize LED
	led_init();

	//Initialize Push Button
	button_init();



    while(1)
    {
    	printf("Update is Running....\n\r");

    }
}

void SystemInit(void)
{
	SCB -> VTOR = VECT_TAB_BASE_ADDRESS | VECT_TAB_OFFSET;

}
