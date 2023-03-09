/*
 * dac.h
 *
 *  Created on: Mar 9, 2023
 *      Author: Marko Topaplovic
 */

#ifndef LIB_PERIPHERIES_DAC_DAC_H_
#define LIB_PERIPHERIES_DAC_DAC_H_

#include <stdint.h>
#include "stm32f405xx.h"

// Prototipovi funkcija
void dac_init();
void start_dac();
void setDACValue(uint8_t dac_value);
void end_dac();

#endif /* LIB_PERIPHERIES_DAC_DAC_H_ */
