/*
 * ax.c
 *
 *  Created on: Apr 18, 2023
 *      Author: Marko Topalovic
 */

#include "ax.h"

void zatvaranje_zadnjh_vrata(void);
void otvaranje_zadnjh_vrata(void);
void loptice_pocetni_polozaj(void);
void prva_loptica(void);
void druga_loptica(void);
void treca_loptica(void);
void prednja_leva_vrata_otvorena(void);
void prednja_leva_vrata_zatvorena(void);
void sva_vrata_otvorena(void);
void hvatanje_kolaca(void);
void sva_vrata_zatvorena(void);
void prednja_desna_vrata_hvatanje(void);
void prednja_leva_vrata_hvatanje(void);
void prednja_desna_vrata_otvorena(void);
void prednja_desna_vrata_zatvorena(void);

uint8_t citanje[] = { 0xFF, 0xFF, 0x04, 0x04, 0x02, 0x24, 0x02, 0xCF };

void zatvaranje_zadnjh_vrata(void) {
	servo_control(4, 61);
	tajmer_delay_mikro(20);
	for (uint8_t i = 0; i < sizeof(citanje) / sizeof(*citanje); i++) {
		uart_send_byte6(citanje[i]);
	}
	if (get_ugao() >= 50 && get_ugao() <= 70) {
		//tajmer_delay(1000);
		__NOP();
	} else {
		servo_control(4, 61);
		tajmer_delay_mikro(20);
		//tajmer_delay(1000);
	}
}

void otvaranje_zadnjh_vrata(void) {
	servo_control(4, 151);
	tajmer_delay_mikro(20);
	for (uint8_t i = 0; i < sizeof(citanje) / sizeof(*citanje); i++) {
		uart_send_byte6(citanje[i]);
	}
	if (get_ugao() >= 140 && get_ugao() <= 160) {
		//tajmer_delay(1000);
		__NOP();
	} else {
		servo_control(4, 151);
		tajmer_delay_mikro(20);
		//tajmer_delay(1000);

	}
}

void loptice_pocetni_polozaj(void) {
	servo_control(5, 18);
	for (uint8_t i = 0; i < sizeof(citanje) / sizeof(*citanje); i++) {
		uart_send_byte6(citanje[i]);
	}
	if (get_ugao() >= 16 && get_ugao() <= 20) {
		__NOP();
	} else {
		servo_control(5, 18);
	}

}

void prva_loptica(void) {
	servo_control(5, 108);
	for (uint8_t i = 0; i < sizeof(citanje) / sizeof(*citanje); i++) {
		uart_send_byte6(citanje[i]);
	}
	if (get_ugao() >= 106 && get_ugao() <= 110) {
		__NOP();
	} else {
		servo_control(5, 108);

	}
}

void druga_loptica(void) {
	servo_control(5, 198);
	for (uint8_t i = 0; i < sizeof(citanje) / sizeof(*citanje); i++) {
		uart_send_byte6(citanje[i]);
	}
	if (get_ugao() >= 196 && get_ugao() <= 200) {
		__NOP();
	} else {
		servo_control(5, 198);
	}
}
void treca_loptica(void) {
	servo_control(5, 288);
	for (uint8_t i = 0; i < sizeof(citanje) / sizeof(*citanje); i++) {
		uart_send_byte6(citanje[i]);
	}
	if (get_ugao() >= 286 && get_ugao() <= 290) {
		__NOP();
	} else {
		servo_control(5, 288);
	}
}

void prednja_leva_vrata_otvorena(void) {
	servo_control(7, 33);
	for (uint8_t i = 0; i < sizeof(citanje) / sizeof(*citanje); i++) {
		uart_send_byte6(citanje[i]);
	}
	if (get_ugao() >= 25 && get_ugao() <= 35) {
		__NOP();
	} else {
		servo_control(7, 33);
	}
}

void prednja_leva_vrata_zatvorena(void) {
	servo_control(7, 150);
	for (uint8_t i = 0; i < sizeof(citanje) / sizeof(*citanje); i++) {
		uart_send_byte6(citanje[i]);
	}
	if (get_ugao() >= 145 && get_ugao() <= 155) {
		__NOP();
	} else {
		servo_control(7, 150);
	}
}

void prednja_leva_vrata_hvatanje(void) {
	servo_control(7, 87);
	for (uint8_t i = 0; i < sizeof(citanje) / sizeof(*citanje); i++) {
		uart_send_byte6(citanje[i]);
	}
	if (get_ugao() >= 82 && get_ugao() <= 92) {
		__NOP();
	} else {
		servo_control(7, 87);
	}

}

void prednja_desna_vrata_hvatanje(void) {
	servo_control(8, 90);
	for (uint8_t i = 0; i < sizeof(citanje) / sizeof(*citanje); i++) {
		uart_send_byte6(citanje[i]);
	}
	if (get_ugao() >= 85 && get_ugao() <= 95) {
		__NOP();
	} else {
		servo_control(8, 90);
	}

}

void prednja_desna_vrata_otvorena(void) {
	servo_control(8, 60);
	for (uint8_t i = 0; i < sizeof(citanje) / sizeof(*citanje); i++) {
		uart_send_byte6(citanje[i]);
	}
	if (get_ugao() >= 55 && get_ugao() <= 65) {
		__NOP();
	} else {
		servo_control(8, 60);
	}

}

void prednja_desna_vrata_zatvorena(void) {
	servo_control(8, 150);
	for (uint8_t i = 0; i < sizeof(citanje) / sizeof(*citanje); i++) {
		uart_send_byte6(citanje[i]);
	}
	if (get_ugao() >= 140 && get_ugao() <= 160) {
		__NOP();
	} else {
		servo_control(8, 150);
	}

}

void sva_vrata_otvorena(void) {
	prednja_desna_vrata_otvorena();
	prednja_leva_vrata_otvorena();
	otvaranje_zadnjh_vrata();
}

void hvatanje_kolaca(void) {
	prednja_desna_vrata_hvatanje();
	prednja_leva_vrata_hvatanje();
}

void otpustanje_kolaca(void) {
	prednja_desna_vrata_otvorena();
	prednja_leva_vrata_otvorena();
}

void sva_vrata_zatvorena(void) {
	prednja_leva_vrata_zatvorena();
	prednja_desna_vrata_zatvorena();
	zatvaranje_zadnjh_vrata();
}
