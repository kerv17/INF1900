#include <avr/io.h> 
#include <util/delay.h>


//Etat present| Appuye | Etat suivant | Sortie        |
// initial    |   False| initial      | Rouge         |
// initial    |    True| push1        | Ambre         |
// push1      |  False | off1         | Verte         |
// push1      |  True  | push1        | Ambre         |
// off1       |  False | off1         | Verte         |
// off1       |  True  | push2        | Rouge         |
// push2      |  False | off2         | Aucune lumiere|            
// push2      |  True  | push2        | Rouge         |
// off2       |  False | off2         | Aucune lumiere|
// off2       |  True  | push3        |  green        |
// push3      |   False| initial      | red           |
// push3      |    True| push3        | green         |

  




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
    for(;;)
    {
      switch (state)
      {
        case initial:
          red();
          if (PIND & 0x04)
          {
            state = push1;
          }
          _delay_ms(10);
          break;
        
        case push1:
          amber(1);
          if (!(PIND & 0x04))
          {
            state = off1;
          }
          
          break;

        case off1:
          green();
          if (PIND & 0x04)
          {
            state = push2;
          }
          _delay_ms(10);
          break;

        case push2:
          red();
          if (!(PIND & 0x04))
          {
            state = off2;
          }
          _delay_ms(10);
          break;

        case off2:
          off();
          if (PIND & 0x04)
          {
            state = push3;
          }
          _delay_ms(10);
          break;

        case push3:
          green();
          if (!(PIND & 0x04))
          {
            state = initial;
          }
          
          
          break;
       }
    }
}
