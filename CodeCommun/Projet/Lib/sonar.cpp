#include "../../Lib/can.h"
#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/interrupt.h>

#include "../../Lib/adjustmentPWM.h"


// Not sure how to declare Port B0

// Send a pulse de 10us sur bo

 uint16_t lireCapteur(uint16_t position){
PORTB |= (1 << 0) ;
_delay_us(10); 
PORTB |= (0<<0);
_delay_us(8*F_CPU);
can can1;
uint16_t lecture = can1.lecture(position) & 0xFF;
return 8;
};




