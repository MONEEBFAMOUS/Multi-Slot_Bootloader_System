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

bool btn_state;

unsigned char __attribute__((section(".custom_ram_block"))) custom_ram_buff[10]; //Size 10 here means 10 Bytes

unsigned char __attribute__((section(".custom_flash_block"))) custom_flash_buff[10]; //Size 10 here means 10 Bytes

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
    	btn_state = get_btn_state();
    	if (btn_state == true)
    	{
    		led_on();
    	}
    	else
    	{
    		led_off();
    	}

    }
}
