#ifndef UART_BSP_H
#define UART_BSP_H

#include "stm32c0xx.h"
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>


void initUART(void);
//void printMsg(char *message);
void transmitByte(const char byte);

void printMsg(char *message, ...);

#endif
