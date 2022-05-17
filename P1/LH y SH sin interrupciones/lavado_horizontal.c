#include "commonstuff.h"
#include "lavado_horizontal.h"
#include <avr/io.h>
#include <avr/interrupt.h>

/*Version sin interrupciones todo se gestiona por consulta periodica
*/

extern miliseconds_t miliseconds;
extern miliseconds_t milisecondsFinal_LH;
extern bool LH;
extern bool LH_up_final;
extern bool LH_ready;
extern char ready;

void setup_LH_PORTS()
{
	cli();
	
	DDRK&= ~(1 << SO3pin);
	DDRK&= ~(1 << SO4pin);
	DDRK&= ~(1 << SO5pin);
	
	DDRK &= ~(1 << 6);
	
	DDRD|=(1<<M3ENpin);
	DDRD|=(1<<M3DIpin);
	DDRL|=(1<<M4ENpin);
	PINK_prev=PINK;
	sei();
}

void lavado_horizontal()
{
	/*Gestion de subida de bandera y perfilado dle coche*/

	if(LH == 1)
	{															//Bandera que indica si el lavado horizontal esta activo
			if(SO3_f && SO5_f)
		{														//Se comprueba si S03 y S05 estan detectando algo
			if(SO4_f)											//Se comprueba si S04 esta detectando algo
			{													
				motor(M3,ON,IZQUIERDA);
			}else
			{
				motor(M3,OFF,IZQUIERDA);
			}
		}else{
			motor(M3,ON,DERECHA);
		}
	}else{
		if(!SO3_f && (LH_up_final == 0))						//Se activa la bandera de LH si SO3_f esta a cero y no estamos en la subida a posicion de reposo(LH_up_final)	
		{
			LH = 1;
			motor(M3,ON,DERECHA);
			motor(M4,ON,DERECHA);
		}
	}

	/*Gestion de bajada de bandera*/

	if(LH_up_final == 0)                                         //Bandera de que se esta subiendo a la posicion final
	{
		if(!(PINK & (1 << 7)) == (1 << 7))					//En cuanto se activa SW2 se baja la bandera LH y comienza la subida a posicion de reposo(LH_up_final)						
		{
			LH = 0;
			LH_up_final = 1;
			milisecondsFinal_LH = miliseconds;
			motor(M4,OFF,DERECHA);
			motor(M3,ON,DERECHA);
		}
	}else
	{
		if(milisecondsFinal_LH + 2500 < miliseconds)
		{
			LH_up_final = 0;
			motor(M5,OFF,DERECHA);
		}
	}
}

void gestionLH(mode_t modo)
{
    switch (modo)
	{
		case STARTING:
			motor(M4,OFF,DERECHA);
			if(LH_ready == 0)
			{
				if(LH_up_final == 0)                                                    //Bandera de que se esta subiendo a la posicion final
				{
					if((PINK & (1 << 6)) == (1 << 6))                               //Esto no funciona porque creemos que el SW2 no funciona
					{
						motor(M4,OFF,DERECHA);
						motor(M3,ON,M3,IZQUIERDA);
					}else
					{
						M3_state = OFF;
						M4_state = OFF;
						LH_up_final = 1;
						milisecondsFinal_LH = miliseconds;
						motor(M4,OFF,DERECHA);
						motor(M3,ON,DERECHA);
				}
				}else
				{
					if(milisecondsFinal_LH + 2500 < miliseconds)
					{
						LH_up_final = 0;
						LH_ready = 1;
						ready |= (1 << LH_MOD);
						motor(M3,OFF,DERECHA);
					}
				}
			}
			break;
		
		case EMERGENCY:
			motor(M3,OFF,DERECHA);
			motor(M4,OFF,DERECHA);
			break;
		
		case BUSY:
			lavado_horizontal()
			break;
		default:
			
			break;			
	}
}
