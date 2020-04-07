#include "AfficheurSegment.h"

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
    valeursAffichees_({0,0,0,0,0})
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
    PORTC = valeur;    
}