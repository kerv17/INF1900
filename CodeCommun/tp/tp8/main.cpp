  #include <avr/io.h>
  #define F_CPU 8000000UL
  #include <util/delay.h>
  #include <avr/interrupt.h>
  #include "../../Lib/Debug.h"
  #include "../../Lib/uart.h"

enum etat{
  initial,
  push1,
  off1,
  push2,
  off2,
  push3,
};


bool init()
{
bool appuye =false;
 while (PIND & 0x04)
 {
  appuye =true;  
 }
 if (appuye)
 {
     return true;
 }
  else  return false ;
}



void red()
{
  PORTC = 0xAA;
  PORTB = 0xAA;
  PORTA = 0xAA;
}

void green()
{

  PORTC = 0x55;
  PORTB = 0x55;
  PORTA = 0x55;
}

void off()
{

  PORTC = 0x00;
  PORTB = 0x00;
  PORTA = 0x00;
}

void amber(unsigned long s_count)
{
  for( long i =0; i < s_count; i++)
  {
  green();
  _delay_ms(9);
  red();
  _delay_ms(1);
  }
}

void blink(){
    amber(1);
    
    off();
}


int main()
{
    DDRA = 0xff; // PORT A est en mode sortie
    DDRB = 0xff; // PORT B est en mode sortie
    DDRC = 0xff; // PORT C est en mode sortie
    DDRD = 0b11111011; // PORT D est en mode entree
    etat state= initial;
  
     a.initialisationUART();
    for(;;)
    {
      switch (state)
      {
        case initial:
          red();
          if (PIND & 0x04)
          {
            state = push1;
            DEBUG_PRINT("push1 ");
          }
          _delay_ms(10);
          break;
        
        case push1:
          amber(1);
          if (!(PIND & 0x04))
          {
            state = off1;
            DEBUG_PRINT("off1 ");
          }
          
          break;

        case off1:
          green();
          if (PIND & 0x04)
          {
            state = push2;
             DEBUG_PRINT("push2 ");
          }
          _delay_ms(10);
          break;

        case push2:
          red();
          if (!(PIND & 0x04))
          {
            state = off2;
             DEBUG_PRINT("off2 ");
          }
          _delay_ms(10);
          break;

        case off2:
          off();
          if (PIND & 0x04)
          {
            state = push3;
             DEBUG_PRINT("push3 ");
          }
          _delay_ms(10);
          break;

        case push3:
          green();
          if (!(PIND & 0x04))
          {
            state = initial;
             DEBUG_PRINT("initial ");
          }
          
          
          break;
       }
       
    }
}
