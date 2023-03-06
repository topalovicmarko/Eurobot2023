/*
 * timer.h
 *
 *  Created on: Feb 27, 2023
 *      Author: Marko Topalovic
 */

#ifndef LIB_PERIPHERIES_TIMER_TIMER_H_
#define LIB_PERIPHERIES_TIMER_TIMER_H_

#include <stdint.h>

//Prototipovi
void timer_init();
uint8_t isTimeFlag95s();
uint8_t isTimeFlag100s();
uint32_t getSysTime();
void setTimeOut(uint32_t delay);
uint8_t isTimeOut();

#endif /* LIB_PERIPHERIES_TIMER_TIMER_H_ */
