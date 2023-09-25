/*
 * gpio.c
 *
 *  Created on: Apr 18, 2023
 *      Author: Marko Topalovic
 */

#include "gpio.h"

static void init_port_a(void);
static void init_port_c(void);

void gpio_init(void) {
	init_port_a();
	init_port_c();
}

static void init_port_a(void) {
	//LED dioda PA5
	const uint8_t pin_a = 5;

	RCC->AHB1ENR |= (0b01 << 0);
	GPIOA->MODER &= ~(0b11 << 2 * pin_a);
	GPIOA->MODER |= (0b01 << 2 * pin_a);
	GPIOA->OTYPER &= ~(0b01 << pin_a);
	GPIOA->PUPDR &= ~(0b11 << 2 * pin_a);
}
static void init_port_c(void) {
	//Button PC13
	const uint8_t pin_c = 13;
	//Cinc PC1
	const uint8_t pin_c_cinc = 1;

	RCC->AHB1ENR |= (0b01 << 2);
	GPIOC->MODER &= ~(0b11 << 2 * pin_c);
	GPIOC->MODER &= ~(0b11 << 2 * pin_c_cinc);
	GPIOC->OTYPER &= ~(0b01 << pin_c);
	GPIOC->OTYPER &= ~(0b01 << pin_c_cinc);
	GPIOC->PUPDR &= ~(0b11 << 2 * pin_c);
	GPIOC->PUPDR &= ~(0b11 << 2 * pin_c_cinc);
	//GPIOC->PUPDR |= (0b01 << 2 * pin_c_cinc);
}
bool cinc_stanje(void) {
	const uint8_t pin_c_cinc = 1;

	if (GPIOC->IDR & (0b01 << pin_c_cinc)) {
		return false;
	} else
		return true;
}
void gpio_led_stanje(bool stanje) {
	const uint8_t pin_a = 5;
	if (stanje == true) {
		GPIOA->ODR |= (0b01 << pin_a);
	} else
		GPIOA->ODR &= ~(0b01 << pin_a);
}
bool gpio_taster_stanje(void) {
	const uint8_t pin_c = 13;
	if (GPIOC->IDR & (0b01 << pin_c)) {
		return false;
	} else
		return true;
}
