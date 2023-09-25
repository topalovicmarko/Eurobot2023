/*
 * maxxoni.h
 *
 *  Created on: Apr 18, 2023
 *      Author: Marko Topalovic
 */

#ifndef LIB_MODULI_MAXXONI_H_
#define LIB_MODULI_MAXXONI_H_

#include <stdint.h>
#include <stdbool.h>
#include "stm32f4xx.h"

void maxxoni_init (void);
void okretanje_m1 (float procenat);
void okretanje_m2 (float procenat);
void motor1_smer(bool);
void motor2_smer(bool);


#endif /* LIB_MODULI_MAXXONI_H_ */
