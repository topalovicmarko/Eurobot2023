/*
 * encoder.c
 *
 *  Created on: Mar 12, 2023
 *      Author: Marko Topalovic
 */

#include "encoder.h"

//Prototipovi privatnih funkcija
static void tim2_init(void);
static void tim3_init(void);
static void tim4_init(void);
static void tim8_init(void);

void encoder_init() {
	tim2_init();
	tim3_init();
	tim4_init();
	tim8_init();
}

static void tim2_init(void) {
	// M1 INTERN ENCODER A	(TIM2 CH1)	->	GPA0
	// M1 INTERN ENCODER B	(TIM2 CH2)	->	GPA1

	const uint8_t pin_0 = 0;
	const uint8_t pin_1 = 1;

	RCC->AHB1ENR |= (1 << 0);

	GPIOA->MODER |= (0b10 << 2 * pin_0);	//Mode alt. f
	GPIOA->MODER |= (0b10 << 2 * pin_1);

	GPIOA->OSPEEDR |= (0b11 << 2 * pin_0);	//High speed
	GPIOA->OSPEEDR |= (0b11 << 2 * pin_1);

	GPIOA->AFR[0] |= (0b0001 << pin_0 * 4);	// Alt. f. for tim2
	GPIOA->AFR[0] |= (0b0001 << pin_1 * 4);

	RCC->APB1ENR |= (0b01 << 0);	//TIM2 enable

	TIM2->PSC = 0;	//Mora da se podesi - ne koristimo ga

	//CH_A ENC -> CH1 TIM
	TIM2->CCMR1 |= (0b01 << 0);

	//CH_B ENC -> CH2 TIM
	TIM2->CCMR1 |= (0b01 << 8);

	TIM2->ARR = 0xFFFF; //65535 -> Ovde se resetuje na 0 ili na max

	//Registri dozvole
	TIM2->CCER &= ~((0b01 << 1) | (0b01 << 3)); //Rastuća ivica se ne invertuje na CH1
	TIM2->CCER &= ~((0b01 << 5) | (0b01 << 7));	//Rastuća ivica se ne invertuje na CH2

	TIM2->SMCR |= (0b011 << 0);		//Encoder mode 3 - očitavanje oba kanala

	TIM2->CR1 |= (1 << 2);	//Update req. source

	TIM2->DIER |= (1 << 0);	//Dozvola interrupta

	TIM2->EGR |= (1 << 0);

	TIM2->CR1 |= (1 << 0);	//Counter enabled

	//promenljiva = TIM2->CNT;	//Za iščitavanje
}

static void tim3_init(void) {
	RCC->AHB1ENR |= (0b01 << 1);

	const uint8_t pin_4 = 4;
	const uint8_t pin_5 = 5;

	GPIOB->MODER &= ~(0b01 << 2 * pin_4);
	GPIOB->MODER |= (0b10 << 2 * pin_4);

	const uint8_t alternativna_funkcija = 2;

	GPIOB->AFR[pin_4 / 8] &= ~(0b1111 << 4 * (pin_4 % 8));
	GPIOB->AFR[pin_4 / 8] |= (alternativna_funkcija << 4 * (pin_4 % 8));

	GPIOB->MODER &= ~(0b01 << 2 * pin_5);
	GPIOB->MODER |= (0b10 << 2 * pin_5);
	GPIOB->AFR[pin_5 / 8] &= ~(0b1111 << 4 * (pin_5 % 8));
	GPIOB->AFR[pin_5 / 8] |= (alternativna_funkcija << 4 * (pin_5 % 8));

	//podesavanje tajmera

	RCC->APB1ENR |= (0b01 << 1);

	TIM3->PSC = 0;
	TIM3->ARR = 0xFFFF; //65535

	TIM3->SMCR &= ~(0b111 << 0);
	TIM3->SMCR |= (0b011 << 0);

	//Kanal A enkodera povezujemo sa kanalom 1 tajmera
	TIM3->CCMR1 &= ~(0b11 << 0);
	TIM3->CCMR1 |= (0b01 << 0);
	//Kanal B enkodera povezujemo sa kanalom 2 tajmera
	TIM3->CCMR1 &= ~(0b11 << 8);
	TIM3->CCMR1 |= (0b01 << 8);

	TIM3->CCER &= ~((0b01 << 1) | (0b01 << 3)); //moze i sa maskom 0b101<<1
	TIM3->CCER &= ~((0b01 << 5) | (0b01 << 7));

	TIM3->CR1 |= (0b01 << 0);
}

static void tim4_init(void) {
	RCC->AHB1ENR |= (0b01 << 1);

	const uint8_t pin_6 = 6;
	const uint8_t pin_7 = 7;

	GPIOB->MODER &= ~(0b01 << 2 * pin_6);
	GPIOB->MODER |= (0b10 << 2 * pin_6);

	const uint8_t alternativna_funkcija = 2;

	GPIOB->AFR[pin_6 / 8] &= ~(0b1111 << 4 * (pin_6 % 8));
	GPIOB->AFR[pin_6 / 8] |= (alternativna_funkcija << 4 * (pin_6 % 8));

	GPIOB->MODER &= ~(0b01 << 2 * pin_7);
	GPIOB->MODER |= (0b10 << 2 * pin_7);
	GPIOB->AFR[pin_7 / 8] &= ~(0b1111 << 4 * (pin_7 % 8));
	GPIOB->AFR[pin_7 / 8] |= (alternativna_funkcija << 4 * (pin_7 % 8));

	//podesavanje tajmera

	RCC->APB1ENR |= (0b01 << 2);

	TIM4->PSC = 0;
	TIM4->ARR = 0xFFFF; //65535

	TIM4->SMCR &= ~(0b111 << 0);
	TIM4->SMCR |= (0b011 << 0);

	//Kanal A enkodera povezujemo sa kanalom 1 tajmera
	TIM4->CCMR1 &= ~(0b11 << 0);
	TIM4->CCMR1 |= (0b01 << 0);
	//Kanal B enkodera povezujemo sa kanalom 2 tajmera
	TIM4->CCMR1 &= ~(0b11 << 8);
	TIM4->CCMR1 |= (0b01 << 8);

	TIM4->CCER &= ~((0b01 << 1) | (0b01 << 3)); //moze i sa maskom 0b101<<1
	TIM4->CCER &= ~((0b01 << 5) | (0b01 << 7));

	TIM4->CR1 |= (0b01 << 0);
}

static void tim8_init(void) {
	RCC->AHB1ENR |= (0b01 << 2);

	const uint8_t pin_6 = 6;
	const uint8_t pin_7 = 7;
	const uint8_t alternativna_funkcija = 3;

	GPIOC->MODER &= ~(0b01 << 2 * pin_6);
	GPIOC->MODER |= (0b10 << 2 * pin_6);
	GPIOC->AFR[pin_6 / 8] &= ~(0b1111 << 4 * (pin_6 % 8));
	GPIOC->AFR[pin_6 / 8] |= (alternativna_funkcija << 4 * (pin_6 % 8));

	GPIOC->MODER &= ~(0b01 << 2 * pin_7);
	GPIOC->MODER |= (0b10 << 2 * pin_7);
	GPIOC->AFR[pin_7 / 8] &= ~(0b1111 << 4 * (pin_7 % 8));
	GPIOC->AFR[pin_7 / 8] |= (alternativna_funkcija << 4 * (pin_7 % 8));

	//podesavanje tajmera

	RCC->APB2ENR |= (0b01 << 1);

	TIM8->PSC = 0;
	TIM8->ARR = 0xFFFF; //65535

	TIM8->SMCR &= ~(0b111 << 0);
	TIM8->SMCR |= (0b011 << 0);

	//Kanal A enkodera povezujemo sa kanalom 1 tajmera
	TIM8->CCMR1 &= ~(0b11 << 0);
	TIM8->CCMR1 |= (0b01 << 0);
	//Kanal B enkodera povezujemo sa kanalom 2 tajmera
	TIM8->CCMR1 &= ~(0b11 << 8);
	TIM8->CCMR1 |= (0b01 << 8);

	TIM8->CCER &= ~((0b01 << 1) | (0b01 << 3)); //moze i sa maskom 0b101<<1
	TIM8->CCER &= ~((0b01 << 5) | (0b01 << 7));

	TIM8->CR1 |= (0b01 << 0);
}

