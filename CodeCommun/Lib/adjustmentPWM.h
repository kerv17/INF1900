#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <inttypes.h>
#include <util/delay_basic.h>

#ifndef PWM_H
#define PWM_H

class adjustmentPWM
{
private:
	/* data */
public:
	adjustmentPWM(/* args */){}
	~adjustmentPWM();
	void PWM (uint8_t duration);
};

#endif


