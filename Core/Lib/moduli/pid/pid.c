/*
 * pid.c
 *
 *  Created on: Apr 18, 2023
 *      Author: Marko Topalovic
 */

#include "stm32f4xx.h"
#include "stdbool.h"
#include "pid.h"
#include <math.h>
#include "../maxxoni/maxxoni.h"
#include "../odometrija/odometrija.h"
#include "../../periferije/enkoder/enkoder.h"


bool napred = true;
bool nazad = false;

static volatile float Kpd;
static volatile float Kid;
static volatile float Kdd;
static volatile float Kp_teta;
static volatile float Ki_teta;
static volatile float Kd_teta;

volatile float Vdl = 0;
volatile float Vl = 0;
volatile float Vdr = 0;
volatile float Vr = 0;

static float volatile teta_ei_max;
static float volatile teta_ei_min;
static float volatile d_ei_max;
static float volatile d_ei_min;
float volatile teta_d;
volatile float teta_e, teta_ei, teta_de, teta_de_p;
volatile float teta_min;
volatile float d_e, d_ei, d_de_p, d_de;
static volatile float d_e_min = 0.005;
volatile int smer = 1;
int faza=0;
volatile float x_e = 0.0;
volatile float x_el = 0.0;
volatile float y_el = 0.0;
volatile float y_e = 0.0;
volatile float acc = 0.5;
volatile float x_d;
volatile float y_d;
volatile float t_ce;

void pid_init(void)
{

	teta_min=0.0178;


	Kp_teta = 40; //51
	Ki_teta = 0.14; //0.15
	Kd_teta = 40000;  //40000

	Kpd = 110; //	17
	Kid = 0.13; //	0.15
	Kdd = 130000; //   110000

	d_ei_max = 100;
	d_ei_min = -100;


	teta_ei_max = 130;
	teta_ei_min = -130;
}

void regulacija_ugla(void) {


	teta_e = teta_d - teta; //proporcionalno dejstvo*
	teta_ei += teta_e; //integralno dejstvo
	teta_de = teta_e - teta_de_p;
	teta_de_p = teta_de;

	if (teta_ei > teta_ei_max) {
		teta_ei = teta_ei_max;
	} else if (teta_ei < teta_ei_min) {
		teta_ei = teta_ei_min;
	}

	if (fabs(teta_e) > teta_min) {

		Vdr = -(Kp_teta * teta_e + Ki_teta * teta_ei + Kd_teta * teta_de);
		Vdl = +(Kp_teta * teta_e + Ki_teta * teta_ei + Kd_teta * teta_de);

		if (fabs(Vdr) > 100) {
				if (Vdr < 0) {
					Vdr = -100;
				} else if (Vdr > 0) {
					Vdr = 100;
				}
			}
			if (fabs(Vdl) > 100) {
				if (Vdl < 0) {
					Vdl = -100;
				} else if (Vdl > 0) {
					Vdl = 100;
				}
			}

			if (Vl < Vdl)
				Vl += 0.5;
			if (Vl > Vdl)
				Vl -= 0.5;
			if (Vr > Vdr)
				Vr -= 0.5;
			if (Vr < Vdr)
				Vr += 0.5;

			if (Vl < 0) // smer 2
					{
				okretanje_m2(fabs(Vl));
				motor2_smer(nazad);
			} else if (Vl > 0) { // smer 1
				okretanje_m2(fabs(Vl));
				motor2_smer(napred);
			}
			if (Vr < 0) { //smer 2
				okretanje_m1(fabs(Vr));
				motor1_smer(nazad);
			} else if (Vr > 0) { //smer 1
				okretanje_m1(fabs(Vr));
				motor1_smer(napred);
			}

	}
//	else {
//		okretanje_m1(0);
//		okretanje_m2(0);
//	}
}

void regulacija(void) {
	x_d = 450;
	y_d = 0;
	if (faza == 0) {          /////////////////////////faza0

		x_e = x_d - (float)x;  //greska x, zadato - trenutno
		y_e = y_d - (float)y;

		x_el = x_e*cosf((float)teta) + y_e*sinf((float)teta);
		y_el = y_e*cosf((float)teta) - x_e*sinf((float)teta);

		if (smer == 1){
			t_ce = atan2f(y_el, x_el);
		} else if (smer == 2){
			t_ce = atan2f(-y_el, -x_el);
		}

		if (t_ce < -M_PI)
			t_ce += 2 * M_PI;
		if (t_ce > M_PI)
			t_ce -= 2 * M_PI;

		teta_e = t_ce; // te pi/2 pi/4

		teta_ei += teta_e;
		teta_de = teta_e - teta_de_p; //tde pi/2 -pi/4
		teta_de_p = teta_e;

		if (teta_ei > teta_ei_max) {
			teta_ei = teta_ei_max;
		} else if (teta_ei < teta_ei_min) {
			teta_ei = teta_ei_min;
		}

		Vdr = +(Kp_teta * teta_e + Ki_teta * teta_ei + Kd_teta * teta_de);
		Vdl = -(Kp_teta * teta_e + Ki_teta * teta_ei + Kd_teta * teta_de);

		//prosledi_pwm(Vdr, Vdl, Vr, Vl);
		acc = 0.5;

		if (fabs(teta_e) < M_PI/20)
			acc = 1;

		if (fabs(teta_e) < teta_min) {
			acc = 1;
			//medju_stanje();
			faza = 1;
			teta_ei = 0;
			d_ei = 0;
			teta_de = 0;
			d_de = 0;
			teta_de_p = teta_de;
			d_de_p = d_de;
		}

	} else if (faza == 1) { ///////////////////////////faza1////////////////////////////////////////////////////////////////////////////
		x_e = x_d - x;
		y_e = y_d - y;

		x_el = x_e*cosf(teta) + y_e*sinf(teta);
		y_el = -x_e*sinf(teta) + y_e*cosf(teta);

		if (smer == 1){
			t_ce = atan2f(y_el, x_el);
		} else if (smer == 2){
			t_ce = atan2f(-y_el, -x_el);
		}

		if (t_ce < -M_PI)
			t_ce += 2 * M_PI;
		if (t_ce > M_PI)
			t_ce -= 2 * M_PI;

		if(smer == 1){
			d_e = sqrt(x_el * x_el + y_el * y_el) / 1000; //u metrima
		} else if(smer == 2){
			d_e = -sqrt(x_el * x_el + y_el * y_el) / 1000;
		}

		if (fabs (t_ce) > (M_PI /2) )
		     // if ((theta_ce > ((M_PI/2) + teta)) || (theta_ce < (-(M_PI/2) + teta)))
			{
			      d_e *= -1;
			    if(t_ce>0)
				t_ce -= M_PI;
			      else
				t_ce += M_PI;
			 }

		teta_e = t_ce;
		teta_ei += teta_e;
		teta_de = teta_e - teta_de_p;				//tde pi/2 -pi/4
		teta_de_p = teta_e;

		d_ei += d_e;
		d_de = d_e - d_de_p;				//tde pi/2 -pi/4
		d_de_p = d_e;

		if (d_ei > d_ei_max)
			d_ei = d_ei_max;
		if (d_ei < d_ei_min)
			d_ei = d_ei_min;

		if (teta_ei > teta_ei_max) {
			teta_ei = teta_ei_max;
		} else if (teta_ei < teta_ei_min) {
			teta_ei = teta_ei_min;
		}

		Vdr = +(Kpd * d_e + Kid * d_ei + Kdd * d_de);
		Vdl = +(Kpd * d_e + Kid * d_ei + Kdd * d_de);

		acc = 0.5;

		if (fabs (d_e) < 0.1)
			acc = 1;
		//prosledi_pwm(Vdr, Vdl, Vr, Vl);
		if (fabs (d_e) > 0.1)
			{
			  // uticaj orijentacije na regulciju
			  Vdl -= 1 * (Kp_teta * teta_e + Ki_teta * teta_ei + Kd_teta * teta_de);
			  Vdr += 1 * (Kp_teta * teta_e + Ki_teta * teta_ei + Kd_teta * teta_de);
			}
		      else
			{
			  Vdl -= 0.1 * (Kp_teta * teta_e + Ki_teta * teta_ei + Kd_teta * teta_de);
			  Vdr += 0.1 * (Kp_teta * teta_e + Ki_teta * teta_ei + Kd_teta * teta_de);
			}

		if (fabs(d_e) < d_e_min) {
			acc = 1;
			//medju_stanje();
			teta_ei = 0;
			d_ei = 0;
			faza = 2;
			d_de_p = 0;
			teta_de_p = 0;
		}

	}
	else if ((faza == 2)||(faza == 3)) {

		x_e = x_d - x;
		y_e = y_d - y;

		x_el = x_e*cosf(teta) + y_e*sinf(teta);
		y_el = -x_e*sinf(teta) + y_e*cosf(teta);
		d_e = sqrt(x_el * x_el + y_el * y_el) / 1000; //u metrima

		teta_e = teta_d - teta;

		if (teta_e < -M_PI)
			teta_e += 2 * M_PI;
		if (teta_e > M_PI)
			teta_e -= 2 * M_PI;

		teta_ei += teta_e;
		teta_de = teta_e - teta_de_p; //tde pi/2 -pi/4
		teta_de_p = teta_e;

		if (teta_ei > teta_ei_max) {
			teta_ei = teta_ei_max;
		} else if (teta_ei < teta_ei_min) {
			teta_ei = teta_ei_min;
		}

		Vdr = +(Kp_teta * teta_e + Ki_teta * teta_ei + Kd_teta * teta_de);
		Vdl = -(Kp_teta * teta_e + Ki_teta * teta_ei + Kd_teta * teta_de);


		if(faza == 3)
		{
			if (x_el<0){
				d_e*=-1;
			}
			d_ei += d_e;
			d_de = d_e - d_de_p;				//tde pi/2 -pi/4
			d_de_p = d_e;

			if (d_ei > d_ei_max)
				d_ei = d_ei_max;
			if (d_ei < d_ei_min)
				d_ei = d_ei_min;

			Vdr += (Kpd * d_e + Kid * d_ei + Kdd * d_de);
			Vdl += (Kpd * d_e + Kid * d_ei + Kdd * d_de);

			  //medju_stanje();
			  //faza = 0;
			  //teta_ei = 0;
			  //d_ei = 0;

		}

		acc = 0.5;

		if (fabs(teta_e) < M_PI/20 && fabs(d_e) < d_e_min)
			acc = 1;


		if (fabs(teta_e) < teta_min)
			{
			  //medju_stanje();
			  faza = 3;
			  //teta_ei = 0;
			  //d_ei = 0;
			}
		else
			faza = 2;

		//prosledi_pwm(Vdr, Vdl, Vr, Vl);

		}


	if (fabs(Vdr) > 50) {
		if (Vdr < 0) {
			Vdr = -50;
		} else if (Vdr > 0) {
			Vdr = 50;
		}
	}
	if (fabs(Vdl) > 100) {
		if (Vdl < 0) {
			Vdl = -50;
		} else if (Vdl > 0) {
			Vdl = 50;
		}
	}

	if (Vl < Vdl)
		Vl += acc;
	if (Vl > Vdl)
		Vl -= acc;
	if (Vr > Vdr)
		Vr -= acc;
	if (Vr < Vdr)
		Vr += acc;



	if (Vl < 0) {
		okretanje_m2(fabs(Vl));
		motor2_smer(nazad);
	} else if (Vl > 0) { // smer 1
		okretanje_m2(fabs(Vl));
		motor2_smer(napred);
	}
	if (Vr < 0) { //smer 2
		okretanje_m1(fabs(Vr));
		motor1_smer(nazad);
	} else if (Vr > 0) { //smer 1
		okretanje_m1(fabs(Vr));
		motor1_smer(napred);
	}

}


