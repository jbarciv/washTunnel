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
#include "setup.h"

miliseconds_t  miliseconds = 0;

char PINK_prev;
bool LH = 0;
bool LH_up_final = 0;
status_t M4_state=OFF;
status_t M3_state=OFF;
direccion_t M3_dir;
miliseconds_t  milisecondsFinal_LH = 0;

bool SH=  0;
bool LH_up_final = 0;
status_t M5_state = OFF;
direccion_t M5_dir;
miliseconds_t  milisecondsFinal_SH = 0;

 


int main(void)
{   
    setup_LH_PORTS();
	setup_SH_PORTS();
	timerSetup();
	
    while(1)
    {
        //gestionSH(STARTING);
        //gestionLH(STARTING);
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