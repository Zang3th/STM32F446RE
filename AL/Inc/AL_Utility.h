#ifndef AL_UTILITY
#define AL_UTILITY

#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>

#include "AL_GPIO.h"
#include "AL_Usart.h"
#include "AL_SysTick.h"

/* Function prototypes */
void AL_initUtilities();
void AL_printf(const char* msg, ...);
void AL_blockMilliseconds(uint32_t delay);

#endif
