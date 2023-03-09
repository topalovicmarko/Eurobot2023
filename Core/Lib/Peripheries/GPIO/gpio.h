/*
 * gpio.h
 *
 *  Created on: Feb 27, 2023
 *      Author: Marko Topalovic
 */

#ifndef LIB_PERIPHERIES_GPIO_GPIO_H_
#define LIB_PERIPHERIES_GPIO_GPIO_H_
#include <stdint.h>
#include "stm32f405xx.h"

//Prototipovi
void gpio_init(void);
uint8_t debounce();

#endif /* LIB_PERIPHERIES_GPIO_GPIO_H_ */
