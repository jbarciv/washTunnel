/*
Esta version aun no esta probada puede dar fallos
*/

#include "commonstuff.h"
#include "secado_horizontal.h"
#include "actuators.h"
#include <avr/io.h>
#include <avr/interrupt.h>

extern char ready;

extern bool SH;
extern bool SH_up_final;

extern status_t M5_state;
extern direccion_t M5_dir;

extern miliseconds_t miliseconds;
extern miliseconds_t milisecondsFinal_SH;

ISR (PCINT0_vect)       // PCINT puerto b
{
	secado_horizontal_ISR();
}

void setup_SH_PORTS()
{
	cli();
	/*Setup de los pines de los sensores y su respectiva PCint(PCint0)*/
	DDRB &= ~(1 << SO7pin);
	DDRB &= ~(1 << SO8pin);
	DDRB &= ~(1 << SO9pin);
	PCICR |= 0x01;	
	PCMSK0 = 0X00;
	PCMSK0 |= (1<<SO7pin);
	PCMSK0 |= (1<<SO8pin);
	PCMSK0 |= (1<<SO9pin);
	 /*Setup de los pines de los motores y PWM  */
	DDRL |= (1<<M5ENpin);
	DDRL |= (1<<M5DIpin);
	TCCR5A = 0x23;
	TCCR5B = 0x19;
	OCR5A = 4000;
	OCR5B = 0;
	sei();
}

void secado_horizontal_ISR()							// PCINT puerto B
{
	if(SH == 1)									//Bandera que indica si el secado esta ativo
    {											
		if(SO7_f && SO9_f)						//Sensores S07 y S09 sin detectar nada
        {					                    
			if(SO8_f)                           //Sensor S08 sin detectar nada
            { 					
				M5_state = ON;
				M5_dir = IZQUIERDA;
				//milisecondsFinal_SH = miliseconds;
			}else
            {
				M5_state = OFF;
			}
		}else
        {
			M5_state = ON;
			M5_dir = DERECHA;
		}	
	}else
    {
		SH = 1;
		M5_state = ON;
		M5_dir = DERECHA;
	}	
}

void secado_horizontal_CP()
{
	/*
    Esto es otra forma de bajar la bandera pero de momento esta descartada

	if((M5_state==ON&&M5_dir==IZQUIERDA)&&(milisecondsFinal_SH+2000<miliseconds)){
		M5_state=OFF;
		SH=0;
	}
    */
    /*
    La bajada de banderas se gestiona de manera analoga que el modo starting, si los motores tocan 
    el sensor de fin de carrera se entiende que ha acabado e secado y suben durante 2500 ms para quedarse 
    en la posicion adecuada para esperar al siguiente coche
    */
    if(SH_up_final == 0)                                                    //Bandera de que se esta subiendo a la posicion final
    {
		if(((PINK &= (1 << 6)) == (1 << 6)))                               
        {
            /*Mientras no se detecte nada en SW3 se hace caso a las banderas de la ISR*/
	        motor(M5,M5_state,M5_dir);
		}else
        {
		    SH_up_final = 1;
			milisecondsFinal_SH = miliseconds;
			motor(M5,ON,DERECHA);
		}
	}else
    {
		if(milisecondsFinal_SH + 2500 < miliseconds)
        {
			SH_up_final = 0;
			SH = 0;
			motor(M5,OFF,DERECHA);
		}
	}	
}



void gestionSH(mode_t modo)
{
    switch (modo)
	{
		case STARTING:
            /*
            Este modo hace que el motor baje hasta abajo y cuando toque el sensor SW3 
            suba durante 2500 ms y despues se para para quedarse en la posicion adecuada.
            */
			if((ready & (1 << DRYER_MOD))==(1 << DRYER_MOD))              //Se comprueba si SH esta ready
            {
				if(SH_up_final == 0)                                //Bandera de que se esta subiendo a la posicion final
                {
					if((PINK &= (1 << 6)) == (1 << 6))
                    {
						motor(M5,ON,IZQUIERDA);
					}else
                    {
						SH_up_final = 1;
						milisecondsFinal_SH = miliseconds;
						motor(M5,ON,DERECHA);
					}
				}else
                {
					if(milisecondsFinal_SH+2500<miliseconds)
                    {
						SH_up_final = 0;
						ready |= (1 << DRYER_MOD);							
						motor(M5,OFF,DERECHA);
					}
				}
			}
			break;
		
		case EMERGENCY:
			motor(M5,OFF,DERECHA);
			break;
		
		case BUSY:
			secado_horizontal_CP();
			break;
		default:
			break;			
	}
}
