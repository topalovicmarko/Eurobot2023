/*
 * tajmer.h
 *
 *  Created on: Apr 18, 2023
 *      Author: Marko Topalovic
 */

#ifndef LIB_PERIFERIJE_TAJMER_TAJMER_H_
#define LIB_PERIFERIJE_TAJMER_TAJMER_H_

#include "stm32f4xx.h"
#include <stdint.h>
//#include "../Lib/moduli/pid/pid.h"

void tajmer_init(void);
uint32_t get_sistemsko_vreme(void);
void tajmer_delay(uint32_t ms);
void tajmer_delay_mikro(uint32_t ms);

#endif /* LIB_PERIFERIJE_TAJMER_TAJMER_H_ */
