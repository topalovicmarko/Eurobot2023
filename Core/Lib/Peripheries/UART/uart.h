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

//Prototipovi funkcija
void uart_init();
void send_char(volatile unsigned char send_ch);
void send_str(volatile unsigned char* send_str);
void echo_test();

#endif /* LIB_PERIPHERIES_UART_UART_H_ */
