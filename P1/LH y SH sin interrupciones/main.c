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

seconds_t half_second;

bool LH=0;
bool LH_ready = 0;
bool LH_up_final = 0;

bool SH=0;
bool SH_ready = 0;
bool SH_up_final = 0;

miliseconds_t  miliseconds = 0;
miliseconds_t  milisecondsFinal_LH = 0;
miliseconds_t  milisecondsFinal_SH = 0;

char ready=0x00;
 


int main(void)
{   
    setup_LH_PORTS();
	setup_SH_PORTS();
	timerSetup();
	
    while(1)
    {
		//gestionSH(STARTING);
		//gestionLH(STARTING);
		lavado_horizontal();
		secado_horizontal();
    }
}