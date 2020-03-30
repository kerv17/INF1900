#include <avr/io.h>
#include <util/delay.h>

//Etat present | Appuye | Etat suivant | Sortie        |
// INIT        |   False| Init         | Aucune lumiere|
// INIT        |    True| INIT1        | Aucune lumiere|
// INIT1       |  False | INIT1        | Aucune lumiere|
// INIT1       |  True  | INIT2        | Aucune lumiere|
// INIT2       |  False | INIT2        | Aucune lumiere|
// INIT2       |  True  | INIT3        | Aucune lumiere|
// INIT3       |  False | INIT3        | Aucune lumiere|
// INIT3       |  True  | INIT4        | Aucune lumiere|
// INIT4       |  False | INIT4        | Aucune lumiere|
// INIT4       |  True  | blink        | Aucune lumiere|
// Blink       |   X    | INIT         | Lumiere Ambre |      
  

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


int main()
{
    DDRA = 0xff; // PORT A est en mode sortie
    DDRB = 0xff; // PORT B est en mode sortie
    DDRC = 0xff; // PORT C est en mode sortie
    DDRD = 0b11111011; // PORT D est en mode entree
    
    for(;;)
    {
      //le for roule jusq'à temps que le bouton a été appuyé cinq fois
        for(uint8_t count = 0; count < 5; count++)
        {
            while (!(init()))
            {
            }
            _delay_ms(500);
            
        }
        blink();
    }
}
