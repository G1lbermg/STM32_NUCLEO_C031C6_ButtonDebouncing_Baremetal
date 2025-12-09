#ifndef BUTTON_BSP_H
#define BUTTON_BSP_H

#include "stm32c0xx.h"
#include <stdint.h>

uint8_t initButton(GPIO_TypeDef *port, uint8_t pinNum);
uint8_t readButton(GPIO_TypeDef *port, uint8_t pinNum, uint16_t *inputData);


#endif
