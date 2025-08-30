#include <stdio.h>
#include "stm32f4xx.h"
#include "fpu.h"
#include "uart.h"

/*
Module: DRIVERS
 * FPU = Floating Point Computation, Core peripheral of the arm architecture
 * UART
 * GPIO
 * TIMEBASE
*/

#define GPIODEN (1U<<3)   // Shift 1 to position 3 register (Enable GPIOD clock)
#define PIN12 (1U<<12)    // Shift 1 to position 12 register (Green LED)
#define PIN13 (1U<<13)    // Shift 1 to position 13 register (Orange LED)
#define PIN14 (1U<<14)    // Shift 1 to position 14 register (Red LED)
#define PIN15 (1U<<15)    // Shift 1 to position 15 register (Blue LED)

int main(void)
{
    // Enable FPU
	fpu_enable();

	// Initialize UART
	debug_uart_init();

    while(1)
    {
    	printf("Hello From STM32\n\r");
    	for(int i=0; i<9000; i++){}

    }
}
