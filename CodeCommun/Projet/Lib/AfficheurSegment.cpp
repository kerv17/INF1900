#include "AfficheurSegment.h"
#include "tmr2.h"

AfficheurSegment::AfficheurSegment():
    affichages{
        0b01111110, //0
        0b00001100, //1
        0b10110110, //2
        0b10011110, //3
        0b11001100, //4
        0b11011010, //5
        0b11111010, //6
        0b00001110, //7
        0b11111110, //8
        0b11011110, //9
        0b10000000, //-
        },
    valeursAffichees_({0,0,10,0,0})
{
}
AfficheurSegment::~AfficheurSegment()
{
}

void AfficheurSegment::changerValeur(size_t position, uint8_t valeur){
    valeursAffichees_[position] =valeur;
}

void AfficheurSegment::afficherValeur(size_t position){
    uint8_t valeur = affichages[valeursAffichees_[position]];
    PORTA = (1 << 3+getCompteurTmr2());
    PORTC = valeur;
    
}

void AfficheurSegment::etablirValeurs(uint8_t pourcentageGauche, uint8_t pourcentageDroite){
    changerValeur(0,(pourcentageGauche/10));
    changerValeur(1,(pourcentageGauche%10));

    changerValeur(3,(pourcentageDroite/10));
    changerValeur(4,(pourcentageDroite%10));
}

