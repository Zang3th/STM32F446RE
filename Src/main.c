#include <stdint.h>
#include "stm32f4xx.h"

int main(void)
{
    uint32_t rccCRState = 0UL;
    rccCRState = RCC->CR;

	for(;;);
}
