#include "commonstuff.h"
#include "secado_horizontal.h"
#include <avr/io.h>
#include <avr/interrupt.h>

/*Cosas que faltan:


-Poner el sistema para bajar las banderas de encendido que para eso necesito contar tiempo
-Poner un sistema para cuando el coche va para atras accidentalmente una vez fuera del lavado
-Utilizar PWM para el motro M5 que va muy demasiado rapido
*/

extern bool SH;
extern status_t M5_state;
extern direccion_t M5_dir;

extern miliseconds_t miliseconds;
extern miliseconds_t milisecondsFinal_SH;
extern bool SH_ready;
extern bool SH_up_final;
extern miliseconds_t antireb_SH;
extern char ready;

void setup_SH_PORTS()
{
	cli();
	
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
	

	//TCCR5A=0b00100011;
	//TCCR5B=0b00011001;
	
	TCCR5A = 0x23;
	TCCR5B = 0x19;
	
	OCR5A = 4000;
	OCR5B = 0;

	sei();
	
}

void secado_horizontal_ISR()							// PCINT puerto B
{
	//if ((miliseconds-antireb_SH)>SENSOR_DELAY)
	//{
		if(SH==1)
		{																//Bandera que indica si el secado esta ativo
			if(SO7_f && SO9_f)									//Sensores S07 y S09 sin detectar nada
			{		
				if(SO8_f)
				{ 							//Sensor S08 sin detectar nada
					M5_state = ON;
					M5_dir = IZQUIERDA;
					milisecondsFinal_SH=miliseconds;
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
	//}
	antireb_SH = miliseconds;
}

void secado_horizontal_CP()
{
	
	if((M5_state==ON&&M5_dir==IZQUIERDA)&&(milisecondsFinal_SH+3000<miliseconds)){
		M5_state=OFF;
		SH=0;
	}
	motor(M5,M5_state,M5_dir);
	/*
	if(SH_up_final == 0)                                                    //Bandera de que se esta subiendo a la posicion final
	{
		if((PINK & (1 << 7)) == (1 << 7))									//Esto no funciona porque creemos que el SW2 no funciona
		{
			motor(M5,M5_state,M5_dir);
		}else
		{
			M5_state = OFF;
			SH_up_final = 1;
			milisecondsFinal_SH = miliseconds;
			motor(M5,ON,DERECHA);
		}
	}else
	{
		if(milisecondsFinal_SH + 1500 < miliseconds)
		{
			SH_up_final = 0;
			SH = 0;
			motor(M5,OFF,DERECHA);
		}
	}*/	
}



void gestionSH(mode_t modo)
{
    switch (modo)
	{
		case STARTING:
			if(!(ready & (1 << DRYER_MOD) == (1 << DRYER_MOD)))
			{
				if(SH_up_final == 0)
				{
					if((PINK & (1<<7)) == (1<<7))
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
					if(milisecondsFinal_SH + 1500 < miliseconds)
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
