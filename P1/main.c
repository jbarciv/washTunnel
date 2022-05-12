/*
 * Prueba_lavado_horizontal.c
 *
 * Created: 04/05/2022 19:22:04
 * Author : Mario
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "commonstuff.h"
#include "lavado_horizontal.h"
#include "secado_horizontal.h"
#include "actuators.h"


 bool LH=0;
 status_t M4_state=OFF;
 status_t M3_state=OFF;
 direccion_t M3_dir;
 
 bool SH=0;
 status_t M5_state=OFF;
 direccion_t M5_dir;
 //seconds_t  seconds = 0;
 //miliseconds_t  miliseconds = 0;
 //seconds_t  secondsBack = 0;
 //seconds_t  secondsFinal = 0;
 //miliseconds_t  milisecondsFinal_LH = 0;
// miliseconds_t  milisecondsFinal_SH = 0;
 
// seconds_t  secondsFinal_LH = 0;

 


int main(void)
{   
    setup_LH_PORTS();
	setup_SH_PORTS();
	//timerSetup();
	
    while(1)
    {
		lavado_horizontal_CP();
		secado_horizontal_CP();
    }
}

ISR (PCINT2_vect)       // PCINT puerto k
{	
	lavado_horizontal_ISR();	
}

ISR (PCINT0_vect)       // PCINT puerto b
{	
	secado_horizontal_ISR();	
}