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

#define CUSTOM_FUNC __attribute__((section(".custom_section")))
#define RAM_FUNC __attribute__((section(".RamFunc")))

unsigned char __attribute__((section(".custom_ram_block"))) custom_ram_buff[10]; //Size 10 here means 10 Bytes
unsigned char __attribute__((section(".custom_flash_block"))) custom_flash_buff[10]; //Size 10 here means 10 Bytes

void RAM_FUNC _led_toggle(uint32_t dly_ms)
{
	GPIOD -> ODR ^= LED_PIN;
	delay(dly_ms);

}

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

    	_led_toggle(300);

    }
}
