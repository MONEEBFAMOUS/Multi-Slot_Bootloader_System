#include "stm32f4xx.h"

#define GPIODEN (1U<<3)   // Shift 1 to position 3 register (Enable GPIOD clock)
#define PIN12 (1U<<12)    // Shift 1 to position 12 register (Green LED)
#define PIN13 (1U<<13)    // Shift 1 to position 13 register (Orange LED)
#define PIN14 (1U<<14)    // Shift 1 to position 14 register (Red LED)
#define PIN15 (1U<<15)    // Shift 1 to position 15 register (Blue LED)

int main(void)
{
    // Enable Clock access to GPIOD
    RCC->AHB1ENR |= GPIODEN;

    // Configure PD12 as output - Green LED
    // We need to set two bits in MODER register for each pin (pin12 uses bits 24,25)
    GPIOD->MODER |= (1U<<24);  // Set bit 24 to 1 (pin12 * 2 = 24)
    GPIOD->MODER &= ~(1U<<25); // Set bit 25 to 0 (pin12 * 2 + 1 = 25)

    // Configure PD13 as output - Orange LED
    // Pin13 uses bits 26,27 in MODER register
    GPIOD->MODER |= (1U<<26);  // Set bit 26 to 1 (pin13 * 2 = 26)
    GPIOD->MODER &= ~(1U<<27); // Set bit 27 to 0 (pin13 * 2 + 1 = 27)

    // Configure PD14 as output - Red LED
    // Pin14 uses bits 28,29 in MODER register
    GPIOD->MODER |= (1U<<28);  // Set bit 28 to 1 (pin14 * 2 = 28)
    GPIOD->MODER &= ~(1U<<29); // Set bit 29 to 0 (pin14 * 2 + 1 = 29)

    // Configure PD15 as output - Blue LED
    // Pin15 uses bits 30,31 in MODER register
    GPIOD->MODER |= (1U<<30);  // Set bit 30 to 1 (pin15 * 2 = 30)
    GPIOD->MODER &= ~(1U<<31); // Set bit 31 to 0 (pin15 * 2 + 1 = 31)

    while(1)
    {
        // "^" is the toggle operator, used here to toggle each LED
        GPIOD->ODR ^= PIN12;  // Toggle Green LED (PD12)
        GPIOD->ODR ^= PIN13;  // Toggle Orange LED (PD13)
        GPIOD->ODR ^= PIN14;  // Toggle Red LED (PD14)
        GPIOD->ODR ^= PIN15;  // Toggle Blue LED (PD15)

        // Simple delay loop to make blinking visible
        for(int i = 0; i < 1000000; i++)
        {
            // Empty loop for delay
        }
    }
}
