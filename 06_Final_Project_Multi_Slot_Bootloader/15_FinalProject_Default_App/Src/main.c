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

#define VECTOR_TABLE_BASE_ADDRESS FLASH_BASE
#define VECTOR_TABLE_OFFSET 0x4000


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
    	printf("Default App is Running....\n\r");

    }
}

void SystemInit(void)
{
	SCB -> VTOR = VECTOR_TABLE_BASE_ADDRESS | VECTOR_TABLE_OFFSET;

}
