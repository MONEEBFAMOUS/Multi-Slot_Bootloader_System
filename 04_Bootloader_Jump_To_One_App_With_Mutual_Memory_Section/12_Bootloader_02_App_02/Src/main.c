#include <stdio.h>
#include "stm32f4xx.h"
#include <stdbool.h>
#include <timebase_min.h>
#include <uart_min.h>

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

struct Bootloader_Common_Apis
{
	void (*led_init)(void);
	void (*led_toggle)(uint32_t dly);
	void (*led_on)(void);
	void (*led_off)(void);
	void (*debug_uart_init)(void);
	void (*button_init)(void);
	bool (*get_btn_state)(void);
	void (*fpu_enable)(void);
	void (*timebase_init)(void);

};


int main(void)
{
	struct Bootloader_Common_Apis *Common_Apis = (struct Bootloader_Common_Apis *) 0x0800C000;

    // Enable FPU
	Common_Apis -> fpu_enable();

	// Initialize UART
	Common_Apis -> debug_uart_init();

	//Initialize timebase
	Common_Apis -> timebase_init();

	//Initialize LED
	Common_Apis -> led_init();

	//Initialize Push Button
	Common_Apis -> button_init();



    while(1)
    {

    	printf("Application 2 Running...\n\r");

    }
}


//Startup_stm32f407 weak function called SystemInit(void)
//We dont have to call SystemInit anywhere the Reset Hanlder already calls it like an interrupt request Handler.

void SystemInit(void)
{
	//SCB Stands for System Control Block, where as VTOR stands for Vector Table Offset register
	SCB -> VTOR = VECTOR_TABLE_BASE_ADDRESS | VECTOR_TABLE_OFFSET;
}
