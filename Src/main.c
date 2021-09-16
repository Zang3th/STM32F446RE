#include "stm32f4xx.h"
#include "system_stm32f4xx.h"

#include "AL_GPIO.h"
#include "AL_Utility.h"
#include "AL_EXTI.h"
#include "AL_SysTick.h"

#define TIMER0_VALUE 500
#define TIMER1_VALUE 1000

int main(void)
{
	__disable_irq();

	//Configure SysTick and create timers
	AL_sysTickInit(SYSTICK_PRECISION_1MS);
	uint32_t  timer0 = TIMER0_VALUE;
	uint32_t  timer1 = TIMER1_VALUE;
	uint32_t* timerList[] = {&timer0, &timer1};
	uint32_t  timerListSize = sizeof(timerList) / sizeof(uint32_t);

	//Activate clocks
	AL_gpioInitPort(GPIOA);
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

	//Configure GPIOA
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

	//Configure EXTI
	AL_extiInit();
	AL_extiConfigIrq(GPIOA, PIN0);
	AL_extiConfigIrq(GPIOA, PIN1);
	AL_extiEnableIrq(EXTI_PIN0);
	AL_extiEnableIrq(EXTI_PIN1);
	AL_extiSetTriggerEdge(EXTI_PIN0, FALLING_EDGE);
	AL_extiSetTriggerEdge(EXTI_PIN1, FALLING_EDGE);

	NVIC_EnableIRQ(EXTI0_IRQn); // EXTI0: Aktivieren
	NVIC_EnableIRQ(EXTI1_IRQn); // EXTI1: Aktivieren

	__enable_irq();

	while(1)
	{
		if(AL_sysTickTimerExpired(timer1) == true)
		{
			AL_gpioTogglePin(GPIOA, PIN5); //Keep alive signal
			timer1 = TIMER1_VALUE;
		}

		AL_sysTickUpdateTimers(timerList, timerListSize);
	}
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
