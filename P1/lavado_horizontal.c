#include "commonstuff.h"
#include "lavado_horizontal.h"
//variable global LH
//Motor(motor_t motor, status_t estado, direccion_t giro)
extern int LH;
extern int PINK0;

ISR (PCINT2_vect)       // PCINT puerto k
{
    
    if(LH==1){  //Bandera que indica si el lavado horizontal esta activo
        if(((PINK0&0x20)==0x20)&&((PINK&0x20)==0x00)&&((PINK&0x1C)==0x1C)){ 
            //Se comprueba si ha habido flaNco de bajada en S06 y si S03,S04 y S05 no detectan nada, el coche esta saliendo
            LH=0;
            motor(M4,OFF,DERECHA);
        }else{
            if((PINK&0X14)==0X14){  //Se comprueba si S03 y S05 estan detectando algo
                if((PINK&0X08)==0X08){  //Se comprueba si S04 esta detectando algo
                    motor(M3,ON,IZQUIERDA);
                }else{
                    motor(M3,OFF,IZQUIERDA);
                }
            }else{
                motor(M3,ON,DERECHA);
            }
        }
    }else{
        if((PINK&0x0C)==0x0C){  //Se comprueba si S03 Y S04 estan detectando algo--> el caso raro
            if(((PINK0&0x20)==0x20)&&((PINK&0x20)==0x00)&&((PINK&0x1C)==0x1C)){ //Se comprueba si el coche que ha ido para atras ha salido
                motor(M3,ON,IZQUIERDA);
            }else{
                motor(M3,ON,DERECHA);   //El coche que ha ido para atras sigue bloqueando
            }
        }    
        else{
            LH=1;
            motor(M4,ON,DERECHA);//EL SENTIDO HAY Q MIRARLO
        }
    }
    PINK0=PINK;
}