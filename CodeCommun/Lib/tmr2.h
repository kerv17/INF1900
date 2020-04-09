#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#define F_CPU 8000000UL

#ifndef TIMER2
#define TIMER2


void initialiserTmr2();
void demarerTmr2();
void arreterTmr2();
unsigned int getCompteurTmr2();
void resetCompteurTmr2();
void incrementerCompteurTmr2();

#endif