#define F_CPU 8000000UL
#include "tmr2.h"

void tmr2::demarrerTimer()
{
    cli();
    uint8_t duration = 250;
    TCCR2A = 0x00;   // clear timer registers
    TCCR2B = 0x00;
    TIMSK2 = 0x00;

    TIMSK2 |= (1 << OCIE2B);    // OCRB interruption enableded
    TCCR2A |=  (1 << COM2B0);   // Normal mode & toogle on OC2B


	TCNT2 = 0; // initialise le timer a 0

    // OCR2A = 0;
	OCR2B = duration; // La valeur TOP jusque laquelle le TCNT2 doit compter

	TCCR2B = (1 << CS22) | (0 << CS21) | (1 << CS20); // divise l'horloge par 128 


	TIMSK2 |= (1 << OCIE2B); 	// On active ici le bit output compare interrupts enable B
                                // du time/counter interrupt mask register
    sei();
}								


