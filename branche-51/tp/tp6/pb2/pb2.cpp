#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/interrupt.h>
#include "can.h"





enum Etat{
    bas,
    moyen,
    haut
};

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



void initialisation ( void ) {
  // cli est une routine qui bloque toutes les interruptions.
  // Il serait bien mauvais d'être interrompu alors que
  // le microcontroleur n'est pas prêt...
  cli ();

 
  // configurer et choisir les ports pour les entrées
  // et les sorties. DDRx... Initialisez bien vos variables

  // cette procédure ajuste le registre EIMSK
  // de l’ATmega324PA pour permettre les interruptions externes
  EIMSK |= (1 << INT0) ;
 


  // il faut sensibiliser les interruptions externes aux
  // changements de niveau du bouton-poussoir
  // en ajustant le registre EICRA
  EICRA |= (1 << ISC00) ;
  EICRA |= (0 << ISC01) ;

  // sei permet de recevoir à nouveau des interruptions.
  sei ();
}

volatile uint8_t compteur=0;
volatile bool eteindre = false;



int main()
{
  DDRA = 0x00; //  PORT A est en mode entrée
  DDRB = 0xff; // PORT B est en mode sortie
  DDRC = 0xff; // PORT C est en mode sortie
  DDRD = 0x00 ; // PORT D est en mode sortie
  
  initialisation();
  can can1;
  uint16_t valeur=0;
  Etat etat;
  for(;;)
  {
    valeur=can1.lecture(0) & 0xFF;
    if(valeur>200)
        etat =haut;
    else if (valeur > 100)
    {
        etat = moyen;
    }
    else
    {
      etat = bas;
    }
        
    
  
  switch (etat){
      case bas : 
        green();
        break;
      case moyen: 
        amber(1);
        break;
      case haut  : 
        red();
        break;
    }
  
  valeur=0;
  
  }
}