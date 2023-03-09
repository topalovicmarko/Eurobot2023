/*
 * uart.c
 *
 *  Created on: Mar 9, 2023
 *      Author: Marko Topalovic
 */

#include "uart.h"

//Prototipovi "privatnih" funkcija
static void uart_gpio_init();

//Promenljive
static volatile unsigned char buff_char;
static volatile unsigned char input_str[30], input_str_size = 0;

void uart_init() {
	uart_gpio_init();

	RCC->APB1ENR |= (1 << 18);				// USART3 ENABLE

	USART3->CR1 |= (1 << 13);				// USART ENABLE

	// Baud = fclk/(16xUSARTDIV)
	// USARTDIV = DIV_Mantissa + (DIV_Fraction / 16)
	// fclk = 42MHz
	// Baud = 9600 (standardna vrednost)
	// 9600 = 42000000/(16*USARTDIV) -> USARTDIV = 273.4375
	// DIV_Mantissa = 273
	// DIV_Fraction = 0.4375*16 = 7
	USART3->BRR |= (7 << 0) | (273 << 4);	// Baud rate reg

	USART3->CR2 |= (1 << 2) | (1 << 3);		// Transmiser and reciever enable
	USART3->CR2 |= (1 << 5);				// Dozvola interrupt

	NVIC->ISER[1] |= (1 << (39-32));		// Interrupt USART3 en

}

void uart_gpio_init() {

	//PB10 -> TX
	//PB11 -> RX

	RCC->AHB1ENR |= (1 << 1);			//GPIOB

	GPIOB->MODER |= (0b10 << 10 * 2);	//Alternative func.
	GPIOB->MODER |= (0b10 << 11 * 2);	//Alternative func.

	GPIOB->OSPEEDR |= (0b11 << 10 * 2);	//Very high speed
	GPIOB->OSPEEDR |= (0b11 << 11 * 2);	//Very high speed

	GPIOB->AFR[1] |= (0b111 << 3 * 4);	//USART3 RX HIGH(8-15)
	GPIOB->AFR[1] |= (0b111 << 4 * 4);	//USART3 TX HIGH(8-15)
}

void send_char(unsigned char send_ch) {

	//USART3->DR koristi se za slanje i prihvatanje podataka
	USART3->DR = send_ch;

	while((USART2->SR & (1 << 6))){
		__NOP();
	}
}

void send_str(volatile unsigned char* send_str) {

	while(*send_str != '\0') {
		send_char(*send_str);
		send_str++;
	}
}

void echo_test() {
		void send_str(input_str);

		input_str_size = 0;
		input_str[input_str_size] = '\0';
}

void USART3_IRQHandler() {

	if (USART3->SR & (1 << 5)) {

		// Vršimo čitanje podatka
		buff_char = USART3->DR;

		if (input_str_size < 30 - 1) {
			input_str[input_str_size] = buff_char;
			input_str_size++;
			input_str[input_str_size] = '\0';
		}

		USART3->SR &= ~(1 << 5);

	}

}
