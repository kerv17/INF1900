#include "Port.h"

Port::Port(char lettrePort, uint8_t lignePort, bool portImpair):
    lettrePort_(lettrePort),
    lignePort_(lignePort),
    portImpair_(portImpair)
{}
char Port::getLettrePort(){
    return lettrePort_;
}
int Port::getLignePort(){
    return lignePort_;
}
bool Port::getPortImpair(){
    return portImpair_;
}

void Port::resetSortieLigne()
{
  switch (getLettrePort())
  {
    case 'A':
      PORTA &= (0 << (2*getLignePort()));
      PORTA &= (0 << ((2*getLignePort())+1));
      break;
    case 'B':
      PORTB &= (0 << (2*getLignePort()));
      PORTB &= (0 << ((2*getLignePort())+1));
      break;
    case 'C':
      PORTC &= (0 << (2*getLignePort()));
      PORTC &= (0 << ((2*getLignePort())+1));
      break;
    case 'D':
      PORTD &= (0 << (2*getLignePort()));
      PORTD &= (0 << ((2*getLignePort())+1));
      break;
    default:
      break;
  }
}