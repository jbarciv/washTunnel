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
	DDRD &= ~(1<<DDD0);			// El SW1 asignado al puerto PD0 es una entrada

	EIMSK |= (1<<INT1);			// Habilitamos la INT1
	EICRA |= (1<<ISC10);		// Configuración de la INT1 por flanco de subida y bajada
	
	EIMSK |= (1<<INT0);			// Habilitamos la INT0
	EICRA |= (3<<ISC00);		// Configuramos la INT0 por flanco de subida
}

void salidaSetup()
{
	DDRD &= ~(1<<DDD2);         // El SO10 asignado al puerto PD2 es una entrada
    DDRB &= ~(3<<DDB4);         // SO11 y SO12 asignados a PB4 y PB5 son entradas
    DDRB |= (3<<DDB6);          // L4 y L5 son salidas

    EIMSK |= (1<<INT2);
    EICRA |= (3<<ISC20);
}

void timerSetup()
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
    OCR4A = REAL_TIME;              // Contamos REAL_TIME periodos (=0.5 S)
    TIMSK4 |= (1<<OCIE4A);          // Habilitamos la interrupción por compare match
    sei();
}

void emergenciaSetup()
{
	DDRD &= ~(1<<DDD3);
	EIMSK |= (1<<INT3);			// Habilitamos la INT3
	EICRA |= (1<<ISC30);		// Configuración de la INT3 por flanco de subida y bajada
}

void LHSetup()
{
	
	DDRK&= ~(1 << SO3pin);
	DDRK&= ~(1 << SO4pin);
	DDRK&= ~(1 << SO5pin);
	
	DDRK &= ~(1 << 6);
	
	PCICR |=0x04;

	PCMSK2=0x00;
	PCMSK2 |=(1<<SO3pin);
	PCMSK2 |=(1<<SO4pin);
	PCMSK2 |=(1<<SO5pin);
	
	
	DDRD|=(1<<M3ENpin);
	DDRD|=(1<<M3DIpin);
	DDRL|=(1<<M4ENpin);
	
}

void SHSetup()
{
	DDRB &= ~(1 << SO7pin);
	DDRB &= ~(1 << SO8pin);
	DDRB &= ~(1 << SO9pin);
	
	DDRK &= ~(1 << 7);
	
	PCICR |= 0x01;
	
	PCMSK0=0X00;
	//PCMSK0=0x07;
	PCMSK0 |= (1 << SO7pin);
	PCMSK0 |= (1 << SO8pin);
	PCMSK0 |= (1 << SO9pin);
	
	DDRL |= (1 << M5ENpin);
	DDRL |= (1 << M5DIpin);
	
	//set PWM
	
	/*
	TCCR5A=0b00100011;
	TCCR5B=0b00011001;

	TCCR5A &= ~(1 << WGM51);
	TCCR5A &= ~(1 << WGM50);
	TCCR5B |= (1 << WGM52);
	TCCR5B &= ~(1 << WGM53);
	
	TCCR5A |= (1 << COM5A0);
	TCCR5A &= ~(1 << COM5A1);
	
	
	OCR5A = 60000;
	OCR5B = 0;
	*/
}