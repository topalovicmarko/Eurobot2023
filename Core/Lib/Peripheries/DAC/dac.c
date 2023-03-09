/*
 * dac.c
 *
 *  Created on: Mar 9, 2023
 *      Author: Marko Topalovic
 */

#include "dac.h"

// Prototipovi "privatnih" funkcija
static void dac_gpio_init();

void dac_init() {
	dac_gpio_init();

	RCC->APB1ENR |= (1 << 29);		//DAC PH. ENABLE

	DAC->SWTRIGR |= (1 << 0);		// Koji konventor koristimo -> channel 1
}

void dac_gpio_init() {
	RCC->AHB1ENR |= (1 << 0);			//GPIOA

	GPIOA->MODER |= (0b11 << 4 * 2); 	// PA4 -> analog mode

}

void start_dac(){
	DAC->CR |= (1 << 0); 	// DAC channel1 enabled
}
void setDACValue(uint8_t dac_value){
	DAC->DHR8R1 = dac_value;
}

void end_dac(){
	DAC->CR &= ~(1 << 0);
}
