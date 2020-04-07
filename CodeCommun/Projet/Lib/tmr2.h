#include <avr/io.h>
#include <avr/interrupt.h>

#ifndef TIMER2
#define TIMER2


void initialiserTmr2();
void demarerTmr2();
void arreterTmr2();
void getCompteurTmr2();
void resetCompteurTmr2();
void incrementerCompteurTmr2();

#endif