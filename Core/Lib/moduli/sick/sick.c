/*
 * sick.c
 *
 *  Created on: Apr 18, 2023
 *      Author: Marko Topalovic
 */

#include "sick.h"

void sick_init(void) {

	const uint8_t pinB_1 = 1;
	const uint8_t pinB_2 = 2;
	const uint8_t pinB_13 = 13;
	const uint8_t pinB_14 = 14;
	const uint8_t pinB_15 = 15;

	RCC->AHB1ENR |= (0b1 << 1);

	GPIOB->MODER &= ~(0b11 << 2 * pinB_1);
	GPIOB->MODER &= ~(0b11 << 2 * pinB_2);
	GPIOB->MODER &= ~(0b11 << 2 * pinB_13);
	GPIOB->MODER &= ~(0b11 << 2 * pinB_14);
	GPIOB->MODER &= ~(0b11 << 2 * pinB_15);

	GPIOB->OSPEEDR |= (0b11 << 2 * pinB_1);
	GPIOB->OSPEEDR |= (0b11 << 2 * pinB_2);
	GPIOB->OSPEEDR |= (0b11 << 2 * pinB_13);
	GPIOB->OSPEEDR |= (0b11 << 2 * pinB_14);
	GPIOB->OSPEEDR |= (0b11 << 2 * pinB_15);

	GPIOB->OTYPER &= ~(0b1 << pinB_1);
	GPIOB->OTYPER &= ~(0b1 << pinB_2);
	GPIOB->OTYPER &= ~(0b1 << pinB_13);
	GPIOB->OTYPER &= ~(0b1 << pinB_14);
	GPIOB->OTYPER &= ~(0b1 << pinB_15);

	GPIOB->PUPDR &= ~(0b11 << 2 * pinB_1);
	GPIOB->PUPDR &= ~(0b11 << 2 * pinB_2);
	GPIOB->PUPDR &= ~(0b11 << 2 * pinB_13);
	GPIOB->PUPDR &= ~(0b11 << 2 * pinB_14);
	GPIOB->PUPDR &= ~(0b11 << 2 * pinB_15);

	GPIOB->PUPDR |= (0b01 << 2 * pinB_1);
	GPIOB->PUPDR |= (0b01 << 2 * pinB_2);
	GPIOB->PUPDR |= (0b01 << 2 * pinB_13);
	GPIOB->PUPDR |= (0b01 << 2 * pinB_14);
	GPIOB->PUPDR |= (0b01 << 2 * pinB_15);
}

bool sickLF(void) {
	bool stanje = false;
	if (GPIOB->IDR & (0b1 << 1)) {
		stanje = false;
	} else {
		stanje = true;
	}
	return stanje;
}
bool sickMID(void) {
	bool stanje = false;
	if (GPIOB->IDR & (0b1 << 2)) {
		stanje = true;
	} else {
		stanje = false;
	}
	return stanje;
}
bool sickRF(void) {
	bool stanje = false;
	if (GPIOB->IDR & (0b1 << 13)) {
		stanje = true;
	} else {
		stanje = false;
	}
	return stanje;
}
bool sickLB(void) {
	bool stanje = false;
	if (GPIOB->IDR & (0b1 << 14)) {
		stanje = true;
	} else {
		stanje = false;
	}
	return stanje;
}
bool sickRB(void) {
	bool stanje = false;
	if (GPIOB->IDR & (0b1 << 15)) {
		stanje = true;
	} else {
		stanje = false;
	}
	return stanje;
}

