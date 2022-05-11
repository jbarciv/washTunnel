/*
 * GccApplication1.c
 *
 * Created: 10/05/2022 12:38:10
 * Author : ramos
 */ 
#include "commonstuff.h"
#include "luz.h"
#include "actuators.h"
#include <avr/io.h>
#include <avr/interrupt.h>
//#include "setup.h"
bool coche =0;
int i=0;
int halfsec;//=0;
ISR(TIMER4_COMPA_vect) 
{
    halfsec++;

    parpadeo(halfsec, coche);
}

void timerSetup_1()   // TIENE QUE REVISARSE (?)
{
    // setup del contador 3
    cli ();
    /*TCCR3B |= (1<<WGM32);           // Modo ctc
    TCCR3B |= (1<<CS31)|(1<<CS30);  // Preescalado clk/64 (periodo de 8 uS)
    OCR3A = ANTIREB_TIME;           // Contamos COUNTER_TIME periodos
    TIMSK3 |= (1<<OCIE3A); */         // Habilitamos la interrupción por compare match
    // setup del contador 4
    TCCR4B |= (1<<WGM42);           // Modo ctc
    TCCR4B |= (1<<CS42);            // Preescalado clk/256 (periodo de 32 uS)
    OCR4A = 15200;//REAL_TIME;              // Contamos REAL_TIME periodos (=1 S)
    TIMSK4 |= (1<<OCIE4A);          // Habilitamos la interrupción por compare match
    sei();
}

int main(void)
{
	timerSetup_1();
    /* Replace with your application code */
	halfsec = 0;
    while (1) 
    {
		i++;
		//halfsec++;
		
    }
}
