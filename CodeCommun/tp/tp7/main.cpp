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

  #include "../../Lib/Debug.h"
 

int main(){
    
   a.initialisationUART();
   char c[100] = "Poly mtl ";
  
    
   for(;;){
  
    DEBUG_PRINT(c);
   } 
};
    
