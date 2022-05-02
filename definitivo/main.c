/* ----------------------------------------------------------------------------
 *                                 WASHTUNNEL
 * -------------------------------------------------------------------------- */

#include "commonstuff.h"

/********************* Variables globales ***********************************/
miliseconds_t   miliseconds = 0;
seconds_t       seconds = 0;
bool            SO1_f;          // Sensor SO1: estado real (filtrado)


void motorSetup()
{
    DDRL |= 0xFF;
    DDRD |= 0xF0;
}

void entradaSetup() // TIENE QUE REVISARSE (?)
{
    cli();                      // El SO1 es el DDRD1 y debe ir como entrada(0).
    PCICR |= (1<<PCIE1);        // Activamos las PCINT(15:8)
    CMSK1 |= (1<<PCINT8);       // Habilitamos la interrupcion
    sei();                      //Habilitamos las interrupciones globales
}

void timerSetup() // TIENE QUE REVISARSE (?)
{
    // setup del contador 3
    cli ();
    TCCR3B |= (1<<WGM32);           // Modo ctc
    TCCR3B |= (1<<CS31)|(1<<CS30);  // Preescalado clk/64 (periodo de 8 uS)
    OCR3A = ANTIREB_TIME;           // Contamos COUNTER_TIME periodos
    TIMSK3 |= (1<<OCIE3A);          // Habilitamos la interrupción por compare match
    // setup del contador 4
    TCCR3B |= (1<<WGM42);           // Modo ctc
    TCCR3B |= (1<<CS42);            // Preescalado clk/256 (periodo de 32 uS)
    OCR3A = REAL_TIME;              // Contamos REAL_TIME periodos (=1 S)
    TIMSK3 |= (1<<OCIE4A);          // Habilitamos la interrupción por compare match
    sei();
}


int main(void)
{   
    timerSetup();
    motorSetup();
    entradaSetup();
    
    while(1)
    {
    }
}