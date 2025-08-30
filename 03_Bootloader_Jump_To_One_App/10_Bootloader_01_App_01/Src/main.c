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

#define VECTOR_TABLE_BASE_ADDRESS FLASH_BASE //Vector table base address is the just the flash base address, which is the start of flash address.
#define VECTOR_TABLE_OFFSET	0x8000 //We are placing our application at an ofset of 8000 since our APPLICATION_ADDRESS is 0x08008000


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


	printf("Application Started Successfully...\n\r");


    while(1)
    {

    	printf("Application 1 Running...\n\r");

    }
}


//Startup_stm32f407 weak function called SystemInit(void)
//We dont have to call SystemInit anywhere the Reset Hanlder already calls it like an interrupt request Handler.

void SystemInit(void)
{
	//SCB Stands for System Control Block, where as VTOR stands for Vector Table Offset register
	SCB -> VTOR = VECTOR_TABLE_BASE_ADDRESS | VECTOR_TABLE_OFFSET;
}
