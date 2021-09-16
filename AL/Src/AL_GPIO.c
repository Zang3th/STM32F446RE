#include "AL_GPIO.h"

void AL_gpioInitPort(GPIO_TypeDef *port)
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

void AL_gpioSelectPinMode(GPIO_TypeDef *port, PIN_NUM pin, PIN_MODE mode)
{
	// Set pin to default (INPUT)
	port->MODER &= ~(0b11 << (pin * 2));

	// If mode is not INPUT --> Select other setting
	if(INPUT != mode)
	{
		port->MODER |= (mode << (pin * 2));
	}
}

void AL_gpioSetPin(GPIO_TypeDef *port, PIN_NUM pin)
{
	port->BSRR |= 1 << pin;
}

void AL_gpioResetPin(GPIO_TypeDef *port, PIN_NUM pin)
{
	port->BSRR |= (1 << (pin + 16));
}

void AL_gpioTogglePin(GPIO_TypeDef *port, PIN_NUM pin)
{
	if(AL_gpioGetPinVal(port, pin))
	{
		AL_gpioResetPin(port, pin);
	}
	else
	{
		AL_gpioSetPin(port, pin);
	}
}

void AL_gpioSelectAltFunc(GPIO_TypeDef *port, PIN_NUM pin, ALT_FUNC af)
{
	// Don't forget to select the alternative function mode before...
	AL_gpioSelectPinMode(port, pin, ALTFUNC);

	if(pin <= PIN7)
	{
		port->AFR[0] &= ~(0x0F << (pin * 4));       // Reset previously selected AF
		port->AFR[0] |= af << (pin * 4);            // Set AFR[0] to the new AF
	}
	else
	{
		// !!! Subtract 8 from pin number since we start at bit 0 !!!
		port->AFR[1] &= ~(0x0F << ((pin - 8) * 4)); // Reset previously selected AF.
		port->AFR[1] |= af << ((pin - 8) * 4);      // Set AFR[1] to the new AF
	}
}

bool AL_gpioSetOutputType(GPIO_TypeDef *port, PIN_NUM pin, OUTPUT_TYPE outType)
{
	if(pin >= PIN0 && pin <= PIN15)
	{
		port->OTYPER &= ~(1 << pin);   // Use pin as push-pull output
		if(OPENDRAIN == outType)
		{
			port->OTYPER |= (1 << pin);
		}
	}
	else
	{
        return false;
	}

	return true;
}

void AL_gpioSelectPushPullType(GPIO_TypeDef *port, PIN_NUM pin, PUPD_MODE pupd)
{
    port->PUPDR &= ~(0x03 << (pin * 2));        // Disable PU/PD

    if(port->OTYPER == PUSHPULL)
	{
		if(PULLUP == pupd)
		{
			port->PUPDR |= (PULLUP << (pin *2));
		}
		else if(PULLDOWN == pupd)
		{
			port->PUPDR |= (PULLDOWN << (pin *2));
		}
	}
}

void AL_gpioSetOutputSpeed(GPIO_TypeDef *port, PIN_NUM pin, GPIO_SPEED speed)
{
	port->OSPEEDR &= (LOW_SPEED << (pin * 2));	// Default: Low speed

	if(MEDIUM_SPEED == speed)
	{
		port->OSPEEDR |= (MEDIUM_SPEED << (pin * 2));
	}
	else if(FAST_SPEED == speed)
	{
		port->OSPEEDR |= (FAST_SPEED << (pin * 2));
	}
	else if(HIGH_SPEED == speed)
	{
		port->OSPEEDR |= (HIGH_SPEED << (pin * 2));
	}
}

uint8_t AL_gpioGetPinVal(GPIO_TypeDef *port, PIN_NUM pin)
{
	return (port->IDR & (1 << pin));
}

uint16_t AL_gpioGetPortVal(GPIO_TypeDef *port)
{
	return (port->IDR);
}
