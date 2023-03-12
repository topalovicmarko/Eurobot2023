/*
 * timer.c
 *
 *  Created on: Feb 27, 2023
 *      Author: Marko Topalovic
 */

#include "timer.h"
#include "stm32f405xx.h"
#include <stdint.h>

//Brojanje sekundi
//1s
//95s
//100s

// Novi tipovi
typedef struct Time_flags
{
	uint8_t f1s : 1;
	uint8_t f95s : 1;
	uint8_t f100s : 1;
	uint8_t f_time_out_start : 1;
	uint8_t f_time_out : 1;
}TTime_flags;

//Promenljive
static TTime_flags t_flag = {0, 0, 0, 0, 0};
static volatile uint32_t sys_time = 0;
static volatile uint32_t time_out = 0;

//Prototip privatne funkcije
static void tim13_init(void);

void timer_init()
{
	tim13_init();

	NVIC->ISER[1] |= (0b01 << 12);
}

void tim13_init(void)
{
	RCC->APB1ENR |= (0b1 << 7);	// Dozvola tajmer perferije

	TIM13->CR1 &= ~(0b01 << 1);		// UDIS - Update disable
	TIM13->CR1 |= (0b01 << 2);		// URS - Generisanje tajmera (Underflow, Overflow)

	TIM13->EGR |= (0b01 << 0);		// UG - Update generation
	TIM13->PSC = 84 -1 ;				// Prescaler - deljitelj frekv. -1 zbog forule (1Mhz dobijamo)
	TIM13->ARR = 1000 - 1;			// -> 1s   Brojač broji od 0 zato ide -1

	TIM13->DIER |= (1 << 0);

	TIM13->CR1 |= (0b01 << 0);		// CEN - Dozvola tajmera tek na kraju da bi mogao da broji sa već podešenim vrednostima

	while(!(TIM13->SR & (0b1 << 0)))
		{
			__NOP();
		}
}

uint8_t isTimeFlag95s()
{
	return t_flag.f95s;
}

uint8_t isTimeFlag100s()
{
	return t_flag.f100s;
}

uint32_t getSysTime()
{
	return sys_time;
}

void setTimeOut(uint32_t delay)
{
	if (time_out == 0 && t_flag.f_time_out_start == 0)
	{
		time_out = delay;
		t_flag.f_time_out_start = 1;
	}
}

uint8_t isTimeOut()
{
	return t_flag.f_time_out;
}

void TIM8_UP_TIM13_IRQHandler(void)
{
	//Šta želimo da se izvršava u prekidu
	if (TIM13->SR & (0b01 << 0))
	{
		TIM13->SR &= ~(0b01 << 0);

		//Kod za izvršavanje 1ms
		sys_time++; // svake ms inkrementiramo prom

		if((sys_time % 1000) == 0)
		{
			t_flag.f1s = 1;
		}

		if((sys_time % 95000) == 0)
		{
			t_flag.f95s = 1;
		}

		if((sys_time % 100000) == 0)
		{
			t_flag.f100s = 1;
		}

		if (t_flag.f_time_out_start && (time_out != 0))
		{
			time_out--;
			t_flag.f_time_out = 0;
		}
		else if (t_flag.f_time_out_start && (time_out == 0))
		{
			t_flag.f_time_out = 1;
			t_flag.f_time_out_start = 0;
		}
	}
}
