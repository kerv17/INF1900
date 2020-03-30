#include <avr/io.h>
#include <util/delay.h>




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
  PORTD = 0xAA;
  PORTC = 0xAA;
  PORTB = 0xAA;
  PORTA = 0xAA;
}

void green()
{
  PORTD = 0x55;
  PORTC = 0x55;
  PORTB = 0x55;
  PORTA = 0x55;
}

void off()
{
  PORTD = 0x00;
  PORTC = 0x00;
  PORTB = 0x00;
  PORTA = 0x00;
}

void amber(uint8_t s_count)
{
  for(unsigned long int i =0; i < s_count*100; i++)
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

void _delay_varms(int n) {
 while(n--) {
  _delay_ms(1);
 }
}

int main()
{
    DDRA = 0xff; // PORT A est en mode sortie
    DDRB = 0xff; // PORT B est en mode sortie
    DDRC = 0xff; // PORT C est en mode sortie
    DDRD = 0b11111011; // PORT D est en mode entree
    int n=5000;
    
    for(;;)
    {
     
      if((init()))
      {
        while (true)
        {
          red();
          _delay_varms(n);
          off();
          _delay_ms(50);
          n-=5;
        if(n==0)
          n=100;
        }
      }
    }
}