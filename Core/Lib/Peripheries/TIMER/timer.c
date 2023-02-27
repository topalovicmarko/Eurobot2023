/*
 * timer.c
 *
 *  Created on: Feb 27, 2023
 *      Author: Marko Topalovic
 */

#include "timer.h"
#include "stm32f405xx.h"

static void tim2_init(void);
static void init_timer2_irq();

void timer_init()
{
	tim2_init();
}

void timer_irq_init()
{
	init_timer2_irq();
}

static void tim2_init(void)
{
	RCC->APB1ENR |= (1 << 0);	// Dozvola tajmer perferije
	TIM2->CR1 |= (1 << 0);		// CEN - Dozvola tajmera
	TIM2->CR1 |= (1 << 2);		// URS - Generisanje tajmera (Underflow, Overflow)
	TIM2->EGR |= (1 << 0);		// UG - Update generation
	TIM2->PSC = 84 -1 ;			// Prescaler - deljitelj frekv. -1 zbog forule (1Mhz dobijamo)
	TIM2->ARR = 1000 - 1;		// -> 1s

	while(!(TIM2->SR & (0b1<< 0)))
	{
		__NOP();
	}
}

static void init_timer2_irq()
{
	NVIC->ISER[0] |= (1 << 28);
}

void TIM2_IRQHandler()
{
	//Šta želimo da se izvršava u prekidu
}
