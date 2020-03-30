//Librairies
#include <avr/io.h> 
#include <util/delay.h>
#include <avr/interrupt.h>


//Constantes machine
#define F_CPU 8000000UL
#define PRESCALER 1024


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

struct Port
{
  char lettrePort;    //A,B,C, ou D
  uint8_t lignePort;  //0 a 3
  bool portImpair;    // si port est 1,3,5,7
  //Port = lettrePort $ 2*lignePort + portImpair
};

//Ports Utilises
Port del = {'D',3,false}; //D7

//Variables volatiles
volatile bool boutonAppuye      = false;
volatile bool minuterieExpiree  = false;
volatile bool minuterieDemaree  = false;

//Prototypes
void initiation();
void partirMinuterie (uint16_t duree);
void resetSortieLigne(char port, uint8_t ligne);
void allumerDEL(Port port, couleur couleurDEL)


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



//Interruptions machines
ISR (INT0_vect) {
  // laisser un delai avant de confirmer la réponse du bouton-poussoir: environ 30 ms (anti-rebond)
  _delay_ms ( 30 );
  if(!minuterieExpiree && minuterieDemaree)
  {
    boutonAppuye = true;
  }
  
  EIFR |= (1 << INTF0);
}


//Minuterie
void partirMinuterie ( uint16_t duree ) 
{
  minuterieExpiree = 0;

  uint16_t nbCyclesHorloge = duree * (F_CPU/PRESCALER) / 1000;
  TCNT1   = 0x0000;
  OCR1A   = nbCyclesHorloge;
  TCCR1A  = 0b10100001;
  TCCR1B |= (1<<CS12);
  TCCR1B |= (1<<CS10);
  TCCR1C  = 0;
  TIMSK1 |= 0b11000000;
}
ISR(TIMER1_COMPA_vect)
{
  minuterieExpiree = true;
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



//Main
int main()
{
    initialisation();
    _delay_ms(3000);
    allumerDEL(del, rouge);
    _delay_ms(10);
    allumerDEL(del, eteint);
    _delay_ms(10);
    partirMinuterie(1000);

    while (minuterieExpiree)
    {
      if (boutonAppuye) 
    {
      allumerDEL(del, vert);
    }
    }
    

    while (boutonAppuye)
    {
      allumerDEL(del, vert);
    }
    else
    {
      allumerDEL(del, rouge);
    }

    return 0;
}
