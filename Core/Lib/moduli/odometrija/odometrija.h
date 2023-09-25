/*
 * odometrija.h
 *
 *  Created on: Apr 18, 2023
 *      Author: Marko Topalovic
 */

#ifndef LIB_MODULI_ODOMETRIJA_ODOMETRIJA_H_
#define LIB_MODULI_ODOMETRIJA_ODOMETRIJA_H_

#include "../../periferije/enkoder/enkoder.h"
#include <math.h>
#include <stdint.h>
void odometrija_init();
void odometrija_stanje();
float omega;
float lin_brzina;
float distance;
float teta;
float x;
float y;


#endif /* LIB_MODULI_ODOMETRIJA_ODOMETRIJA_H_ */
