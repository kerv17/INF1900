#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <stdio.h>
#include "../../Lib/customprocs.h"
#include "../../Lib/lcm_so1602dtr_m_fw.h"


/********************************* PRINCIPE DE FONCTIONNEMENTS DU CODE POUR LES CAPTEURS SONAR ********************************
 * 
 * Les broches qui receoivent les echo (PA0, PA1, PA2) sont mises en entrées. Ces broches sont reliées (au niveau hardware)
 * à PCINT0, PCINT1, PCINT2, VOIR FONCTIONNEMENT ATMEL. On lance le trigger, et ainsi la valeur sur les broches de l'echo passe 
 * directement à 1. Lorsque la valeur sur ces broches change de 0 à 1, alors il y'a une interruption. 
 * Dans cette interruption on lance le timer0. Lorsque la valeur sur ces broches passe de 1 à 0 (fin echo), alors il y'a une interruption.
 * Dans cette interruption on arrete le timer et on lis le temps écoulé
 * Ensuite on calcul la distance = TCNT0/58
******************************************************************************************************************************/

#define DEMO_DDR	DDRB // `Data Direction Register' AVR occup� par l'aff.
#define DEMO_PORT	PORTB // Port AVR occup� par l'afficheur

volatile double distance_gauche ;
char affichageGauche[5];
char affichageDevant[5];
char affichageDroite[5];
volatile double distance_devant;
volatile double distance_droite;

// The variable ‘pulse’ is used to store the count value from the TCNT register.
static volatile int pulse = 0;

// Ecran LCD
LCM ecranLCD(&DEMO_DDR, &DEMO_PORT);

// Fonction qui retourne le message à afficher en fonction de la distance
char* messageDistance(double distance)
{
    if (distance < 1.00)
    {
        return "DNGR";
    }
    else if ((distance >= 1.00) && (distance < 3.00))
    {
        return "ATTN";
    }
    else
    {
        return " OK ";  // 2 espaces sont rajoutés pour avoir un affichage uniforme
    }
}

void conversion(double a,char* b )
{
uint8_t decimale =(uint8_t(a*10)%10);
uint8_t entier = (uint8_t(a)%10);

b[0]='0'+entier;
b[1]='.';
b[2]='0'+decimale;


}

void initialization() 
{
    cli();		                            // cli est une routine qui bloque toutes les interruptions
    DDRB = 0xFF;                            // PORT B est en mode sortie
    DDRA = 0xF8;                            // PA0-PA2 en entrée le reste en sortie    
    DDRC = 0xFF;                            // PORT C en sortie

    /* 0b1111 0111 PD3(bouton poussoir)est en mode entree, PD4 et PD5(PWM), 
    PD7 et PD2(LED droite), PD0 et PD1(LED gauche) sont en sorties */
    DDRD = 0xf7;  

    EIMSK |= (1 << INT1) | (1 << INT0);                   // Activer les interruptions externes sur INT1
    EICRA |= (1 << ISC11) | (1 << ISC10) | (1 << ISC00);   // regler INT1 pour declencher au front montant uniquement et PCINT0 tous les fronts


    // Active les interruptions sur tout changement logique de PA0-PA2
    PCICR |= (1 << PCIE0);
    PCMSK0 |= (1 << PCINT0) | (1 << PCINT1) | (1 << PCINT2) ;
    sei();				                    // sei permet de recevoir à nouveau des interruptions.
}

ISR(PCINT0_vect)
{
    if((PINA & 0x01) /*|| (PINA & 0x02) || (PINA & 0x04)*/)
    {
        // Start The TIMER prescale by 1024
        TCCR0B |= (1 << CS00) | (1 << CS02);
        TCNT0 = 0;
    }
    else
    {
        // Stop the timer and save the number of ticks in "pulse"
        TCCR0B |= 0;
        pulse = TCNT0;
        TCNT0 = 0;
    }
    PCIFR |= (0 << PCIF0);
}

int main()
{   
    initialization();
    while(1)
    {
        // interruption autorisé que pour changement sur PINA0 (PCINT0)
        PCMSK0 |= (1 << PCINT0) | (0 << PCINT1) | (0 << PCINT2) ;
        PORTB |= (1 << PINB0) ;         // On trigger le sonar
        _delay_us(10);
        PORTB &= ~(1 << PINB0);
        while(PINA & 0x01)
        {
            /* On attends l'echo et donc que PINA0 passe à 0*/
        }
        distance_gauche = pulse/58;
        //itoa(distance_gauche, affichageGauche, 10);
        
        
        conversion(distance_gauche,affichageGauche);
       
        ecranLCD.write( affichageGauche, 0);
       
        ecranLCD[16] = messageDistance(distance_gauche);

        // PCMSK0 |= (0 << PCINT0) | (1 << PCINT1) | (0 << PCINT2) ;
        // PORTB |= (1 << PINB0) ;
        // _delay_us(10);
        // PORTB &= ~(1 << PINB0);
        // while(PINA & 0x02)
        // {       
        //     /* On attends */
        // }
        // distance_devant = pulse/58;
        // itoa(distance_devant, affichageDevant, 10);
        // ecranLCD.write(affichageDevant, 6);
        // ecranLCD[22] = (messageDistance(distance_devant));

        // PCMSK0 |= (0 << PCINT0) | (0 << PCINT1) | (1 << PCINT2) ;
        // PORTB |= (1 << PINB0) ;
        // _delay_us(10);
        // PORTB &= ~(1 << PINB0);
        // while(PINA & 0x04)
        // {
        //     /* On attends */
        // }
        // distance_droite = pulse/58;
        // itoa(distance_droite, affichageDroite, 10);
        // ecranLCD.write(affichageDroite, 12);
        // ecranLCD[28] = (messageDistance(distance_droite));

    }
    
    return 0;
}




