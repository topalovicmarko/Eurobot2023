/*
 * enkoder.h
 *
 *  Created on: Apr 18, 2023
 *      Author: Marko Topalovic
 */

#ifndef LIB_PERIFERIJE_ENKODER_ENKODER_H_
#define LIB_PERIFERIJE_ENKODER_ENKODER_H_
#include "stm32f4xx.h"
#include <stdint.h>
void enkoder_init();
int16_t enkoder_brzina();
int16_t enkoder_brzina2();

#endif /* LIB_PERIFERIJE_ENKODER_ENKODER_H_ */
