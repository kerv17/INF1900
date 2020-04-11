#define F_CPU 8000000UL
#include "tmr2.h"

void tmr2::demarrerTimer()
{
    cli();
    uint8_t duration = 250;
    TCCR2A = 0x00;   // clear timer registers
    TCCR2B = 0x00;
    TIMSK2 = 0x00;

    TIMSK2 |= (1 << OCIE2A);  // OCRA enableded
    TCCR2A |=  (1 << COM2A0);   // Normal mode & toogle on OC2A & OC2B


	TCNT2 = 0; // initialise le timer a 0

	OCR2A = duration; // La valeur TOP jusque laquelle le TCNT1 doit compter

	TCCR2B = (1 << CS22) | (0 << CS21) | (1 << CS20); // divise l'horloge par 128 


	TIMSK2 |= (1 << OCIE2A); 	// On active ici le bit output compare interrupts enable A
                                // du time/counter interrupt mask register
    sei();
}								



