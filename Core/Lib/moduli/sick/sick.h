/*
 * sick.h
 *
 *  Created on: Apr 18, 2023
 *      Author: Marko Topalovic
 */

#ifndef LIB_MODULI_SICK_SICK_H_
#define LIB_MODULI_SICK_SICK_H_
#include "stm32f4xx.h"
#include <stdint.h>
#include <stdbool.h>
void sick_init(void);
bool sickLF(void);
bool sickMID(void);
bool sickRF(void);
bool sickLB(void);
bool sickRB(void);
#endif /* LIB_MODULI_SICK_SICK_H_ */
