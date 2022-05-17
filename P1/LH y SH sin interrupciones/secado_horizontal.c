#include "commonstuff.h"
#include "secado_horizontal.h"
#include <avr/io.h>
#include <avr/interrupt.h>

extern miliseconds_t miliseconds;
extern miliseconds_t milisecondsFinal_SH;
extern bool SH;
extern bool SH_ready;
extern bool SH_up_final;
extern char ready;

void setup_SH_PORTS()
{
	cli();
	
	DDRB &= ~(1 << SO7pin);
	DDRB &= ~(1 << SO8pin);
	DDRB &= ~(1 << SO9pin);
	
	DDRK &= ~(1 << 7);
	
	DDRL |= (1 << M5ENpin);
	DDRL |= (1 << M5DIpin);
	
	//set PWM
	
	TCCR5A = 0x23;
	TCCR5B = 0x19;
	
	OCR5A = 4000;
	OCR5B = 0;

	sei();
	
}

void secado_horizontal()					
{
	/*Gestion de subida de bandera y perfilado dle coche*/

	if(SH == 1)								//Bandera que indica si el secado esta ativo
	{										
		if(SO7_f && SO9_f)					//Sensores S07 y S09 sin detectar nada
		{		
			if(SO8_f)						//Sensor S08 sin detectar nada
			{ 							
				motor(M5,ON,IZQUIERDA);
			}else
			{
				motor(M5,OFF,IZQUIERDA);
			}
		}else
		{
			motor(M5,ON,DERECHA);
		}
	}else
	{
		if(!SO7_f && (SH_up_final == 0))		//Se activa la bandera de SH si SO7_f esta a cero y no estamos en la subia a posicion de reposo	(SH_up_final)
		{
			SH = 1;
			motor(M5,ON,DERECHA);
		}
	}	

	/*Gestion de bajada de bandera*/

	if(SH_up_final == 0)                                                    //Bandera de que se esta subiendo a la posicion de resposo(SH_up_final)
	{
		if(!(PINK & (1 << 7)) == (1 << 7))									//En cuanto se activa SW3 se baja la bandera SH y comienza la subida a posicion de reposo(SH_up_final)		
		{
			SH = 0;
			SH_up_final = 1;
			milisecondsFinal_SH = miliseconds;
			motor(M5,ON,DERECHA);
		}
	}else
	{
		if(milisecondsFinal_SH + 2500 < miliseconds)						//Se reaiza la subida durante 2500 ms
		{
			SH_up_final = 0;
			motor(M5,OFF,DERECHA);
		}
	}
}

void gestionSH(mode_t modo)
{
    switch (modo)
	{
		case STARTING:
			if(SH_ready == 0)
			{
				if(SH_up_final == 0)                                       //Bandera de que se esta subiendo a la posicion final
				{
					if((PINK & (1 << 7)) == (1 << 7))                               
					{
						motor(M5,ON,IZQUIERDA);
					}else
					{
						M5_state = OFF;
						SH_up_final = 1;
						milisecondsFinal_SH = miliseconds;
						motor(M5,ON,DERECHA);
				}
				}else
				{
					if(milisecondsFinal_SH + 2500 < miliseconds)			//Se reaiza la subida durante 2500 ms
					{
						SH_up_final = 0;
						SH_ready = 1;
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
			secado_horizontal();
			break;
		default:
			
			break;			
	}
}