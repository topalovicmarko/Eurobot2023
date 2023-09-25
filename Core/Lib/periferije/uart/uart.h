/*
 * uart.h
 *
 *  Created on: Apr 18, 2023
 *      Author: Marko Topalovic
 */

#ifndef LIB_PERIFERIJE_UART_UART_H_
#define LIB_PERIFERIJE_UART_UART_H_

#include "stm32f4xx.h"
#include <stdint.h>
void uart_init(void);
void uart_send_byte6(uint8_t podatak);
void uart_send_str6(char* str);
uint16_t get_ugao(void);
void servo_control(uint8_t id, uint16_t ugao);
#endif /* LIB_PERIFERIJE_UART_UART_H_ */
