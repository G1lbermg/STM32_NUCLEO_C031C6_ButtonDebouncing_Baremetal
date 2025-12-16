
#ifndef TIMER3_BSP_H
#define TIMER3_BSP_H

#include "stm32c0xx.h"
#include "stdint.h"
#include "error_codes.h"

ErrorCode_t initTmr3(uint32_t targetFreqHz);
ErrorCode_t elapsedTicks_Tmr3(uint32_t *milliSeconds);
ErrorCode_t delayTicks_Tmr3(uint32_t milliSeconds);


#endif
