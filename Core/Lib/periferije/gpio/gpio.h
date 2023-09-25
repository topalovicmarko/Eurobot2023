/*
 * gpio.h
 *
 *  Created on: Apr 18, 2023
 *      Author: Marko Topalovic
 */

#ifndef LIB_PERIFERIJE_GPIO_GPIO_H_
#define LIB_PERIFERIJE_GPIO_GPIO_H_

#include "stm32f4xx.h"
#include <stdbool.h>
#include <stdint.h>
void gpio_led_stanje(bool stanje);
void gpio_init(void);
bool gpio_taster_stanje(void);
bool cinc_stanje(void);

#endif /* LIB_PERIFERIJE_GPIO_GPIO_H_ */
