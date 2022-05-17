#include "commonstuff.h"
#include "lavado_horizontal.h"
#include <avr/io.h>
#include <avr/interrupt.h>


extern bool LH;
extern char PINK_prev;
extern status_t M4_state;
extern status_t M3_state;
extern direccion_t M3_dir;
extern miliseconds_t miliseconds;
extern miliseconds_t milisecondsFinal_LH;
extern bool LH_up_final;
extern bool LH_ready;
extern miliseconds_t antireb_LH;
extern char ready;

void setup_LH_PORTS()
{
	cli();
	
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
	PINK_prev=PINK;
	sei();
	
}

void lavado_horizontal_ISR()
{
	//if(miliseconds-antireb_LH>SENSOR_DELAY)
	//{
		if((PINK_prev & 0X1C) != (PINK & 0X1C))
		{
			if(LH == 1)
			{																			//Bandera que indica si el lavado horizontal esta activo
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
	//}
	PINK_prev = PINK;
	antireb_LH = miliseconds;
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
			if(!(ready & (1 << LH_MOD) == (1 << LH_MOD))){
				if(LH_up_final == 0){
					if((PINK & (1 << 6)) == (1 << 6)){
						motor(M3,ON,IZQUIERDA);
					}else{
						LH_up_final = 1;
						milisecondsFinal_LH = miliseconds;
						motor(M3,ON,DERECHA);
					}
				}else{
					if(milisecondsFinal_LH + 2500 < miliseconds){
						LH_up_final = 0;
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
