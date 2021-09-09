#include "stm32f446xx.h"
#include "system_stm32f4xx.h"

#include "alUtility.h"
#include "alGPIO.h"

int main(void)
{
	gpioInitPort(GPIOA);
	gpioSelectPinMode(GPIOA, PIN0, OUTPUT);

	while(1)
	{
		gpioTogglePin(GPIOA, PIN0);
		delayMS(100);
	}
}
