#ifndef BUTTON_BSP_H
#define BUTTON_BSP_H

#include "stm32c0xx.h"
#include "error_codes.h"
#include <stdint.h>

typedef struct {
    GPIO_TypeDef *port;
    uint16_t readMask;

} Button_t;

ErrorCode_t initButton(Button_t *button,GPIO_TypeDef *port, uint8_t pinNum);
ErrorCode_t readButton(Button_t *button, uint16_t *readData);


#endif
