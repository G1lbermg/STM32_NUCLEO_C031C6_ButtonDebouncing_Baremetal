#ifndef UART_BSP_H
#define UART_BSP_H

#include "stm32c0xx.h"
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

#include "error_codes.h"

ErrorCode_t initUSART2(void);
ErrorCode_t printMsg_USART2(char *message, ...);
ErrorCode_t printMsgNL_USART2(char *message, ...);
ErrorCode_t transmitByte_USART2(const char byte);

#endif
