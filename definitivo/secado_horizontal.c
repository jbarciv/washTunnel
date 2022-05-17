/* ----------------------------------------------------------------------------
 *                       CONTROL DEL LAVADO HORIZONTAL
 * 
 * DATE:    12/05/2022
 * AUTHOR:  Mario Gómez Pozo
 *          Juan Galvañ Hernando
 * -------------------------------------------------------------------------- */

#include "secado_horizontal.h"


extern bool SH;
extern status_t M5_state;
extern direccion_t M5_dir;

extern miliseconds_t miliseconds;
extern miliseconds_t milisecondsFinal_SH;
extern bool SH_ready;
extern bool SH_up_final;
extern miliseconds_t antireb_SH;
extern char ready;


void secado_horizontal_ISR()			// PCINT puerto B
{
	if(SH==1)
	{									//Bandera que indica si el secado esta ativo
		if(SO7_f && SO9_f)				//Sensores S07 y S09 sin detectar nada
		{
			if(SO8_f)
			{ 							//Sensor S08 sin detectar nada
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
	if((M5_state==ON&&M5_dir==IZQUIERDA)&&(milisecondsFinal_SH+2000<miliseconds)){
		M5_state=OFF;
		SH=0;
	}
	motor(M5,M5_state,M5_dir);
	*/
	if(SH_up_final == 0)                           //Bandera de que se esta subiendo a la posicion final
	{
		if((PINK & (1 << 7)) == (1 << 7))			//Esto no funciona porque creemos que el SW2 no funciona
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
		if(milisecondsFinal_SH + 2500 < miliseconds)
		{
			M5_state = OFF;
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
		if(SH_ready == 0)
		{
			if(SH_up_final == 0)                              //Bandera de que se esta subiendo a la posicion final
			{
				if((PINK & (1 << 7)) == (1 << 7))             //Esto no funciona porque creemos que el SW2 no funciona
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
				if(milisecondsFinal_SH + 2500 < miliseconds)
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
		secado_horizontal_CP();
		break;
		default:
		
		break;
	}
}
