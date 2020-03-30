#include <avr/io.h> 
#define F_CPU 8000000
#include <util/delay.h>
#include <avr/interrupt.h>

const int MODE_SORTIE = 0xff;

void ajustementPWM (int pourcentage) {
    OCR1A = pourcentage;
    OCR1B = pourcentage;
    TCCR1A |= (1 << COM1A1) | (1 << COM1B1)| (1 << WGM10);
    TCCR1B |= (1 << CS11);
    TCCR1C = 0;
}

int main(){
    TCNT1 = 0;
    DDRD = MODE_SORTIE;
    ajustementPWM(255);
    _delay_ms(2000);
    ajustementPWM(191);
    _delay_ms(2000);
    ajustementPWM(127);
    _delay_ms(2000);
    ajustementPWM(64);
    _delay_ms(2000);
    ajustementPWM(0);

    return 0;
}
