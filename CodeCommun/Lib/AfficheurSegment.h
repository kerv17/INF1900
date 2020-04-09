#include <avr/io.h> 
#include <util/delay.h>
#include <avr/interrupt.h>

#ifndef SEG7
#define SEG7

class AfficheurSegment
{
private:
    uint8_t valeursAffichees_[5];
    const uint8_t affichages[11];
public:
    AfficheurSegment();
    ~AfficheurSegment();
    void afficherValeurs();
    void afficherValeur(uint8_t position);
    void changerValeur(uint8_t position, uint8_t valeur);
    void etablirValeurs(uint8_t pourcentageGauche, uint8_t pourcentageDroite);
};

#endif