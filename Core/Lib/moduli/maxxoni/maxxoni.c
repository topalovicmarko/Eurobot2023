/*
 * maxxoni.c
 *
 *  Created on: Apr 18, 2023
 *      Author: Marko Topalovic
 */

#include "maxxoni.h"

static void pwm_tim2_init(void);
static void pwm_tim5_init(void);
static void mode_init(void);

void maxxoni_init() {
	pwm_tim2_init();
	pwm_tim5_init();
	mode_init();
}
static void mode_init(void) {
	// M1
	const uint8_t m1_mode_pin1 = 4;
	const uint8_t m1_mode_pin2 = 15;
	GPIOA->MODER &= ~(0b11 << 2 * m1_mode_pin1);
	GPIOA->MODER |= (0b01 << 2 * m1_mode_pin1);

	GPIOA->OTYPER &= ~(0b1 << m1_mode_pin1);

	GPIOA->OSPEEDR &= ~(0b11 << 2 * m1_mode_pin1);
	GPIOA->OSPEEDR |= (0b11 << 2 * m1_mode_pin1);

	GPIOA->PUPDR &= ~(0b11 << 2 * m1_mode_pin1);

	GPIOA->MODER &= ~(0b11 << 2 * m1_mode_pin2);
	GPIOA->MODER |= (0b01 << 2 * m1_mode_pin2);

	GPIOA->OTYPER &= ~(0b1 << m1_mode_pin2);

	GPIOA->OSPEEDR &= ~(0b11 << 2 * m1_mode_pin2);
	GPIOA->OSPEEDR |= (0b11 << 2 * m1_mode_pin2);

	GPIOA->PUPDR &= ~(0b11 << 2 * m1_mode_pin2);

	// M2
	const uint8_t m2_mode_pin1 = 11;
	const uint8_t m2_mode_pin2 = 12;
	GPIOA->MODER &= ~(0b11 << 2 * m2_mode_pin1);
	GPIOA->MODER |= (0b01 << 2 * m2_mode_pin1);

	GPIOA->OTYPER &= ~(0b1 << m2_mode_pin1);

	GPIOA->OSPEEDR &= ~(0b11 << 2 * m2_mode_pin1);
	GPIOA->OSPEEDR |= (0b11 << 2 * m2_mode_pin1);

	GPIOA->PUPDR &= ~(0b11 << 2 * m2_mode_pin1);

	GPIOA->MODER &= ~(0b11 << 2 * m2_mode_pin2);
	GPIOA->MODER |= (0b01 << 2 * m2_mode_pin2);

	GPIOA->OTYPER &= ~(0b1 << m2_mode_pin2);

	GPIOA->OSPEEDR &= ~(0b11 << 2 * m2_mode_pin2);
	GPIOA->OSPEEDR |= (0b11 << 2 * m2_mode_pin2);

	GPIOA->PUPDR &= ~(0b11 << 2 * m2_mode_pin2);
}
static void pwm_tim2_init(void) {

	const uint8_t pinA = 1;

	RCC->AHB1ENR |= (0b1 << 0); //Port A EN
	RCC->APB1ENR |= (0b1 << 0); //TIM2EN

	GPIOA->MODER &= ~(0b11 << 2 * pinA);
	GPIOA->MODER |= (0b10 << 2 * pinA);

	//Alt funkcija
	const uint8_t alt_funkcija = 1;

	GPIOA->AFR[pinA / 8] &= ~(0b1111 << (pinA % 8) * 4);
	GPIOA->AFR[pinA / 8] |= (alt_funkcija << (pinA % 8) * 4);

	//Pitati Cilaga kako se odredjuje ovo!
	TIM2->PSC = 0;
	TIM2->ARR = 4000 - 1;

	TIM2->CCMR1 &= ~(0b111 << 12);
	TIM2->CCMR1 |= (0b110 << 12);

	TIM2->CCMR1 |= (0b1 << 11);
	TIM2->CCMR1 &= ~(0b11 << 8); // CC2S

	TIM2->CR1 |= (0b1 << 7); //auto-reload

	TIM2->CCER |= (0b1 << 4); // enebale ch 2

	TIM2->CR1 &= ~(0b1 << 2);
	TIM2->CR1 &= ~(0b1 << 1);

	TIM2->EGR |= (0b1 << 0); //Reset brojaca

	while (!(TIM2->SR & (0b1 << 0))) {
		__NOP();
	}
	TIM2->SR &= ~(0b1 << 0); //Cistimo statusni registar

	TIM2->CR1 |= (0b1 << 2);
	TIM2->CR1 |= (0b1 << 0);
}

static void pwm_tim5_init(void) {

	const uint8_t pinA = 0;

	RCC->AHB1ENR |= (0b1 << 0); //Port A EN
	RCC->APB1ENR |= (0b1 << 3); //TIM5EN

	GPIOA->MODER &= ~(0b11 << 2 * pinA);
	GPIOA->MODER |= (0b10 << 2 * pinA);

	//Alt funkcija
	const uint8_t alt_funkcija = 2;

	GPIOA->AFR[pinA / 8] &= ~(0b1111 << (pinA % 8) * 4);
	GPIOA->AFR[pinA / 8] |= (alt_funkcija << (pinA % 8) * 4);

	//Pitati Cilaga kako se odredjuje ovo!
	TIM5->PSC = 0;
	TIM5->ARR = 4000 - 1;

	TIM5->CCMR1 &= ~(0b111 << 4);
	TIM5->CCMR1 |= (0b110 << 4);

	TIM5->CCMR1 |= (0b1 << 3);
	TIM5->CCMR1 &= ~(0b11 << 0); // CC1S

	TIM5->CR1 |= (0b1 << 7); //auto-reload

	TIM5->CCER |= (0b1 << 0); // enebale ch 2

	TIM5->CR1 &= ~(0b1 << 2);
	TIM5->CR1 &= ~(0b1 << 1);

	TIM5->EGR |= (0b1 << 0); //Reset brojaca

	while (!(TIM5->SR & (0b1 << 0))) {
		__NOP();
	}
	TIM5->SR &= ~(0b1 << 0); //Cistimo statusni registar

	TIM5->CR1 |= (0b1 << 2);
	TIM5->CR1 |= (0b1 << 0);
}

void okretanje_m1(float procenat) {
	//100 : (4000-1) = procenat : faktor_ispune
	TIM2->CCR2 = (uint16_t) (((4000 - 1) * procenat) / 100);
}

void okretanje_m2(float procenat) {
	//100 : (4000-1) = procenat : faktor_ispune
	TIM5->CCR1 = (uint16_t) (((4000 - 1) * procenat) / 100);
}

void motor1_smer(bool smer) {
	if (smer) {
		GPIOA->ODR &= ~(0b1 << 4);
		GPIOA->ODR |= (0b1 << 15);
	} else {
		GPIOA->ODR |= (0b1 << 4);
		GPIOA->ODR &= ~(0b1 << 15);
	}
}

void motor2_smer(bool smer) {
	if (smer) {
		GPIOA->ODR &= ~(0b1 << 11);
		GPIOA->ODR |= (0b1 << 12);
	} else {
		GPIOA->ODR |= (0b1 << 11);
		GPIOA->ODR &= ~(0b1 << 12);
	}
}

