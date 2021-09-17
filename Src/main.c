#include "stm32f4xx.h"
#include "system_stm32f4xx.h"

#include "AL_GPIO.h"
#include "AL_Utility.h"
#include "AL_EXTI.h"
#include "AL_SysTick.h"
#include "AL_Timer.h"
#include "AL_Usart.h"

bool tim6Trigger = false;

void configureGPIO()
{
	AL_gpioInitPort(GPIOA);
	AL_gpioSelectPinMode(GPIOA, PIN0, INPUT);
	AL_gpioSelectPinMode(GPIOA, PIN1, INPUT);
	AL_gpioSelectPinMode(GPIOA, PIN4, OUTPUT);
	AL_gpioSelectPinMode(GPIOA, PIN5, OUTPUT);
	AL_gpioSetOutputType(GPIOA, PIN0, PUSHPULL);
	AL_gpioSetOutputType(GPIOA, PIN1, PUSHPULL);
	AL_gpioSetOutputType(GPIOA, PIN4, PUSHPULL);
	AL_gpioSetOutputType(GPIOA, PIN5, PUSHPULL);
	AL_gpioSelectPushPullType(GPIOA, PIN0, NO_PULLUP_PULLDOWN);
	AL_gpioSelectPushPullType(GPIOA, PIN1, NO_PULLUP_PULLDOWN);
	AL_gpioSelectPushPullType(GPIOA, PIN4, NO_PULLUP_PULLDOWN);
	AL_gpioSelectPushPullType(GPIOA, PIN5, NO_PULLUP_PULLDOWN);
}

void configureInterrupts()
{
	//Activate syscfg clock (needed for exti)
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

	AL_extiInit();
	AL_extiConfigIrq(GPIOA, PIN0);
	AL_extiConfigIrq(GPIOA, PIN1);
	AL_extiEnableIrq(EXTI_PIN0);
	AL_extiEnableIrq(EXTI_PIN1);
	AL_extiSetTriggerEdge(EXTI_PIN0, FALLING_EDGE);
	AL_extiSetTriggerEdge(EXTI_PIN1, FALLING_EDGE);

	NVIC_EnableIRQ(EXTI0_IRQn); // EXTI0: Aktivieren
	NVIC_EnableIRQ(EXTI1_IRQn); // EXTI1: Aktivieren
}

void configureUSART()
{

}

int main(void)
{
	__disable_irq();

	configureGPIO();
	configureInterrupts();
	configureUSART();

	//Configure timer
	AL_timerBusClkOn(TIM6);
	AL_timerSetPrescaler(TIM6, (1600 - 1));
	AL_timerSetAutoReloadValue(TIM6, (5000 - 1));
	AL_timerEnableInterrupt(TIM6);
	AL_timerStart(TIM6);
	NVIC_EnableIRQ(TIM6_DAC_IRQn);

	__enable_irq();

	while(1)
	{
		if(tim6Trigger == true)
		{
			AL_gpioTogglePin(GPIOA, PIN5);
		    tim6Trigger = false;
		}
	}
}

void TIM6_DAC_IRQHandler(void)
{
    tim6Trigger = true;
    TIM6->SR = 0;
}

void EXTI0_IRQHandler(void)
{
    AL_gpioSetPin(GPIOA, PIN4);
    AL_extiResetPending(EXTI_PIN0);
}

void EXTI1_IRQHandler(void)
{
	AL_gpioResetPin(GPIOA, PIN4);
    AL_extiResetPending(EXTI_PIN1);
}
