#include "alGPIO.h"

void gpioInitPort(GPIO_TypeDef *port)
{
	if(GPIOA == port)
	{
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	}
	else if(GPIOB == port)
	{
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
	}
	else if(GPIOC == port)
	{
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
	}
	else if(GPIOD == port)
	{
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
	}
	else if(GPIOE == port)
	{
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
	}
	else if(GPIOF == port)
	{
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOFEN;
	}
	else if(GPIOG == port)
	{
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN;
	}
	else if(GPIOH == port)
	{
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOHEN;
	}
}

void gpioSelectPinMode(GPIO_TypeDef *port, PIN_NUM pin, PIN_MODE mode)
{
	// Set pin to default (INPUT)
	port->MODER &= ~(0b11 << (pin * 2));

	// If mode is not INPUT --> Select other setting
	if(INPUT != mode)
	{
		port->MODER |= (mode << (pin * 2));
	}
}

void gpioSetPin(GPIO_TypeDef *port, PIN_NUM pin)
{
	port->BSRR |= 1 << pin;
}

void gpioResetPin(GPIO_TypeDef *port, PIN_NUM pin)
{
	port->BSRR |= (1 << (pin + 16));
}

void gpioTogglePin(GPIO_TypeDef *port, PIN_NUM pin)
{
	if(gpioGetPinVal(port, pin))
	{
		gpioResetPin(port, pin);
	}
	else
	{
		gpioSetPin(port, pin);
	}
}

uint8_t gpioGetPinVal(GPIO_TypeDef *port, PIN_NUM pin)
{
	return (port->IDR & (1 << pin));
}
