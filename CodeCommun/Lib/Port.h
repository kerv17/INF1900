#include <avr/io.h> 
#include <util/delay.h>
#include <avr/interrupt.h>

#ifndef PORT_H
#define PORT_H

class Port
{
private:
    char lettrePort_;    //A,B,C, ou D
    uint8_t lignePort_;  //0 a 3
    bool portImpair_;    // si port est 1,3,5,7
  //Port = lettrePort $ 2*lignePort + portImpair
public:
    Port(char lettrePort, uint8_t lignePort, bool portImpair);
    ~Port();
    char getLettrePort();
    int getLignePort();
    bool getPortImpair();

    void resetSortieLigne();
};

#endif