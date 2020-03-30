//Librairies
#include <avr/io.h> 
#include <util/delay.h>
#include <avr/interrupt.h>

//Constantes machine
#define F_CPU 8000000UL

//Constantes d'entree
#define PORT_ENTREE 0x00
#define PORT_SORTIE 0xFF

//Constantes de couleurs
#define ROUGE   0b01
#define VERT    0b10
#define ETEINT  0b00

//Enums possibles
enum couleur{
  rouge = ROUGE,
  vert = VERT,
  ambre,
  eteint = ETEINT;
};
enum Etat{
  initial=0,
  push1=1,
  off1=2,
  push2=3,
  off2=4,
  push3=5, 

};
struct Port{
  char lettrePort;    //A,B,C, ou D
  uint8_t lignePort;  //0 a 3
  bool portImpair;    // si port est 1,3,5,7
  //Port = lettrePort $ 2*lignePort + portImpair
};


//Variables volatiles
volatile Etat etat = initial; // selon le nom de votre variable
volatile bool appuye = false; // placer le bon type de signal d'interruption à prendre en charge en argument

//Ports Utilises
Port del = {'D',3,false}; //D7

//Prototypes
void initialisation ( void );
void allumerDEL(Port port, couleur couleurDEL);
void resetSortieLigne(char port, uint8_t ligne);




//Initiation
void initialisation () 
{
  cli (); //Coupe l'acces aux interruptions
  DDRA = PORT_SORTIE;             // PORT A est en mode sortie
  DDRB = PORT_SORTIE;             // PORT B est en mode sortie
  DDRC = PORT_SORTIE;             // PORT C est en mode sortie
  DDRD = PORT_SORTIE - (1 << 2);  // PORT D est en mode sortie, sauf D3 (D.2)
  // cette procédure ajuste le registre EIMSK de l’ATmega324PA pour permettre les interruptions externes
  EIMSK |= (1 << INT0) ;
  // il faut sensibiliser les interruptions externes aux
  // changements de niveau du bouton-poussoir
  // en ajustant le registre EICRA
  EICRA |= (1 << ISC00) ;
  EICRA |= (0 << ISC01) ;
  sei ();
}


//Interruptions
ISR (INT0_vect) 
{
  // laisser un delai avant de confirmer la réponse du bouton-poussoir: environ 30 ms (anti-rebond)
  _delay_ms ( 30 );
  // se souvenir ici si le bouton est pressé ou relâché
  appuye = !appuye;
  

  // changements d'états
  if(etat == 5)
  {
     etat = initial;
  }
  else
  {
    int newetat = etat+ 1 ;
    etat = (Etat)newetat;
  }
  EIFR |= (1 << INTF0) ;

}

//Fonctions d'ecriture
void resetSortieLigne(char port, uint8_t ligne)
{
  switch (port)
  {
    case 'A':
      PORTA &= (0 << (2*ligne));
      PORTA &= (0 << (2*ligne)+1);
      break;
    case 'B':
      PORTB &= (0 << (2*ligne));
      PORTB &= (0 << (2*ligne)+1);
      break;
    case 'C':
      PORTC &= (0 << (2*ligne));
      PORTC &= (0 << (2*ligne)+1);
      break;
    case 'D':
      PORTD &= (0 << (2*ligne));
      PORTD &= (0 << (2*ligne)+1);
      break;
    default:
      break;
  }
}

void allumerDEL(Port port, couleur couleurDEL)
{
  resetSortieLigne(port.lettrePort, port.lignePort);

  if (couleurDEL != ambre)
  {
    switch (port.lettrePort)
    {
      case 'A':
        PORTA |= (couleurDEL << (2*port.lignePort));
        break;
      case 'B':
        PORTB |= (couleurDEL << (2*port.lignePort));
        break;
      case 'C':
        PORTC |= (couleurDEL << (2*port.lignePort));
        break;
      case 'D':
        PORTD |= (couleurDEL << (2*port.lignePort));
        break;
      default:
        break;
    }
  }

  else
  {
    switch (port.lettrePort)
    {
      case 'A':
        PORTA |= (vert << (2*port.lignePort));
        _delay_ms(9);
        PORTA |= (rouge << (2*port.lignePort));
        _delay_ms(1);
        break;
      case 'B':
        PORTB |= (vert << (2*port.lignePort));
        _delay_ms(9);
        PORTB |= (rouge << (2*port.lignePort));
        _delay_ms(1);
        break;
      case 'C':
        PORTC |= (vert << (2*port.lignePort));
        _delay_ms(9);
        PORTC |= (rouge << (2*port.lignePort));
        _delay_ms(1);
        break;
      case 'D':
        PORTD |= (vert << (2*port.lignePort));
        _delay_ms(9);
        PORTD |= (rouge << (2*port.lignePort));
        _delay_ms(1);
        break;
    }
  
}





int main()
{
    initialisation();
    for(;;)
    {
      switch (etat)
      {
        case initial:
          allumerDEL(del, rouge);
          
          break;
        
        case push1:
          allumerDEL(del, ambre);
          break;

        case off1:
          allumerDEL(del, vert);
          break;

        case push2:
          allumerDEL(del, rouge);
          break;

        case off2:
          allumerDEL(del, eteint);
          break;

        case push3:
          allumerDEL(del, vert);
          break;
       }
    }
}
