#include "AL_Utility.h"

void AL_initUtilities()
{
	//Initialize and confiure Usart
	AL_gpioSelectPinMode(GPIOA, PIN2, ALTFUNC);      // PA2   : Modus = Alt. Funktion
	AL_gpioSelectAltFunc(GPIOA, PIN2, AF7);          // PA2   : AF7 = USART2 Rx
	AL_gpioSelectPinMode(GPIOA, PIN3, ALTFUNC);      // PA3   : Modus = Alt. Funktion
	AL_gpioSelectAltFunc(GPIOA, PIN3, AF7);          // PA3   : AF7 = USART2 Tx

	AL_usartSelectUsart(USART2);
	AL_usartStartUsart(USART2);
	AL_usartSetCommParams(USART2, 9600, NO_PARITY, LEN_8BIT, ONE_BIT);

	//Init SysTick
	AL_sysTickInit(SYSTICK_PRECISION_1MS);
}

void AL_printf(const char* msg, ...)
{
	va_list args;
	char buffer[32];
	memset(buffer, 0, 32);

	va_start(args, msg);
	vsprintf(buffer, msg, args);
	AL_usartSendString(USART2, buffer);
	va_end(args);
}

void AL_blockMilliseconds(uint32_t delay)
{
	uint32_t  timer0 = delay;
	uint32_t* timerList[] = {&timer0};
	uint32_t  timerListSize = sizeof(timerList) / sizeof(uint32_t);

	while(AL_sysTickTimerExpired(timer0) == false)
	{
		AL_sysTickUpdateTimers(timerList, timerListSize);
	}
}
