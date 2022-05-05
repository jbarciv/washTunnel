/* ----------------------------------------------------------------------------
 *                       SETUP - DECLARACIÓN DE FUNCIONES
 * -------------------------------------------------------------------------- */

#include "setup.h"


void motorSetup()
{
    DDRL |= 0xFF;
    DDRD |= 0xF0;
}

void entradaSetup()
{	
	DDRD &= ~(1<<DDD1);         // El SO1 asignado al puerto PD1 es una entrada
	DDRL |= (3<<DDL0);			// Activamos como salida M1en y M1dir
	DDRK &= ~(1<<DDK1);			// El SO2 asignado al puerto PK1 es una entrada
	DDRD |= (1<<DDD0);			// El SW1 asignado al puerto PD0 es una salida


	EIMSK |= (1<<INT1);			// Habilitamos la INT1
	EICRA |= (1<<ISC10);		// Configuración de la INT1 por flanco de subida y bajada
	
	EIMSK |= (1<<INT0);			// Habilitamos la INT0
	EICRA |= (3<<ISC00);		// Configuramos la INT0 por flanco de subida
}

void timerSetup()   // TIENE QUE REVISARSE (?)
{
    // setup del contador 3
    cli ();
    TCCR3B |= (1<<WGM32);           // Modo ctc
    TCCR3B |= (1<<CS31)|(1<<CS30);  // Preescalado clk/64 (periodo de 8 uS)
    OCR3A = ANTIREB_TIME;           // Contamos COUNTER_TIME periodos
    TIMSK3 |= (1<<OCIE3A);          // Habilitamos la interrupción por compare match
    // setup del contador 4
    TCCR4B |= (1<<WGM42);           // Modo ctc
    TCCR4B |= (1<<CS42);            // Preescalado clk/256 (periodo de 32 uS)
    OCR4A = REAL_TIME;              // Contamos REAL_TIME periodos (=1 S)
    TIMSK4 |= (1<<OCIE4A);          // Habilitamos la interrupción por compare match
    sei();
}