#include <stdint.h>
#include "uart.h"

#define GPIOAEN (1U<<0)
#define USART2EN (1U<<17)

#define USART2_BAUDRATE 115200
#define SYS_FREQ 16000000
#define APB1_CLK SYS_FREQ
#define CR1_TE (1U<<3)
#define CR1_UE (1U<<13)
#define SR_TXE (1U<<7)

static void usart_set_baudrate(uint32_t periph_clk, uint32_t baudrate);
static void uart_write(int ch);

int __io_putchar(int ch)
{
	uart_write(ch);
	return ch;
}

void debug_uart_init(void)
{
	// Enable Clock access to GPIOA
	RCC -> AHB1ENR |= GPIOAEN;

	//Set the mode of PA2 to alternate function mode
	GPIOA -> MODER &=~ (1U<<4); //Clear bit 4 of MODER (part of PA2 mode field)
	GPIOA -> MODER |= (1U<<5); //Set bit 5 of MODER (part of PA2 mode field)

	//Set the alternate function type to AF7 (UART2_TX)
	GPIOA -> AFR[0] |= (1U<<8);
	GPIOA -> AFR[0] |= (1U<<9);
	GPIOA -> AFR[0] |= (1U<<10);
	GPIOA -> AFR[0] &=~ (1U<<11);

	//Enable clock access to USART2
	RCC -> APB1ENR |= USART2EN;

	//Configure USART2 baudrate
	usart_set_baudrate(APB1_CLK, USART2_BAUDRATE);

	//Configure transfer direction
	USART2 -> CR1 = CR1_TE; //Set entire register to 0 and set bit3 to 1

	//Enable USART Module
	USART2 -> CR1 |= CR1_UE; //Just update the value of bit 13


}

static void uart_write(int ch)
{
	//Make sure transmit data register is empty
	while(!(USART2 -> SR & SR_TXE)){}

	//Write to Transmit Data register
	USART2 -> DR = (ch & 0xFF);


}

static uint16_t compute_uart_bd(uint32_t periph_clk, uint32_t baudrate)
{
	return (periph_clk + (baudrate/2U))/baudrate;
}

static void usart_set_baudrate(uint32_t periph_clk, uint32_t baudrate)
{
	USART2 -> BRR = compute_uart_bd(periph_clk, baudrate);
}
