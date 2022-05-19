/* ----------------------------------------------------------------------------
 *                       CONTROL DEL LAVADO HORIZONTAL
 * 
 * DATE:    12/05/2022
 * AUTHOR:  Mario Gómez Pozo
 *          Juan Galvañ Hernando
 * -------------------------------------------------------------------------- */

#include "lavado_horizontal.h"
#include "actuators.h"

extern bool LH;
extern bool LH_ready;
extern bool LH_up_final;
extern char PINK_prev;
extern status_t M4_state;
extern status_t M3_state;
extern direccion_t M3_dir;
extern miliseconds_t miliseconds;
extern miliseconds_t milisecondsFinal_LH;

extern char ready;

ISR (PCINT2_vect)       // PCINT puerto k
{	
	lavado_horizontal_ISR();	
}

void lavado_horizontal_ISR()
{
	if(LH == 1)
	{															//Bandera que indica si el lavado horizontal esta activo
		if(SO3_f && SO5_f)
		{														//Se comprueba si S03 y S05 estan detectando algo
			if(SO4_f)											//Se comprueba si S04 sin detectando algo
			{													
				M3_state = ON;
				M3_dir = IZQUIERDA;
			}else
			{
				M3_state = OFF;
			}
		}else{
			M3_state = ON;
			M3_dir = DERECHA;
		}
	}else{
		LH=1;
		M4_state = ON;
		M3_state = ON;
		M3_dir = DERECHA;
	}
}

void lavado_horizontal_CP()
{
	if(LH_up_final == 0)                                                    //Bandera de que se esta subiendo a la posicion final
	{
		if((PINK & (1 << 6)) == (1 << 6))                               //Esto no funciona porque creemos que el SW2 no funciona
		{
			motor(M4,M4_state,DERECHA);
			motor(M3,M3_state,M3_dir);
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
			LH = 0;
			motor(M3,OFF,DERECHA);
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
						motor(M3,ON,IZQUIERDA);
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
			lavado_horizontal_CP();
			break;
		default:
			break;			
	}
}
