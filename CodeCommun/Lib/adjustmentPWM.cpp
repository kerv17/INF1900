#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <inttypes.h>
#include <util/delay_basic.h>
#include "adjustmentPWM.h"


void adjustmentPWM::startMotor (uint8_t roueGauche, uint8_t roueDroite) volatile
{
	// mise à un des sorties OC1A et OC1B sur comparaison
	// réussie en mode PWM 8 bits, phase correcte
	// et valeur de TOP fixe à 0xFF (mode #1 de la table 17-6
	// page 177 de la description technique du ATmega324PA)

	TCNT1 = 0;	//Timer a 0

	OCR1A = roueDroite;	// PD5

	OCR1B = roueGauche;	// PD4

	// division d'horloge par 8 - implique une frequence de PWM fixe

	TCCR1A |= (1 << COM1A0) | (1 << COM1B0) | (1 << WGM10);

	TCCR1B |= (1 << CS11); // Divise l'horloge par 8

	TCCR1C = 0;
}