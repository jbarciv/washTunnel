#include "commonstuff.h"
#include "secado_horizontal.h"
#include <avr/io.h>
#include <avr/interrupt.h>

//variable global SH?
//Motor(motor_t motor, status_t estado, direccion_t giro)
// es posible que este motor tenga que tener PWM

extern char SH;
extern status_t M5_state;
extern direccion_t M5_dir;



void setup_SH_PORTS()
{
	cli();
	
	DDRB |= (0 << SO7pin);
	DDRB |= (0 << SO8pin);
	DDRB |= (0 << SO9pin);
	
	PCICR |=0x01;
	
	PCMSK0=0X00;
	PCMSK0|=(1<<SO7pin);
	PCMSK0|=(1<<SO8pin);
	PCMSK0|=(1<<SO9pin);
	
	DDRL|=(1<<M5ENpin);
	DDRL|=(1<<M5DIpin);
	
	/*//set PWM
	TCCR5A |=  (0 << COM5B1) | (1 << COM5B0); //tougle oc5b on compare match
	TCCR5A |=  (0 << WGM50) | (0 << WGM51);   //normal mode 
	TCCR5B |=  (0 << WGM52) | (0 << WGM53);
	TCCR1B |=  (0 << CS52) | (0 << CS51) | ( 0 << CS50 ); 
	OCR5B=32768; //hay que verlo bien
	*/
	sei();
	
}

void secado_horizontal_ISR()							// PCINT puerto B
{
	if(SH==1){											//Bandera que indica si el secado esta ativo
		if((PINB&0x05)==0x05){							//Sensores S07 y S09 sin detectar nada
			if((PINB&0x02)==0x02){						//Sensores S08 sin detectar nada
				
				//motor(M5,ON,IZQUIERDA);
				M5_state=ON;
				M5_dir=IZQUIERDA;
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
	motor(M5,M5_state,M5_dir);
}