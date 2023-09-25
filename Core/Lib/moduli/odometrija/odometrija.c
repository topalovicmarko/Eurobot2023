/*
 * odometrija.c
 *
 *  Created on: Apr 18, 2023
 *      Author: Marko Topalovic
 */

#include "odometrija.h"

static float d = 0.0f;
static float precnik_ot = 0.0f;
static float inc2mm = 0.0f;

int16_t vd_inc;
int16_t vl_inc;

void
odometrija_init (void)
{
  omega = 0.0f;
  lin_brzina = 0.0f;
  distance = 0.0f;
  teta = 0.0f;
  d = 369.0f; // mm
  precnik_ot = 60.95f; // mm
  float obim_ot = precnik_ot * M_PI;
  float N = 1000 / obim_ot;
  float n = N * 2048 * 4;
  inc2mm = 1000 / n;
}

void
odometrija_stanje (void)
{
  vd_inc = enkoder_brzina();
  vl_inc = enkoder_brzina2();

  omega = (float)(vd_inc - vl_inc) / d;
  lin_brzina = (float)(vd_inc + vl_inc) / 2.0;

  lin_brzina *= inc2mm;
  omega *= inc2mm;

  distance += lin_brzina;

  teta += omega;
  x += lin_brzina * cos(teta);
  y += lin_brzina * sin(teta);
}
