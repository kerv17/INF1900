#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/interrupt.h>
#include <inttypes.h>
#include <util/delay_basic.h>
#include "../../Lib/InitInterrupt.h"
#include "../LCD/customprocs.h"
#include "../LCD/lcm_so1602dtr_m_fw.h"
#include "../../Lib/adjustmentPWM.h"

void InitInterrupt::initialization() 
{
    cli();		                            // cli est une routine qui bloque toutes les interruptions
    DDRB = 0xff;                            // PORT B est en mode sortie

    /* 0b1111 0111 PD3(bouton poussoir)est en mode entree, PD4 et PD5(PWM), 
    PD7 et PD2(LED droite), PD0 et PD1(LED gauche) sont en sorties */
    DDRD = 0xf7;  

    EIMSK |= (1 << INT1);                   // Activer les interruptions externes sur INT1
    EICRA |= (1 << ISC11) | (1 << ISC10);   // regler INT1 pour declencher au front montant uniquement (appuie bouton)
    sei();				                    // sei permet de recevoir à nouveau des interruptions.
}

void manoeuvre1()
{
    // Affichage numéro manoeuvre sur LCD
    LCM ecranLCD();

    // manoeuvre
    adjustmentPWM pwm;
    pwm.startMotor((255*90)/100, (255*90)/100);  // 90% du TOP qui est 255 (uint8_t)
    for(uint8_t i = 90; i>=52; --i)
    {
        pwm.startMotor((255*i)/100, (255*90)/100);
        _delay_ms(100);
    }
    _delay_ms(1000);
    for(uint8_t i = 52; i<=90; i++)
    {
        pwm.startMotor((255*i)/100, (255*90)/100);
        _delay_ms(100);
    }
    _delay_ms(2000;)

    // Affichage vitesse roue sur 7 segments
}

void manoeuvre2()
{
    // Affichage numéro manoeuvre sur LCD

    // Début manoeuvre
    adjustmentPWM pwm;
    pwm.startMotor((255*90)/100, (255*90)/100);  // 90% du TOP qui est 255 (uint8_t)
    for(uint8_t i = 90; i>=52; --i)
    {
        pwm.startMotor((255*90)/100, (255*i)/100);
        _delay_ms(100);
    }
    _delay_ms(1000);
    for(uint8_t i = 52; i<=90; i++)
    {
        pwm.startMotor((255*90)/100, (255*i)/100);
        _delay_ms(100);
    }
    _delay_ms(2000;)

    // Affichage vitesse roue sur 7 segments
}

void manoeuvre3()
{
    // Affichage numéro manoeuvre sur LCD

    // Début manoeuvre

    // Affichage vitesse roue sur 7 segments
}

void manoeuvre4()
{
    // Affichage numéro manoeuvre sur LCD

    // Début manoeuvre

    // Affichage vitesse roue sur 7 segments
}

void manoeuvre5()
{
    // Affichage numéro manoeuvre sur LCD

    // Début manoeuvre

    // Affichage vitesse roue sur 7 segments
}

void manoeuvre6()
{
    // Affichage numéro manoeuvre sur LCD

    // Début manoeuvre

    // Affichage vitesse roue sur 7 segments
}

ISR(INT1_vect)
{
    // On choisis quelle combinaison Manoeuvre faire 
    if (/* manoeuvre 1 */)
    {
        manoeuvre1();
    }
    else if (/* manoeuvre 2 */)
    {
        manoeuvre2();
    }
    else if (/* manoeuvre 3 */)
    {
        manoeuvre3();
    }
    else if (/* manoeuvre 4 */)
    {
        manoeuvre4();
    }
    else if (/* manoeuvre 5 */)
    {
        manoeuvre5();
    }
    else if (/* manoeuvre 6 */)
    {
        manoeuvre6();
    }
    else 
    {
        // Affiche "combinaison non evaluer" sur le LCD pendant 2 secondes
        cp_wait_ms(2000);
    }
    EIFR |= (1 << INTF1); // Puttin th INTF1 bit at 0. so it clear the interruption flag
}

int main()
{
    InitInterrupt::initialization();
    return 0;
}

