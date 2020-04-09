#define F_CPU 8000000UL
#include "tmr2.h"
volatile unsigned int compteurTmr2;
void initialiserTmr2(){
    
    
    //Prescaler = 256
    TCCR2B |= (1 << CS22) | (1 << CS21);
    //Inintialiser compteur
    TCNT2 = 0;
    

    compteurTmr2 = 0;

    sei();
    
}

void incrementerCompteurTmr2(){
    compteurTmr2++;
}

unsigned int getCompteurTmr2(){
    return compteurTmr2;
}

void resetCompteurTmr2(){
    compteurTmr2 = 0;
}

void demarerTmr2(){
    TIMSK2 |= (1 << TOIE2);
    resetCompteurTmr2();
}

void arreterTmr2(){
    TIMSK2 -= (1 << TOIE2);
}



ISR(TIMER2_COMPB_vect){
    if (getCompteurTmr2() < 5)
    {
        incrementerCompteurTmr2();
    }
    else
    {
        resetCompteurTmr2();
    }
    PORTA = (1 << (3+getCompteurTmr2() ) );
}