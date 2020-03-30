
//Écrit par Nicholas Legrand
#include <avr/io.h>
#include <util/delay.h>
#include "memoire_24.h"

#ifndef UART_H
#define UART_H
class uart
{
private:
    
public:
    uart(){}
 
    void initialisationUART ( void );
    void transmissionUART ( uint8_t donnee );
};
#endif



