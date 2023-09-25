/*
 * tajmer.c
 *
 *  Created on: Apr 18, 2023
 *      Author: Marko Topalovic
 */

#include "tajmer.h"

static void init_tim10(void);
static void init_tim11(void);
void step_delay(uint32_t ms);
volatile static uint32_t sistemsko_vreme = 0;
volatile static uint32_t sistemsko_vreme_mikro = 0;
volatile static uint32_t step_vreme = 0;
void tajmer_init(void) {
	init_tim10();
	init_tim11();
}

static void init_tim10(void) {
	//Aktivacija tim_10
	RCC->APB2ENR |= (0b01 << 17);
	TIM10->PSC = 84 - 1; //84
	TIM10->ARR = 1000 - 1;
	//Sta izaziva dogadjaj
	TIM10->CR1 &= ~(0b01 << 2);
	TIM10->CR1 &= ~(0b01 << 1);
	TIM10->DIER |= (0b01 << 0);
	TIM10->EGR |= (0b01 << 0);

	while (!(TIM10->SR & (0b01 << 0))) {
		__NOP();
	}
	TIM10->SR &= ~(0b01 << 0);
	TIM10->CR1 |= (0b01 << 2);

	const uint8_t prekidni_index = 25;
	NVIC->ISER[prekidni_index / 32] |= (0b01 << (prekidni_index % 32));

	TIM10->CR1 |= (0b01 << 0);
}
static void init_tim11(void) {
	RCC->APB2ENR |= (0b01 << 16);
	TIM9->PSC = 0;
	TIM9->ARR = 84 - 1;
	TIM9->CR1 &= ~(0b01 << 2);
	TIM9->CR1 &= ~(0b01 << 1);
	TIM9->DIER |= (0b01 << 0);
	TIM9->EGR |= (0b01 << 0);

	while (!(TIM9->SR & (0b01 << 0))) {
		__NOP();
	}
	TIM9->SR &= ~(0b01 << 0);
	TIM9->CR1 |= (0b01 << 2);

	const uint8_t prekidni_index = 24;
	NVIC->ISER[prekidni_index / 32] |= (0b01 << (prekidni_index % 32));
	TIM9->CR1 |= (0b01 << 0);

}
void TIM1_BRK_TIM9_IRQHandler(void) {
	if (TIM9->SR & (0b01 << 0)) {
		TIM9->SR &= ~(0b01 << 0);
		sistemsko_vreme_mikro++;

	}
}
void TIM1_UP_TIM10_IRQHandler(void) {
	if (TIM10->SR & (0b01 << 0)) {
		TIM10->SR &= ~(0b01 << 0);
		sistemsko_vreme++;
		odometrija_stanje();
		regulacija();
	}
}
void tajmer_delay_mikro(uint32_t ms) {
	uint32_t pocetno_vreme = sistemsko_vreme_mikro;
	while (sistemsko_vreme_mikro < (pocetno_vreme + ms)) {
		__NOP();
	}
}

void step_delay(uint32_t ms) {
	uint32_t pocetno_vreme = step_vreme;
	while (step_vreme < (pocetno_vreme + ms)) {
		__NOP();
	}
}
void tajmer_delay(uint32_t ms) {
	uint32_t pocetno_vreme = sistemsko_vreme;
	while (sistemsko_vreme < (pocetno_vreme + ms)) {
		__NOP();
	}
}
uint32_t get_sistemsko_vreme_mikro(void) {
	return sistemsko_vreme_mikro;
}
uint32_t get_sistemsko_vreme(void) {
	return sistemsko_vreme;
}
