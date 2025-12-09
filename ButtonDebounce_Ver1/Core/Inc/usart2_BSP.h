#ifndef UART_BSP_H
#define UART_BSP_H

#include "stm32c0xx.h"
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>


void initUSART2(void);
void printMsg_USART2(char *message, ...);
void printMsgNL_USART2(char *message, ...);
void transmitByte_USART2(const char byte);

//void printMsg(char *message);

#endif
