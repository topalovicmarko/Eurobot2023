/*
 * uart.c
 *
 *  Created on: Mar 9, 2023
 *      Author: Marko Topalovic
 */

#include "uart.h"

void
uart_init()
{
	/*
	 * PB10 - UART3 TX, AF7
	 * PB11 - UART3 RX, AF7
	 *
	 * USART3 115 200 KBps / sec --> AX 12 je konfigurisan za ovaj protok
	 */

	// 42 MHz na APB1

	// Clock enable
	RCC->APB1ENR |= RCC_APB1ENR_USART3EN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

	// Alt. func. for PB10 & PB11
	GPIOB->MODER &= ~(0b11 << 10 * 2);
	GPIOB->MODER |=  (0b10 << 10 * 2);

	GPIOB->MODER &= ~(0b11 << 11 * 2);
	GPIOB->MODER |=  (0b10 << 11 * 2);

	// Output speed = HIGH
	GPIOB->OSPEEDR |= (0b11 << 10 * 2);
	GPIOB->OSPEEDR |= (0b11 << 11 * 2);

	// Alt. f. 7
	GPIOB->AFR[1] &= ~(15UL << (10 % 8) * 4);
	GPIOB->AFR[1] |=  (7UL	  << (10 % 8) * 4);

	GPIOB->AFR[1] &= ~(0b1111 << (11 % 8) * 4);
	GPIOB->AFR[1] |=  (7	  << (11 % 8) * 4);
	/*
	GPIOB->PUPDR  &= ~(0b11 << 10 * 2);
	GPIOB->PUPDR  |=  (0b01 << 10 * 2);
	GPIOB->OTYPER |=  (0b1  << 10);
	*/
	/*
	 * 		USART
	 */
	USART3->CR1 |= (0b1 << 13); //Enable
	USART3->CR1 &= ~(0b1 << 12); // 1 start bit, 8 data bits, n stop bits

	/*
	 * Configuring baudrate
	 *
	 * F_clk = 42 MHz
	 * zeljeni baud: 115200
	 * Baud = F_clk / (16 * USARTDIV)
	 * 115200 = 42000000 / (16 * USARTDIV) -> USARTDIV = 42000000 / (16 * 115200)
	 * USARTDIV = 22.78645833333333 = DIV_Mantissa + (DIV_Fraction / 8 x (2 - OVER8))
	 * Mantissa => 22
	 * DIV_Fraction = 16 * 0.78645833333333 -> DIV_Fraction = 12.58 ~ 12 = 0xC
	 */
	USART3->BRR =  ( 12 | (22 << 4));
	USART3->CR1 |= (0b1 << 2); //enable RX
	USART3->CR1 |= (0b1 << 3); //enable TX

	USART3->CR1 |= (0b1 << 5); // ISR samo na RX

	// BEGIN AX podesavanja

	USART3->CR2 &= ~((0b1 << 11) | (0b1 << 14));
	USART3->CR3 &= ~((0b1 << 1) | (0b1 << 5));
	//USART6->CR3 &= ~(0b1 << 3); // half duplex disable
	USART3->CR3 |=  (0b1 << 3); // half duplex enable

	// END AX podesavanja

	//NVIC->ISER[(int)(39 / 32)] |= (0b1 << (39 % 32));
}

void sendChar(unsigned char ch)
{
	USART3->DR = ch;
	while(! (USART3->SR & (0b1 << 6)));
}

void sendStr(unsigned char* str)
{
	while( *str != '\0')
	{
		sendChar(*str++);
	}
}

void sendArray(uint8_t* array, size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		sendChar(array[i]);
	}
}

void USART3_IRQHandler()
{
	if(USART3->SR & (1 << 5))
	{

		USART3->SR &= ~(0b1 << 5);
	}
}
