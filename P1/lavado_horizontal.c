#include "commonstuff.h"
#include "lavado_horizontal.h"
#include <avr/io.h>
#include <avr/interrupt.h>


extern bool LH;
//extern char PINK_prev;
extern status_t M4_state;
extern status_t M3_state;
extern direccion_t M3_dir;
//extern miliseconds_t miliseconds;
//extern miliseconds_t milisecondsFinal_LH;
//extern seconds_t seconds;
//extern seconds_t secondsFinal_LH;
//extern seconds_t secondsBack;

void setup_LH_PORTS()
{
	cli();
	
	DDRK&= ~(1 << SO3pin);
	DDRK&= ~(1 << SO4pin);
	DDRK&= ~(1 << SO5pin);
	DDRK&= ~(1 << SO6pin);
	
	PCICR |=0x04;
	
	//PCMSK2=0X3C;
	PCMSK2 |=(1<<SO3pin);
	PCMSK2 |=(1<<SO4pin);
	PCMSK2 |=(1<<SO5pin);
	//PCMSK2 |=(1<<SO6pin);
	
	//DDRL=0xFF;
	DDRD|=(1<<M3ENpin);
	DDRD|=(1<<M3DIpin);
	DDRL|=(1<<M4ENpin);

	sei();
	
}

void lavado_horizontal_ISR()
{
	if(LH==1){																			//Bandera que indica si el lavado horizontal esta activo
		if((PINK&0X14)==0X14){														//Se comprueba si S03 y S05 estan detectando algo
			if((PINK&0X08)==0X08){													//Se comprueba si S04 sin detectando algo
				//motor(M3,ON,IZQUIERDA);
				M3_state=ON;
				M3_dir=IZQUIERDA;
				//milisecondsFinal_LH=miliseconds;
				//secondsFinal_LH=seconds;
				
			}else{
				//motor(M3,OFF,IZQUIERDA);
				M3_state=OFF;
			}
		}else{
			//motor(M3,ON,DERECHA);
			M3_state=ON;
			M3_dir=DERECHA;
		}
	}else{
		LH=1;
		//motor(M4,ON,IZQUIERDA);														//EL SENTIDO HAY Q MIRARLO
		M4_state=ON;
		//motor(M3,ON,DERECHA);
		M3_state=ON;
		M3_dir=DERECHA;
	}
}

void lavado_horizontal_CP()
{
	/*
	if((M4_state==ON&&M3_state==ON&&M3_dir==IZQUIERDA)&&(secondsFinal_LH+1<seconds)){
		M4_state=OFF;
		M3_state=OFF;
		LH=0;
		
	}
	*/
	motor(M4,M4_state,DERECHA);
	motor(M3,M3_state,M3_dir);
}
