/*
 * gpio.c
 *
 *  Created on: Feb 27, 2023
 *      Author: Marko Topalovic
 */

#include "gpio.h"
#include "../TIMER/timer.h"

static void gpioB_init(void);
static void gpioC_init(void);

void gpio_init(void) {
	gpioB_init();
	gpioC_init();
}

static void gpioB_init(void) {
	//External switch
	RCC->AHB1ENR |= (0b01 << 1); // GPIOB PERIPHERIE ENABLE
	GPIOB->MODER &= ~(0b11 << 0 * 2); // PB0 input
	GPIOB->PUPDR |= (0b01 << 0 * 2); // Pull-up input
}

static void gpioC_init(void) {
	// Internal diode
	RCC->AHB1ENR |= (0b01 << 2); // GPIOC PERIPHERIE ENABLE
	GPIOC->MODER |= (0b01 << 15 * 2); // PC15 output
	GPIOC->OTYPER &= ~(0b01 << 15); // Push-pull output
	//GPIOC->ODR &= ~(0b01 << 15); // Output -> LED ON
	//GPIOC->ODR |= (0b01 << 15); // Output -> LED OFF

	// External diode
	GPIOC->MODER |= (0b01 << 5 * 2); // PC5 output
	GPIOC->OTYPER &= ~(0b01 << 5); // Push-pull output
	//GPIOC->ODR |= (0b01 << 5); // Output -> LED ON
}

void ENC_enable(void)
{
	//M1 M2 ENCODER enable
	RCC->AHB1ENR |= (0b01 << 2);
	const uint8_t pin_8 = 8;
	GPIOC->MODER &= ~(0b11 << 2*pin_8);
	GPIOC->MODER |= (0b01 << 2*pin_8);
	GPIOC->OTYPER &= ~(0b01 << pin_8);
	GPIOC->PUPDR &= ~(0b11 << 2 * pin_8);
	GPIOC->ODR &= ~(0b01 << pin_8);
	//EXT ENC1 ENC2 enable
	RCC->AHB1ENR |= (0b01 << 1);
	const uint8_t pin_3 = 3;
	GPIOB->MODER &= ~(0b11 << 2*pin_3);
	GPIOB->MODER |= (0b01 << 2*pin_3);
	GPIOB->OTYPER &= ~(0b01 << pin_3);
	GPIOB->PUPDR &= ~(0b11 << 2 * pin_3);
	GPIOB->ODR &= ~(0b01 << pin_3);

}

uint8_t debounce() {
	uint8_t temp = GPIOB->IDR & (1 << 0); //External switch

	if (temp == 0) {
		// sačekati 10ms
		setTimeOut(10);
		while (isTimeOut() == 0)
			;
		if (temp != (GPIOB->IDR & (1 << 0))) {
			return 0;
		}
	}
	return 1;
}

