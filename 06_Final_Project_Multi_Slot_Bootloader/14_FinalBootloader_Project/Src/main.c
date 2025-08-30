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

#define SECTOR0_BASE_ADDRESS 0X08000000 //Bootloader Section
#define SECTOR1_BASE_ADDRESS 0X08004000 //Default App Section
#define SECTOR2_BASE_ADDRESS 0X08008000 //App1 Sector
#define SECTOR3_BASE_ADDRESS 0X0800C000 //Factory App reset

#define DEFAULT_APP_ADDRESS SECTOR1_BASE_ADDRESS
#define APP1_ADDRESS SECTOR2_BASE_ADDRESS
#define FACTORY_APP_ADDRESS SECTOR3_BASE_ADDRESS
//#define LED_PIN PIN12

//0X20020000 = Stack Pointer Value / Start of Firmware

bool btn_state;

#define APPLICATION_ADDRESS 0x08008000 //Sector2 search Embedded flash in MCU Reference Manual

#define MSP_VERIFY_MASK	0x2FFE0000

#define EMPTY_MEM 0xFFFFFFFF

#define MEM_CHECK_V2


volatile char g_ch_key;
volatile uint8_t g_un_key;

typedef void(*func_ptr)(void);



typedef enum
{
	APP = 1,
	FACTORY_APP,
}SYS_APPS;

static void process_btldr_cmds(SYS_APPS curr_app);

//-----------------------------------------------------------------------------------------------------

//void jump_to_default_app(void)
//{
//	uint32_t app_start_address;
//	func_ptr jump_to_app;
//
//	printf("Bootloader started...\n\r");
//
//	delay(300);
//
//	//Version_01
//#ifdef MEM_CHECK_V1
//	if(((*(uint32_t *)APPLICATION_ADDRESS) & MSP_VERIFY_MASK ) == 0x20020000 )
//#endif
//
//	//Version_02
//#ifdef MEM_CHECK_V2
//		if((*(uint32_t *)APPLICATION_ADDRESS) != EMPTY_MEM )
//#endif
//
//	{
//
//		printf("Starting Application......\n\r");
//
//		app_start_address = *(uint32_t *)(APPLICATION_ADDRESS + 4);
//		jump_to_app = (func_ptr) app_start_address;
//
//		//Initialize main Stack Pointer
//		__set_MSP(*(uint32_t *)APPLICATION_ADDRESS);
//
//		//Jump
//		jump_to_app();
//
//
//	}
//	else
//	{
//		printf("No application Found at Sector 2 location......\n\r");
//	}
//
//}

//-------------------------------------------------------------------------------------------------

static void jump_to_app(uint32_t addr_value)
{
	uint32_t app_start_address;
	func_ptr jump_to_app;

	printf("Bootloader started...\n\r");

	delay(300);

	//Version_01
#ifdef MEM_CHECK_V1
	if(((*(uint32_t *)addr_value) & MSP_VERIFY_MASK ) == 0x20020000 )
#endif

	//Version_02
#ifdef MEM_CHECK_V2
		if((*(uint32_t *)addr_value) != EMPTY_MEM )
#endif

	{

		printf("Starting Application......\n\r");

		app_start_address = *(uint32_t *)(addr_value + 4);
		jump_to_app = (func_ptr) app_start_address;

		//Initialize main Stack Pointer
		__set_MSP(*(uint32_t *)addr_value);

		//Jump
		jump_to_app();


	}
	else
	{
		printf("No application Found......\n\r");
	}
}

//-----------------------------------------------------------------------------------------------

int main(void)
{
    // Enable FPU
	fpu_enable();

	// Initialize UART
	system_uart_init();

	//Initialize timebase
	timebase_init();

	//Initialize LED
	led_init();

	//Initialize Push Button
	button_init();

	//Jump to default application function
	//jump_to_default_app();

	//STM32 Cube Programmer is a very useful tool provided by stm32 which helps us to analyze our memory either its is flash, ram or system or developer defined.
	//We can do the same thing using our debugger as well since it has a memory analyzer / memory navigator /memory browser.
	//However, Stm32 cube Programmer is more robust.

	//1> First to mass erase using STM32CubeProgramemr.
	//2> At Adress 0x08008000 the first value will be our Stack Pointer (0X20020000). In Arm Cortex this value is usually near the Top of RAM.

	if(get_btn_state())
	{
		/* Button Pressed */
		printf("DBG: Button Pressed....\n\r");

		/* Button Pressed */
		printf("==========================================\n\r");
		printf("==========================================\n\r");
		printf("==========================================\n\r");
		printf("==========================================\n\r");
		printf("==========================================\n\r");
		printf("\n");
		printf("Bootloader Menu\n");
		printf("\n");
		printf("==========================================\n\r");
		printf("==========================================\n\r");
		printf("==========================================\n\r");

		printf("Available Commands: \n\r");
		printf("Press U to Update: \n\r");
		printf("Press R to Reset to Factory App \n\r");
		printf("Press Any Key to Continue \n\r");

	}
	else
	{
		/* Button Not Pressed */
		jump_to_app(DEFAULT_APP_ADDRESS);

	}

    while(1)
    {
    	//TO DO: Process Boot loader commands
    	process_btldr_cmds(g_un_key);

    }
}

//----------------------------------------------------------------------------------------

static void process_btldr_cmds(SYS_APPS curr_app)
{
	switch(curr_app)
	{
	case APP:
		printf("APP1 Selected....!\n\r");
		jump_to_app(APP1_ADDRESS);
		break;

	case FACTORY_APP:
		printf("Factory Reset App Selected....!\n\r");
		jump_to_app(FACTORY_APP_ADDRESS);
		break;

	default:
		break;
	}
}

//--------------------------------------------------------------------------------------------

static void uart_callback(void)
{
	g_ch_key = USART2 -> DR;

	if ( (g_ch_key == 'u') || (g_ch_key == 'U'))
	{
		g_un_key = 1;
	}
	else if( (g_ch_key == 'r') || (g_ch_key == 'R'))
	{
		g_un_key = 2;
	}
	else
	{
		/* Any Button Pressed */
		jump_to_app(DEFAULT_APP_ADDRESS);
	}
}

//--------------------------------------------------------------------------------------------

void USART2_IRQHandler(void)
{
	//Check if RXNE is set
	if(USART2 -> SR & SR_RXNE)
	{
		uart_callback();
	}
}
