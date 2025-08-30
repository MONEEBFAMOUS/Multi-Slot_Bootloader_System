#include <stdint.h>
#include "uart.h"

#define GPIOAEN (1U<<0) //Enable GPIOA for Tx
#define USART2EN (1U<<17)

#define USART2_BAUDRATE  115200
#define SYS_FREQ 		 16000000
#define APB1_CLK 		 SYS_FREQ //Advance Peripheral Bus
#define CR1_TE 			 (1U<<3) //Transfer Enable , Whereas CR1 stands for Control Register 1
#define CR1_RE 			 (1U<<2) //Receive Enable
#define CR1_RXNEIE 		 (1U<<5) //Receiver Interrupt Enable
#define CR1_UE 			 (1U<<13) //UART Enable
#define SR_TXE 			 (1U<<7) //Transmit Data Register, Whereas SR stands for State Register

static void usart_set_baudrate(uint32_t periph_clk, uint32_t baudrate);
static void uart_write(int ch);

int __io_putchar(int ch)
{
	uart_write(ch);
	return ch;
}

void system_uart_init(void)
{
	// Enable Clock access to GPIOA (for Tx and Rx)
	RCC -> AHB1ENR |= GPIOAEN;

	//Set the mode of PA2 to alternate function mode for Tx
	GPIOA -> MODER &=~ (1U<<4); //Clear bit 4 of MODER (part of PA2 mode field)
	GPIOA -> MODER |= (1U<<5); //Set bit 5 of MODER (part of PA2 mode field)

    // Set PA3 (RX) to alternate function mode
    GPIOA->MODER &= ~(1U<<6); // Clear bit 6
    GPIOA->MODER |= (1U<<7);  // Set bit 7


	//Set PA2 alternate function type to AF7 (UART2_TX)
	GPIOA -> AFR[0] |= (1U<<8);
	GPIOA -> AFR[0] |= (1U<<9);
	GPIOA -> AFR[0] |= (1U<<10);
	GPIOA -> AFR[0] &=~ (1U<<11);

    // Set PA3 alternate function type to AF7 (UART2_RX)
    GPIOA->AFR[0] |= (1U<<12);
    GPIOA->AFR[0] |= (1U<<13);
    GPIOA->AFR[0] |= (1U<<14);
    GPIOA->AFR[0] &= ~(1U<<15);

	//Enable clock access to USART2
	RCC -> APB1ENR |= USART2EN;

	//Configure USART2 baudrate
	usart_set_baudrate(APB1_CLK, USART2_BAUDRATE);

	//Configure transfer direction : Enable Tx and Rx
	USART2 -> CR1 = CR1_TE | CR1_RE; //Set entire register to 0 and set bit3 to 1

	//Enable RXNE Interrupt
	USART2 -> CR1 |= CR1_RXNEIE;

	//Enable UART2 interrupt in NVIC
	NVIC_EnableIRQ(USART2_IRQn);

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
