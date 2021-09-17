#ifndef AL_SYSTEM
#define AL_SYSTEM

#include <stdint.h>
#include <stdbool.h>

#include "stm32f4xx.h"

/* Defines */
#define HSI_VALUE       ((uint32_t) 16000000u)
#define HSE_VALUE       ((uint32_t) 25000000u)

/* Function prototypes */
uint32_t AL_systemGetSysClock(void);
uint32_t AL_systemGetHclkFreq(void);
uint32_t AL_systemGetPclk1Freq(void);
uint32_t AL_systemGetPclk2Freq(void);

#endif
