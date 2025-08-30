#include <stdio.h>
#include "stm32f4xx.h"
#include "fpu.h"
#include "uart.h"
#include "timebase.h"
#include "bsp.h"
#include <stdbool.h>

/*
Module: DRIVERS
 * FPU = Floating Point Computation, Core peripheral of the arm architecture
 * UART
 * GPIO (BSP) =Board Support Package
 * TIMEBASE
 * ADC
*/


//0X20020000 = Stack Pointer Value / Start of Firmware

bool btn_state;

#define APPLICATION_ADDRESS 0x08008000 //Sector2 search Embedded flash in MCU Reference Manual
#define MSP_VERIFY_MASK	0x2FFE0000
#define EMPTY_MEM 0xFFFFFFFF

#define MEM_CHECK_V2

typedef void(*func_ptr)(void);

void jump_to_default_app(void)
{
	uint32_t app_start_address;
	func_ptr jump_to_app;

	printf("Bootloader started...\n\r");

	delay(300);

	//Version_01
#ifdef MEM_CHECK_V1
	if(((*(uint32_t *)APPLICATION_ADDRESS) & MSP_VERIFY_MASK ) == 0x20020000 )
#endif

	//Version_02
#ifdef MEM_CHECK_V2
	if((*(uint32_t *)APPLICATION_ADDRESS) != EMPTY_MEM )
#endif

	{

		printf("Starting Application......\n\r");

		app_start_address = *(uint32_t *)(APPLICATION_ADDRESS + 4);
		jump_to_app = (func_ptr) app_start_address;

		//Initialize main Stack Pointer
		__set_MSP(*(uint32_t *)APPLICATION_ADDRESS);

		//Jump
		jump_to_app();
	}
	else
	{
		printf("No application Found at Sector 2 location......\n\r");
	}

}

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

struct Bootloader_Common_Apis Common_Apis __attribute__((section(".COMMON_APIS"))) =	{
		led_init,
		led_toggle,
		led_on,
		led_off,
		debug_uart_init,
		button_init,
		get_btn_state,
		fpu_enable,
		timebase_init

};

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

	//Jump to default application function
	jump_to_default_app();

	//STM32 Cube Programmer is a very useful tool provided by stm32 which helps us to analyze our memory either its is flash, ram or system or developer defined.
	//We can do the same thing using our debugger as well since it has a memory analyzer / memory navigator /memory browser.
	//However, Stm32 cube Programmer is more robust.

	//1> First to mass erase using STM32CubeProgramemr.
	//2> At Adress 0x08008000 the first value will be our Stack Pointer (0X20020000). In Arm Cortex this value is usually near the Top of RAM.


    while(1)
    {
    	//Boot loader

    }
}
