#include "stm32f4xx.h"

void fpu_enable(void)
{
	/* Enable floating point unit which is arm peripheral: Enable CP10 and CP11 registers full access */
	SCB -> CPACR |= (1<<20); // We use "/" to set only bit 20 to 1 if we don't use it all the rest bits of register will be set to zero.
	SCB -> CPACR |= (1<<21);
	SCB -> CPACR |= (1<<22);
	SCB -> CPACR |= (1<<23); // If set only "=" rather than "|=" means 0B 0000 0000 1000 0000 0000 0000 0000 0000



}
