/*
 * step.c
 *
 *  Created on: Apr 18, 2023
 *      Author: Marko Topalovic
 */
#include "step.h"

const uint8_t step_pin = 8;
const uint8_t dir_pin = 5;

void step_init(void) {
	//PC8 - Step pin - PWM
	//PC5 - Dir pin - GPIO
	RCC->AHB1ENR |= (0b01 << 2);

	GPIOC->MODER &= ~(0b11 << 2 * step_pin);
	GPIOC->MODER |= (0b01 << 2 * step_pin);
	GPIOC->OTYPER &= ~(0b1 << step_pin);
	//GPIOC->OTYPER |= (0b01 << step_pin);
	GPIOA->OSPEEDR &= ~(0b11 << 2 * step_pin);
	GPIOA->OSPEEDR |= (0b11 << 2 * step_pin);
	GPIOC->PUPDR &= ~(0b11 << 2 * step_pin);

	GPIOC->MODER &= ~(0b11 << 2 * dir_pin);
	GPIOC->MODER |= (0b01 << 2 * dir_pin);
	GPIOC->OTYPER &= ~(1 << dir_pin);
	GPIOA->OSPEEDR &= ~(0b11 << 2 * dir_pin);
	GPIOA->OSPEEDR |= (0b11 << 2 * dir_pin);
	//GPIOC->OTYPER |= (0b01 << dir_pin);
	GPIOC->PUPDR &= ~(0b11 << 2 * dir_pin);
}

void steper_pun_ugao(void) {
	GPIOC->ODR |= (0b01 << dir_pin);
	for (int i = 0; i < 400; i++) {
		GPIOC->ODR |= (0b01 << step_pin);
		tajmer_delay_mikro(500);
		GPIOC->ODR &= ~(0b01 << step_pin);
		tajmer_delay_mikro(500);
	}
}

void steper_suprotan_ugao(void) {
	GPIOC->ODR &= ~(0b01 << dir_pin);
	for (int i = 0; i < 400; i++) {
		GPIOC->ODR |= (0b01 << step_pin);
		tajmer_delay_mikro(500);
		GPIOC->ODR &= ~(0b01 << step_pin);
		tajmer_delay_mikro(500);
	}
}

void steper_stop(void) {
	GPIOC->ODR &= ~(0b01 << step_pin);
}

