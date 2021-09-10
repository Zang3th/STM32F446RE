#include "stm32f446xx.h"
#include "system_stm32f4xx.h"

#include "AL_GPIO.h"
#include "AL_Utility.h"

int main(void)
{
	__disable_irq();

	AL_gpioInitPort(GPIOA);
	AL_gpioSelectPinMode(GPIOA, PIN0, INPUT);
	AL_gpioSelectPinMode(GPIOA, PIN1, OUTPUT);
	AL_gpioSelectPinMode(GPIOA, PIN5, OUTPUT);
	AL_gpioSetOutputType(GPIOA, PIN0, PUSHPULL); //Müsste Standard sein
	AL_gpioSetOutputType(GPIOA, PIN1, PUSHPULL); //Müsste Standard sein
	AL_gpioSetOutputType(GPIOA, PIN5, PUSHPULL); //Müsste Standard sein
	AL_gpioSelectPushPullType(GPIOA, PIN0, NO_PULLUP_PULLDOWN);
	AL_gpioSelectPushPullType(GPIOA, PIN1, NO_PULLUP_PULLDOWN);
	AL_gpioSelectPushPullType(GPIOA, PIN5, NO_PULLUP_PULLDOWN);

	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;  // SYSCFG: Clock an
	SYSCFG->EXTICR[0] &= ~0x000F;          // EXTI0 an
	EXTI->IMR  |= EXTI_IMR_IM0;            // EXTI: PA0 Enable IRQ
	EXTI->FTSR |= EXTI_FTSR_TR0;           // EXTI: PA0 Fallende Flanke
	NVIC_EnableIRQ(EXTI0_IRQn);            // EXTI0: Aktivieren

	__enable_irq();

	while(1)
	{
		//Keep alive signal
		AL_gpioTogglePin(GPIOA, PIN5);
		AL_delayMS(200);
	}
}

void EXTI0_IRQHandler(void)
{
    AL_gpioTogglePin(GPIOA, PIN1);
    EXTI->PR |= EXTI_PR_PR0; //Reset IRQ-Pending-Flag
}
