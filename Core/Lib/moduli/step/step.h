/*
 * step.h
 *
 *  Created on: Apr 18, 2023
 *      Author: Marko Topalovic
 */

#ifndef LIB_MODULI_STEP_STEP_H_
#define LIB_MODULI_STEP_STEP_H_

#include "stm32f4xx.h"
#include <stdint.h>
#include "../Lib/periferije/tajmer/tajmer.h"
void step_init(void);
void steper_pun_ugao(void);
void steper_suprotan_ugao(void);
void steper_stop(void);

#endif /* LIB_MODULI_STEP_STEP_H_ */
