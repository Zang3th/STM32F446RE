#ifndef AL_GPIO
#define AL_GPIO

#include <stdint.h>
#include <stdbool.h>

#include "stm32f4xx.h"

typedef enum
{
	PIN0 = 0,
	PIN1,
	PIN2,
	PIN3,
	PIN4,
	PIN5,
	PIN6,
	PIN7,
	PIN8,
	PIN9,
	PIN10,
	PIN11,
	PIN12,
	PIN13,
	PIN14,
	PIN15
} PIN_NUM;

typedef enum
{
	INPUT = 0,
	OUTPUT,
	ALTFUNC,
	ANALOG
} PIN_MODE;

void 	 gpioInitPort(GPIO_TypeDef *port);
void 	 gpioSelectPinMode(GPIO_TypeDef *port, PIN_NUM pin, PIN_MODE mode);
void 	 gpioSetPin(GPIO_TypeDef *port, PIN_NUM pin);
void 	 gpioResetPin(GPIO_TypeDef *port, PIN_NUM pin);
void 	 gpioTogglePin(GPIO_TypeDef *port, PIN_NUM pin);
uint8_t  gpioGetPinVal(GPIO_TypeDef *port, PIN_NUM pin);

#endif
