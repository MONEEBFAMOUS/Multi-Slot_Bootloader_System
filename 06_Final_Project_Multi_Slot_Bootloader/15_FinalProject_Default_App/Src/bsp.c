/*
 * bsp.c
 *
 *  Created on: Aug 25, 2025
 *      Author: Moneeb
 */


#include "bsp.h"
#include "stm32f4xx.h"

#define GPIOAEN (1U << 0)
#define GPIODEN (1U << 3)

// STM32F407 Discovery Board LEDs (GPIOD)
#define PIN12 (1U << 12)  // Green LED
#define PIN13 (1U << 13)  // Orange LED
#define PIN14 (1U << 14)  // Red LED
#define PIN15 (1U << 15)  // Blue LED
#define LED_PIN PIN12     // Using Green LED as default

// STM32F407 Discovery Board User Button (GPIOA)
#define PIN0 (1U << 0)
#define BTN_PIN PIN0

void led_init(void)
{
	//Enable Gpio Clock Access to GPIOD
	RCC -> AHB1ENR |= GPIODEN;

	//Set PD12 mode to output mode
	GPIOD -> MODER |= (1U<<24);
	GPIOD -> MODER &=~ (1U<<25);
}

void led_on(void)
{
	//Set PA5 High
	GPIOD -> ODR |= LED_PIN;
}

void led_off(void)
{
	//Set PD12 to low
	GPIOD -> ODR &=~ LED_PIN;

}

void button_init(void)
{
	//Enable Clock access to PORTA
	RCC -> AHB1ENR |= GPIOAEN;

	//Set PA0 as an input pin
	GPIOA -> MODER &=~ (1U << 0);
	GPIOA -> MODER &=~ (1U << 1);
}

bool get_btn_state(void)
{
	//Check if button is pressed
	if (GPIOA -> IDR & BTN_PIN)
	{
		return true;
	}
	else
	{
		return false;

	}
}

