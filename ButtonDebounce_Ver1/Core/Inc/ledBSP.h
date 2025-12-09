#ifndef LED_BSP_H
#define LED_BSP_H

#include "stm32c0xx.h"
#include <stdint.h>

uint8_t initLED(GPIO_TypeDef *port, uint8_t pinNum);

uint8_t turnOnLED(GPIO_TypeDef *port, uint8_t pinNum);
uint8_t turnOffLED(GPIO_TypeDef *port, uint8_t pinNum);

#endif
