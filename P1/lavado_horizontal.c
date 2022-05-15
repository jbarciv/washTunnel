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
//extern seconds_t seconds;
//extern seconds_t secondsFinal_LH;
//extern seconds_t secondsBack;

void setup_LH_PORTS()
{
	cli();
	
	DDRK&= ~(1 << SO3pin);
	DDRK&= ~(1 << SO4pin);
	DDRK&= ~(1 << SO5pin);
	//DDRK&= ~(1 << SO6pin);
	
	PCICR |=0x04;

	//PCMSK2=0X3C;
	PCMSK2=0x1C;
	//PCMSK2 |=(1<<SO3pin);
	//PCMSK2 |=(1<<SO4pin);
	//PCMSK2 |=(1<<SO5pin);
	//PCMSK2 |=(1<<SO6pin);
	
	//DDRL=0xFF;
	DDRD|=(1<<M3ENpin);
	DDRD|=(1<<M3DIpin);
	DDRL|=(1<<M4ENpin);
	PINK_prev=PINK;
	sei();
	
}

void lavado_horizontal_ISR()
{
	if((PINK_prev&0X1C)!=(PINK&0X1C)){
		if(LH==1){																			//Bandera que indica si el lavado horizontal esta activo
			if((PINK&0X14)==0X14){														//Se comprueba si S03 y S05 estan detectando algo
				if((PINK&0X08)==0X08){													//Se comprueba si S04 sin detectando algo
					//motor(M3,ON,IZQUIERDA);
					M3_state=ON;
					M3_dir=IZQUIERDA;
					milisecondsFinal_LH=miliseconds;
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
	PINK_prev=PINK;
}

void lavado_horizontal_CP()
{
	
	if((M4_state==ON&&M3_state==ON&&M3_dir==IZQUIERDA)&&(milisecondsFinal_LH+2300<miliseconds)){
		M4_state=OFF;
		M3_state=OFF;
		LH=0;
		
	}
	
	motor(M4,M4_state,DERECHA);
	motor(M3,M3_state,M3_dir);
}
/*
extern bool LH_ready;
extern bool LH_up_final;
extern miliseconds_t milisecondsFinal_LH;

void gestionLH(mode_t modo)
{
    switch (modo)
	{
		case STARTING:
			motor(M4,OFF,DERECHA);
			if(LH_ready==0){
				if(LH_up_final==0){
					if((PINK&=(1<<7))==(1<<7)){
						motor(M3,ON,IZQUIERDA);
					}else{
						LH_up_final=1;
						milisecondsFinal_LH=miliseconds;
						motor(M3,ON,DERECHA);
					}
				}else{
					if(milisecondsFinal_LH+2500<miliseconds){
						LH_up_final=0;
						LH_ready=1;
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
}*/
