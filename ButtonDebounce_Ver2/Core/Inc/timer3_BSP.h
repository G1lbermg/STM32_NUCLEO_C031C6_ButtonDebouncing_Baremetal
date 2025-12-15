
#ifndef TIMER3_BSP_H
#define TIMER3_BSP_H

#include "stm32c0xx.h"
#include "stdint.h"

void initTmr3(void);

void delayMS_Tmr3(uint32_t milli_seconds);
void elapsedTimeMs_Tmr3(uint32_t *milli_seconds);

#endif
