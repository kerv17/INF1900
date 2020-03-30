#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/interrupt.h>

#ifndef INITINTERRUPT_H
#define INITINTERRUPT_H

class InitInterrupt
{
private:
    /* data */
public:
    InitInterrupt(/* args */){}
    ~InitInterrupt();
    void initialization();
};

#endif

