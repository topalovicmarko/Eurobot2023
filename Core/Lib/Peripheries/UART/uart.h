/*
 * uart.h
 *
 *  Created on: Mar 9, 2023
 *      Author: Marko Topalovic
 */

#ifndef LIB_PERIPHERIES_UART_UART_H_
#define LIB_PERIPHERIES_UART_UART_H_

#include "stm32f405xx.h"
#include <stdint.h>
#include <stddef.h>
#include "../TIMER/timer.h"

void uart_init();

void sendChar(unsigned char ch);
void sendStr(unsigned char *str);
void sendArray(uint8_t *array, size_t size);
char ReadChar();

#endif /* LIB_PERIPHERIES_UART_UART_H_ */
