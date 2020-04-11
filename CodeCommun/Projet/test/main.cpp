#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/interrupt.h>
#include "../../Lib/adjustmentPWM.h"
#include "../../Lib/amber.h"
#include "../../Lib/can.h"
#include "../../Lib/InitInterrupt.h"
#include "../../Lib/memoire_24.h"
#include "../../Lib/startTimer.h"
#include "../../Lib/tmr2.h"
#include "../../Lib/AfficheurSegment.h"
#include "../../Lib/Debug.h"

 

int main(){
   DDRA = 0xFF;
   DDRB = 0xFF;
   DDRC = 0xFF;
   DDRD = 0xFF;
   AfficheurSegment afficheur; 
   demarerTmr2();
   afficheur.etablirValeurs(15,20);
   
    
   for(;;){
      
   } 
};
    
