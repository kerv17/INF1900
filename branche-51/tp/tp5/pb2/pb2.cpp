#include <avr/io.h>
#include <util/delay.h>
#include "memoire_24.h"
#define F_CPU 8000000UL
#define BAUD 2400
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

void initialisationUART ( void ) {

// 2400 bauds. Nous vous donnons la valeur des deux

// premier registres pour vous éviter des complications

UBRR0H = 0;

UBRR0L = 0xCF;

// permettre la réception et la transmission par le UART0

UCSR0A |= (1<<RXC0) | (1<<TXC0);

UCSR0B = (1<<RXEN0)|(1<<TXEN0) ;

// Format des trames: 8 bits, 1 stop bits, none parity

UCSR0C = (1<<UCSZ01)|(1<<UCSZ00);

}
void transmissionUART ( uint8_t donnee ) {

/* Wait for empty transmit buffer */
while ( !( UCSR0A & (1<<UDRE0)) );
/* Put data into buffer, sends the data */
UDR0 = donnee;

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
    DDRA = 0xff; //  PORT A est en mode sortie
    DDRB = 0xff; // PORT B est en mode sortie
    DDRC = 0xff; // PORT C est en mode sortie
    DDRD = 0b11111011; // PORT D est en mode entree
    Memoire24CXXX memoire;
    initialisationUART();
  
    for(;;)
    {
        

        char mots[21] = "Le robot en INF1900\n";

        uint8_t i, j;

        for ( i = 0; i < 100; i++ ) {

            for ( j=0; j < 20; j++ ) {

                transmissionUART ( mots[j] );

        }

    }
       
      
    }
}