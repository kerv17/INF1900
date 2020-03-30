#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <inttypes.h>
#include <util/delay_basic.h>
#include "../Lib/adjustmentPWM.h"

void adjustmentPWM::PWM (uint8_t duration) 
{
	// mise à un des sorties OC1A et OC1B sur comparaison
	// réussie en mode PWM 8 bits, phase correcte
	// et valeur de TOP fixe à 0xFF (mode #1 de la table 17-6
	// page 177 de la description technique du ATmega324PA)

	TCNT1 = 0;	//Timer a 0

	OCR1A = duration;

	OCR1B = duration;

	// division d'horloge par 8 - implique une frequence de PWM fixe

	TCCR1A |= (1 << COM1A1) | (1 << COM1A0) | (1 << COM1B0) | (1 << WGM10);

	TCCR1B |= (1 << CS11); // Divise l'horloge par 8

	TCCR1C = 0;
}