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
//extern seconds_t seconds;
//extern seconds_t secondsFinal;
extern miliseconds_t miliseconds;
extern miliseconds_t milisecondsFinal_SH;
//extern seconds_t secondsBack;

void setup_SH_PORTS()
{
	cli();
	
	DDRB &= ~(1 << SO7pin);
	DDRB &= ~(1 << SO8pin);
	DDRB &= ~(1 << SO9pin);
	
	PCICR |=0x01;
	
	//PCMSK0=0X00;
	PCMSK0=0x07;
	/*PCMSK0 |=(1<<SO7pin);
	PCMSK0 |=(1<<SO8pin);
	PCMSK0 |=(1<<SO9pin);*/
	
	DDRL |=(1<<M5ENpin);
	DDRL |=(1<<M5DIpin);
	
	//set PWM
	

	//TCCR5A=0b00100011;
	//TCCR5B=0b00011001;
	
	TCCR5A=0x23;
	TCCR5B=0x19;
	
	OCR5A=4000;
	OCR5B=0;

	sei();
	
}

void secado_horizontal_ISR()							// PCINT puerto B
{
	if(SH==1){																					//Bandera que indica si el secado esta ativo
		if(((PINB&0x05)==0x05)){		//				//Sensores S07 y S09 sin detectar nada
			if(((PINB&0x02)==0x02)	){ 											//			//Sensor S08 sin detectar nada
				//motor(M5,ON,IZQUIERDA);
				M5_state=ON;
				M5_dir=IZQUIERDA;
				//secondsFinal=seconds;
				milisecondsFinal_SH=miliseconds;
			}else{
				//motor(M5,OFF,IZQUIERDA)
				M5_state=OFF;
			}
		}else{
			//motor(M5,ON,DERECHA);
			M5_state=ON;
			M5_dir=DERECHA;
		}	
	}else{
		SH=1;
		M5_state=ON;
		M5_dir=DERECHA;
	}	
}

void secado_horizontal_CP()
{
	
	if((M5_state==ON&&M5_dir==IZQUIERDA)&&(milisecondsFinal_SH+2000<miliseconds)){
		M5_state=OFF;
		SH=0;
	}
	motor(M5,M5_state,M5_dir);
	
}
/*
extern bool SH_ready;
extern bool SH_up_final;
extern miliseconds_t milisecondsFinal_SH;
/*
void gestionSH(mode_t modo)
{
    switch (modo)
	{
		case STARTING:
			if(SH_ready==0){
				if(up_final==0){
					if((PINK&=(1<<7))==(1<<7)){
						motor(M5,ON,IZQUIERDA);
					}else{
						up_final=1;
						milisecondsFinal_SH=miliseconds;
						motor(M5,ON,DERECHA);
					}
				}else{
					if(milisecondsFinal_SH+2500<miliseconds){
						SH_up_final=0;
						SH_ready=1;
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
}*/
