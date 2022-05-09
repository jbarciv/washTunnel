#include "commonstuff.h"
#include "lavado_horizontal.h"
#include <avr/io.h>
#include <avr/interrupt.h>

/*Cosas que faltan:

-Poner el sistema para bajar las banderas de encendido que para eso necesito contar tiempo
-Poner un sistema para cuando el coche va para atras accidentalmente una vez fuera del lavado

*/

extern char LH;
extern char PINK_prev;
extern status_t M4_state;
extern status_t M3_state;
extern direccion_t M3_dir;

void setup_LH_PORTS()
{
	cli();
	
	DDRK &= ~(1 << SO3pin);
	DDRK &= ~(1 << SO4pin);
	DDRK &= ~(1 << SO5pin);
	DDRK &= ~(1 << SO6pin);
	
	PCICR |=0x04;
	
	//PCMSK2=0X3C;
	PCMSK2 |=(1<<SO3pin);
	PCMSK2 |=(1<<SO4pin);
	PCMSK2 |=(1<<SO5pin);
	PCMSK2 |=(1<<SO6pin);
	
	//DDRL=0xFF;
	DDRD |=(1<<M3ENpin);
	DDRD |=(1<<M3DIpin);
	DDRL |=(1<<M4ENpin);

	sei();
	
}

void lavado_horizontal_ISR()
{	   
    if(LH==1){																								//Bandera que indica si el lavado horizontal esta activo
        if(((PINK_prev&0x20)==0x00)&&((PINK&0x20)==0x20)&&((PINK&0x1C)==0x1C)){ 	//Esto se va a cambiar por una movida por tiempo 		//Se comprueba si ha habido flaNco de subida en S06 y si S03,S04 y S05 no detectan nada, el coche esta saliendo
            LH=0;
            //motor(M4,OFF,DERECHA);
			M4_state=OFF;
			M3_state=OFF;
        }else{
            if(((SO3PIN &=(1<<SO3pin))==(1<<SO3pin))&&((SO5PIN &=(1<<SO5pin))==(1<<SO5pin))){				//(PINK&0X14)==0X14												//Se comprueba si S03 y S05 estan detectando algo
                if((SO4PIN &=(1<<SO4pin))==(1<<SO4pin)){													//(PINK&0X08)==0X00//Se comprueba si S04 esta detectando algo
                    //motor(M3,OFF,IZQUIERDA);
					M3_state=OFF;
                }else{
                    //motor(M3,ON,IZQUIERDA);
					M3_state=ON;
					M3_dir=IZQUIERDA;
                }
            }else{
                //motor(M3,ON,DERECHA);
				M3_state=ON;
				M3_dir=DERECHA;
            }
        }
    }else{
		LH=1;
        //motor(M4,ON,IZQUIERDA);														//EL SENTIDO HAY Q MIRARLO
        M4_state=ON;
		//motor(M3,ON,DERECHA);
		M3_state=ON;
		M3_dir=DERECHA;			
    }
    PINK_prev=PINK;
}

void lavado_horizontal_CP()
{
	motor(M4,M4_state,DERECHA);
	motor(M3,M3_state,M3_dir);
}