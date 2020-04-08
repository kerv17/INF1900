#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/interrupt.h>

class Sonar{
    public:
            uint16_t lireCapteur(uint16_t position);

};