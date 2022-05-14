/*
Esta version aun no esta probada puede dar fallos
*/

#include "commonstuff.h"
#include "lavado_horizontal.h"
#include "actuators.h"
#include <avr/io.h>
#include <avr/interrupt.h>


extern bool LH;
extern char PINK_prev;
extern bool LH_up_final;
extern status_t M4_state;
extern status_t M3_state;
extern direccion_t M3_dir;

extern miliseconds_t miliseconds;
extern miliseconds_t milisecondsFinal_LH;

extern char ready;


void setup_LH_PORTS()
{
	cli();
    /*Setup de los pines de los sensores y su respectiva PCint(PCint2)*/
	DDRK &= ~(1 << SO3pin);
	DDRK &= ~(1 << SO4pin);
	DDRK &= ~(1 << SO5pin);
	PCICR |= 0x04;
	PCMSK2 = 0x00;
	PCMSK2 |=(1 << SO3pin);
	PCMSK2 |=(1 << SO4pin);
	PCMSK2 |=(1 << SO5pin);
    /*Setup de los pines de los motores */
	DDRD |= (1 << M3ENpin);
	DDRD |= (1 << M3DIpin);
	DDRL |= (1 << M4ENpin);
    /*Variable auxiliar*/
	PINK_prev = PINK;
	sei();
	
}

void lavado_horizontal_ISR()
{
    /*
    El primer if se hace para evitar el problema ese rarisimo de q a veces los sensores del secado 
    activaban el lavado, funciona haciendo que se ejecute la rutina de interrupcion solo si ha habido
    algun cambio en los sensores SO3,SO4 o SO5. Para eso se usa la variable PINK_prev
    */
	if((PINK_prev & 0X1C) != (PINK & 0X1C))                       
    {
		if(LH == 1)
        {													//Bandera que indica si el lavado horizontal esta activo
			if(SO3_f && SO5_f)
            {										        //Se comprueba si S03 y S05 estan detectando algo
				if(SO4_f)
                {											//Se comprueba si S04 sin detectando algo
					M3_state = ON;
					M3_dir = IZQUIERDA;
					//milisecondsFinal_LH = miliseconds;
				}else
                {
					M3_state = OFF;
				}
			}else
            {
				M3_state = ON;
				M3_dir = DERECHA;
			}
		}else
        {
            if(SO6_f)                                       //El coche que ha salido ha ido un poco para atras
            {
                LH = 1;
			    M3_state = ON;
			    M3_dir = DERECHA;
            }else                                           //LLega un coche nuevo
            {
                LH = 1;
		    	M4_state = ON;
		    	M3_state = ON;
		    	M3_dir = DERECHA;
            }
			
		}	
	}
	PINK_prev = PINK;
}

void lavado_horizontal_CP()
{
    /*
    Esto es otra forma de bajar la bandera pero de momento esta descartada

	if((M3_state == ON && M3_dir == IZQUIERDA) && (milisecondsFinal_LH + 2300 < miliseconds)){
		M4_state = OFF;
		M3_state = OFF;
		LH = 0;
		
	}
    */
    /*
    La bajada de banderas se gestiona de manera analoga que el modo starting, si los motores tocan 
    el sensor de fin de carrera se entiende que ha acabado e secado y suben durante 2500 ms para quedarse 
    en la posicion adecuada para esperar al siguiente coche
    */
    if(LH_up_final == 0)                                                    //Bandera de que se esta subiendo a la posicion final
    {
		if(!((PINK &= (1 << 7)) == (1 << 7)))                               //Esto no funciona porque creemos que el SW2 no funciona
        {
            /*Mientras no se detecte nada en SW2 se hace caso a las banderas de la ISR*/
            motor(M4,M4_state,DERECHA);
	        motor(M3,M3_state,M3_dir);
		}else
        {
		    LH_up_final = 1;
			milisecondsFinal_LH = miliseconds;
			motor(M3,ON,DERECHA);
		}
	}else
    {
		if(milisecondsFinal_LH + 2500 < miliseconds)
        {
			LH_up_final = 0;
			motor(M3,OFF,DERECHA);
		}
	}
	
}

void gestionLH(mode_t modo)
{
    switch (modo)
	{
		case STARTING:
            /*
            Este modo hace que el motor baje hasta abajo y cuando toque el sensor SW2 
            suba durante 2500 ms y despues se para para quedarse en la posicion adecuada.
            De momento no funciona. Creemos que no funciona el SW2 hay q comprobarlo.
            */
			motor(M4,OFF,DERECHA);
			if((ready & (1 << LH_MOD))==(1 << LH_MOD))                  //Se comprueba si LH esta ready
            {
				if(LH_up_final == 0)                                    //Bandera de que se esta subiendo a la posicion final
                {
					if((PINK &= (1 << 7)) == (1 << 7))                  //Esto no funciona porque creemos que el SW2 no funciona
                    {
						motor(M3,ON,IZQUIERDA);
					}else
                    {
						LH_up_final = 1;
						milisecondsFinal_LH = miliseconds;
						motor(M3,ON,DERECHA);
					}
				}else
                {
					if(milisecondsFinal_LH + 2500 < miliseconds)
                    {
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
