#include "commonstuff.h"
#include "lavado_horizontal.h"
//variable global LH?
//Motor(motor_t motor, motor_status_t estado, direccion_t giro)
//fucion que realiza el control del lavado por consulta periodica, tiene que estar en el bucle del main

//variariable LH
ISR (PCINT2_vect)       // PCINT(23:16), puerto K
{
    if(LH==1){
        if(((PINK0&0x20)==0x20)&&((PINK&0x20)==0x00)and((PINK&0x1C)==0x1C)){
            LH=0;
            Motor(M4,OFF,DERECHA);
        }else if((PINK&0X14)==0X14){
            if((PINK&0X08)==0X08){
                Motor(M3,ON,IZQUIERDA);
            }else{
                Motor(M3,OFF,IZQUIERDA);
            }
        }else{
            Motor(M3,ON,DERECHA);
        }
    }else if((PINK&0x0C)==0x0C){
        Motor(M3,ON,DERECHA);
        else{
            LH=1;
            Motor(M4,ON,DERECHA);//EL SENTIDO HAY Q MIRARLO
        }
    }
    PINK0=PINK;
}