#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/interrupt.h>
#include "AfficheurSegment.cpp"




int main(){
    AfficheurSegment afficheur;
    for(;;)
    {
        for (uint8_t gauche = 0; gauche < 100; gauche++){
            for (uint8_t droite = 0; droite < 100; droite++)
            {
                afficheur.etablirValeurs(gauche,droite);
                _delay_ms(10);
            }           
        }
    }
}