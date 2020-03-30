#include "del.h"
#include "Port.h"


DEL::DEL(Port port):
  portDEL_(port)
{
}

void DEL::allumerDEL(couleur couleurDEL){
  portDEL_.resetSortieLigne();
  if (couleurDEL != ambre)
  {
    switch (portDEL_.getLettrePort())
    {
      case 'A':
        PORTA |= (couleurDEL << (2*portDEL_.getLignePort()));
        break;
      case 'B':
        PORTB |= (couleurDEL << (2*portDEL_.getLignePort()));
        break;
      case 'C':
        PORTC |= (couleurDEL << (2*portDEL_.getLignePort()));
        break;
      case 'D':
        PORTD |= (couleurDEL << (2*portDEL_.getLignePort()));
        break;
      default:
        break;
    }
  }
  else
  {
    switch (portDEL_.getLettrePort()  )
    {
      case 'A':
        PORTA |= (vert << (2*portDEL_.getLignePort()));
        _delay_ms(9);
        PORTA |= (rouge << (2*portDEL_.getLignePort()));
        _delay_ms(1);
        break;
      case 'B':
        PORTB |= (vert << (2*portDEL_.getLignePort()));
        _delay_ms(9);
        PORTB |= (rouge << (2*portDEL_.getLignePort()));
        _delay_ms(1);
        break;
      case 'C':
        PORTC |= (vert << (2*portDEL_.getLignePort()));
        _delay_ms(9);
        PORTC |= (rouge << (2*portDEL_.getLignePort()));
        _delay_ms(1);
        break;
      case 'D':
        PORTD |= (vert << (2*portDEL_.getLignePort()));
        _delay_ms(9);
        PORTD |= (rouge << (2*portDEL_.getLignePort()));
        _delay_ms(1);
        break;
    }
  }
}