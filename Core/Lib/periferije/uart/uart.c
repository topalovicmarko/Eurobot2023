/*
 * uart.c
 *
 *  Created on: Apr 18, 2023
 *      Author: Marko Topalovic
 */

#include "uart.h"

static void init_usart6(void);
static void upis_u_promenljivu(uint8_t podatak);

static void upis_u_bafer6(uint8_t podatak);
static void parseBafer(void);

volatile static uint8_t bafer[30] = { 0 };
volatile static uint8_t promenljiva_citanje = 0;
volatile static uint8_t velicina = 0;
volatile static uint8_t index_upisa = 0;
volatile static uint8_t index_citanja = 0;
volatile static uint8_t promenljiva_upis = 0;

volatile static uint16_t niz_AX[6] = { 0 };
volatile static uint8_t cs = 0;
volatile static uint16_t ugao = 0;
volatile static uint16_t p1 = 0;
volatile static uint16_t p2 = 0;
volatile static uint16_t p = 0;

void uart_init(void) {
	init_usart6();
}

static void init_usart6(void) {
	//Za AX-eve
	//USART6 TX - PC6
	//USART6 RX - PC7

	const uint8_t pin_tx = 6;
	const uint8_t pin_rx = 7;
	const uint8_t alternativna_funkcija = 8;

	RCC->APB2ENR |= (0b01 << 5);
	RCC->AHB1ENR |= (0b01 << 2);

	GPIOC->MODER &= ~(0b11 << 2 * pin_tx);
	GPIOC->MODER |= (0b10 << 2 * pin_tx);
	GPIOC->MODER &= ~(0b11 << 2 * pin_rx);
	GPIOC->MODER |= (0b10 << 2 * pin_rx);

	//AF8
	//Half duplex
	GPIOC->OTYPER |= (0b01 << pin_tx);
	GPIOC->PUPDR &= ~(0b11 << 2 * pin_tx);
	GPIOC->PUPDR |= (0b01 << 2 * pin_tx);

	GPIOC->AFR[0] &= ~(0b1111 << 4 * pin_tx);
	GPIOC->AFR[0] |= (alternativna_funkcija << 4 * pin_tx);
	GPIOC->AFR[0] &= ~(0b1111 << 4 * pin_rx);
	GPIOC->AFR[0] |= (alternativna_funkcija << 4 * pin_rx);

	//Podesavanje UART-A
	USART6->CR1 &= ~(0b01 << 12); //Duzina reci
	USART6->CR2 &= ~(0b11 << 12); //Broj stop bita: 1
	//Baud rate, ima formula
	USART6->BRR &= ~(0xFFFF << 0);
	USART6->BRR |= (91 << 4) | (3 << 0); //57600
	//USART6->BRR |= (22 << 4 | 13);
	//Ukljucivanje TX-a i RX-a
	USART6->CR1 |= ((0b01 << 2) | (0b01 << 3));
	//Desava se prekid kad se nesto pojavi na RX-u
	USART6->CR1 |= (0b01 << 5);
	//Ovo je potrebno da bude na nuli pise na 557 strani za half-duplex
	USART6->CR2 &= ~((0b01 << 14) | (0b01 << 11));
	USART6->CR3 &= ~((0b01 << 5) | (0b01 << 7));
	//Half duplex mode
	USART6->CR3 |= (0b01 << 3);
	//Ukljucivanje UART-a
	USART6->CR1 |= (0b01 << 13);

	const uint8_t index_prekida = 71;
	NVIC->ISER[index_prekida / 32] |= (0b01 << (index_prekida % 32));
}

void USART6_IRQHandler(void) {
	if (USART6->SR & (0b01 << 5)) {
		upis_u_bafer6(USART6->DR);
		parseBafer();
	}
}

static void upis_u_bafer6(uint8_t podatak) {
	if (velicina != 30) {
		bafer[index_upisa] = podatak;
		index_upisa = (index_upisa + 1) % 30;
		velicina++;
	} else {
		bafer[index_upisa] = podatak;
		index_upisa = (index_upisa + 1) % 30;
		index_citanja = (index_citanja + 1) % 30;
	}
}
void uart_send_byte6(uint8_t podatak) {
	USART6->DR = podatak;
	while (!(USART6->SR & (0b01 << 6))) {
		__NOP();
	}
	USART6->SR &= ~(0b01 << 6);
}
void uart_send_str6(char *str) {
	while (*str != '\0') {
		uart_send_byte(*str);
		str++;
	}
}

static void parseBafer() {

	static uint8_t i = 0;
	static uint8_t korak = 1;

	if (velicina == 0) //proveriti da li bafer nije prazan
			{
		return;
	}

	switch (korak) {
	case 1:
		if (bafer[index_citanja] == 0xFF) //da li je 255
				{
			i = 0;
			index_citanja = (index_citanja + 1) % 30;
			velicina--;
			korak = 2;
		}
		break;
	case 2:
		if (bafer[index_citanja] == 0xFF) {
			index_citanja = (index_citanja + 1) % 30;
			velicina--;
			korak = 3;
		} else {
			index_citanja = (index_citanja + 1) % 30;
			velicina--;
			korak = 1;
		}
		break;
	case 3:
		niz_AX[0] = bafer[index_citanja]; //ovde citamo ID
		index_citanja = (index_citanja + 1) % 30;
		velicina--;
		i++;
		korak = 4;
		break;
	case 4:
		niz_AX[1] = bafer[index_citanja]; //ovde citamo len
		index_citanja = (index_citanja + 1) % 30;
		velicina--;
		i++;
		korak = 5;
		break;
	case 5:
		niz_AX[2] = bafer[index_citanja]; //citamo error
		index_citanja = (index_citanja + 1) % 30;
		velicina--;
		i++;
		korak = 6;
		break;
	case 6:
		niz_AX[3] = bafer[index_citanja]; //prvi parametar pozicije
		index_citanja = (index_citanja + 1) % 30;
		velicina--;
		i++;
		korak = 7;
	case 7:
		niz_AX[4] = bafer[index_citanja]; //drugi parametar pozicije
		index_citanja = (index_citanja + 1) % 30;
		velicina--;
		i++;
		korak = 8;
		break;
	case 8:
		niz_AX[5] = bafer[index_citanja]; //checksum
		index_citanja = (index_citanja + 1) % 30;
		velicina--;
		i++;
		korak = 9;
		break;
	case 9:
		if (niz_AX[2] == 0) {
			korak = 10;
		} else {
			korak = 1;
		}
		break;

	case 10:
		cs = niz_AX[0] + niz_AX[1] + niz_AX[2] + niz_AX[3] + niz_AX[4];
		cs = ~cs;
		if (cs == niz_AX[5]) {
			korak = 11;
		} else {
			korak = 1;
		}
		break;

	case 11:
		p1 = niz_AX[3];
		p2 = niz_AX[4];

		p = p1 | (p2 << 8);

		ugao = p * 300 / 1023;

		korak = 1;
		break;
	}
}

void servo_control(uint8_t id, uint16_t ugao) {
	uint16_t x;
	uint8_t x_12_8;
	uint8_t x_3_8;
	uint8_t checksum;

	x = (ugao * 1023) / 300;

	x_12_8 = x;
	x_3_8 = (x >> 8);

	checksum = ~(id + 5 + 3 + x_12_8 + x_3_8 + 0x1E);

	uint8_t move[] =
			{ 0xFF, 0xFF, id, 0x05, 0x03, 0x1E, x_12_8, x_3_8, checksum };

	for (uint8_t i = 0; i < sizeof(move) / sizeof(*move); i++) {
		uart_send_byte6(move[i]);
	}
	tajmer_delay(50);
}

uint16_t get_ugao(void) {
	return ugao;
}
