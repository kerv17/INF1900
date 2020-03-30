#include <avr/io.h> 
#include <util/delay.h>
#include <avr/interrupt.h>
#include "Port.h"

#ifndef DEL_H
#define DEL_H
//Constantes de couleurs
#define ROUGE   0b01
#define VERT    0b10
#define ETEINT  0b00

class DEL
{
private:
    Port portDEL_;
public:
    DEL(Port port);
    enum couleur{
        rouge = ROUGE,
        vert = VERT,
        ambre,
        eteint = ETEINT
    };
    
    void allumerDEL(couleur couleurDEL);
    
    
};
#endif