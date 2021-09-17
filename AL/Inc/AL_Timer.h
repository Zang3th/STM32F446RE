#ifndef AL_TIMER
#define AL_TIMER

#include <stdint.h>
#include <stdbool.h>

#include "stm32f4xx.h"

/* Function prototypes */
void AL_timerBusClkOn(TIM_TypeDef *tim);
void AL_timerBusClkOff(TIM_TypeDef *tim);
void AL_timerSetPrescaler(TIM_TypeDef *tim, uint16_t psc);
void AL_timerSetAutoReloadValue(TIM_TypeDef *tim, uint32_t reload);
void AL_timerEnableInterrupt(TIM_TypeDef *tim);
void AL_timerStart(TIM_TypeDef *tim);
void AL_timerStop(TIM_TypeDef *tim);

#endif
