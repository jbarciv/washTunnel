#include "commonstuff.h"
#include "secado_horizontal.h"
//variable global SH?
//Motor(motor_t motor, status_t estado, direccion_t giro)
// es posible que este motor tenga que tener PWM

ISR (PCINT0_vect)       // PCINT puerto B
{
    if(SH==1){  //Bandera que indica si el secado esta ativo
        if((PINK&0x80)==0x80){  //Sensor de fin de carrera activo(SW3)
            SH=0;
            Motor(M5,OFF,DERECHA);
        }else{
            if((PINB&0x05)==0x05){ //Sensores S07 y S09 sin detectar nada
                if((PINB&0x02)==0x02){ //Sensores S08 sin detectar nada
                    Motor(M5,ON,IZQUIERDA);
                }else{
                    Motor(M5,OFF,IZQUIERDA);
                }
            }else{
                Motor(M5,ON,DERECHA);
            }
        }
    }else{
        if((PINB&0x03)){    //Se comprueba si S07 y S08 estan activos--> caso raro
            if((PINK&0x80)==0x80){ //Se comprueba si el secado ha subido hasta arriba
                Motor(M5,ON,IZQUIERDA);
            }else{
                Motor(M5,ON,DERECHA);   //El coche que ha ido para atras sigue bloqueando
            }
        } 
        else{
            SH=1;
        }
        
    }
    PINB0=PINB;
}