#include <avr/io.h>
#include <avr/interrupt.h>

#include "tmr2.h"

volatile unsigned int compteurTmr2;
void initialiserTmr2(){
    
    
    //Prescaler = 256
    TCCR2 |= (1 << CS22) | (1 << CS21);
    //Inintialiser compteur
    TCNT2 = 0;
    

    compteurTmr2 = 0;

    sei();
    
}

void incrementerCompteurTmr2(){
    compteurTmr2++;
}

void getCompteurTmr2(){
    return getCompteurTmr2;
}

void resetCompteurTmr2(){
    compteurTmr2 = 0;
}

void demarerTmr2(){
    TIMSK |= (1 << TOIE2);
    resetCompteurTmr2();
}

void arreterTmr2(){
    TIMSK -= (1 << TOIE2);
}



ISR(TIMER2_OVF_vect){
    if (getCompteurTmr2() < 5)
    {
        incrementerCompteurTmr2();
    }
    else
    {
        resetCompteurTmr2();
    }
}