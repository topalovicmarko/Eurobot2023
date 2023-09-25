/*
 * enkoder.c
 *
 *  Created on: Apr 18, 2023
 *      Author: Marko Topalovic
 */

#include "enkoder.h"

static void init_tim3(void);
static void init_tim4(void);

void enkoder_init() {
	init_tim3();
	init_tim4();
}

static void init_tim3(void) {
	//Podesavanje tajmera 3 za rad sa enkoderom

	//Dozvola takta, PB4 i PB5
	RCC->AHB1ENR |= (0b1 << 1); //dozvola takta portu B

	//Pin 4 da bude alternativna funkcija
	const uint8_t pin_4 = 4;
	const uint8_t pin_5 = 5;
	const uint8_t alternativna_funkcija = 2;

	GPIOB->MODER &= ~(0b11 << 2 * pin_4); //prvo oba na nulu
	GPIOB->MODER |= (0b10 << 2 * pin_4);

	GPIOB->AFR[pin_4 / 8] &= ~(0b1111 << 4 * (pin_4 % 8)); //treba postaviti 4 pina, prvo na nule
	GPIOB->AFR[pin_4 / 8] |= (alternativna_funkcija << 4 * (pin_4 % 8));

	GPIOB->MODER &= ~(0b11 << 2 * pin_5); //isto to za pin 5
	GPIOB->MODER |= (0b10 << 2 * pin_5);

	GPIOB->AFR[pin_5 / 8] &= ~(0b1111 << 4 * (pin_5 % 8));
	GPIOB->AFR[pin_5 / 8] |= (alternativna_funkcija << 4 * (pin_5 % 8));

	//Podesavanje tajmera 3

	RCC->APB1ENR |= (0b1 << 1);

	TIM3->PSC = 0; //necemo delitelj frekvencije
	TIM3->ARR = 0xFFFF; //16b, 16 jedinica, velicina registra

	TIM3->SMCR &= ~(0b111 << 0);
	TIM3->SMCR |= (0b011 << 0); //kvadraturno dekodiranje

	//Povezivanje kanala

	//kanal A enkodera povezujemo sa kanalom 1 tajmera
	TIM3->CCMR1 &= ~(0b11 << 0);
	TIM3->CCMR1 |= (0b01 << 0);
	//kanal B enkodera povezujemo sa kanalom 2 tajmera
	TIM3->CCMR1 &= ~(0b11 << 8);
	TIM3->CCMR1 |= (0b01 << 8);

	//Invertovanje (tj neinvertovanje), JEDAN TREBA INVERTOVATI!

	TIM3->CCER &= ~((0b1 << 1) | (0b1 << 3));
	TIM3->CCER &= ~((0b1 << 5) | (0b1 << 7));

	//Ukljucivanje brojaca
	TIM3->CR1 |= (0b1 << 0);

	//TIM3 -> CNT = izbrojano stanje na enkoderu
	//TIM3 -> CR1 - BIT4 -> DIR = u koju strane se enkoder vrti
}

int16_t enkoder_brzina() {
	int16_t trenutna = 0;
	trenutna = (int16_t) TIM3->CNT;
	TIM3->CNT = 0;
	return trenutna;
}

static void init_tim4(void) //drugi tajmer za drugi enkoder
{
	//Podesavanje tajmera 4 za rad sa enkoderom

	//Dozvola takta, PB6 i PB7
	RCC->AHB1ENR |= (0b1 << 1); //dozvola takta portu B

	//Pin 6 da bude alternativna funkcija
	const uint8_t pin_6 = 6;
	const uint8_t pin_7 = 7;
	const uint8_t alternativna_funkcija = 2;

	GPIOB->MODER &= ~(0b11 << 2 * pin_6); //prvo oba na nulu
	GPIOB->MODER |= (0b10 << 2 * pin_6);

	GPIOB->AFR[pin_6 / 8] &= ~(0b1111 << 4 * (pin_6 % 8)); //treba postaviti 4 pina, prvo na nule
	GPIOB->AFR[pin_6 / 8] |= (alternativna_funkcija << 4 * (pin_6 % 8));

	GPIOB->MODER &= ~(0b11 << 2 * pin_7); //isto to za pin 5
	GPIOB->MODER |= (0b10 << 2 * pin_7);

	GPIOB->AFR[pin_7 / 8] &= ~(0b1111 << 4 * (pin_7 % 8));
	GPIOB->AFR[pin_7 / 8] |= (alternativna_funkcija << 4 * (pin_7 % 8));

	//Podesavanje tajmera 4

	RCC->APB1ENR |= (0b1 << 2);

	TIM4->PSC = 0; //necemo delitelj frekvencije
	TIM4->ARR = 0xFFFF; //16b, 16 jedinica, velicina registra

	TIM4->SMCR &= ~(0b111 << 0);
	TIM4->SMCR |= (0b011 << 0); //kvadraturno dekodiranje 011 a sad smo na 001

	//Povezivanje kanala

	//kanal A enkodera povezujemo sa kanalom 1 tajmera
	TIM4->CCMR1 &= ~(0b11 << 0);
	TIM4->CCMR1 |= (0b01 << 0);
	//kanal B enkodera povezujemo sa kanalom 2 tajmera
	TIM4->CCMR1 &= ~(0b11 << 8);
	TIM4->CCMR1 |= (0b01 << 8);

	//Invertovanje (tj neinvertovanje)

	TIM4->CCER &= ~((0b1 << 1) | (0b1 << 3));
	TIM4->CCER &= ~(0b1 << 7);
	TIM4->CCER |= (0b1 << 5);

	//Ukljucivanje brojaca
	TIM4->CR1 |= (0b1 << 0);

	//TIM3 -> CNT = izbrojano stanje na enkoderu
	//TIM3 -> CR1 - BIT4 -> DIR = u koju strane se enkoder vrti
}

int16_t enkoder_brzina2() {
	int16_t trenutna2 = 0;
	trenutna2 = (int16_t) TIM4->CNT;
	TIM4->CNT = 0;
	return trenutna2;
}
