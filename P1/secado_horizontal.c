#include "commonstuff.h"
#include "secado_horizontal.h"
//variable global SH?
//Motor(motor_t motor, motor_status_t estado, direccion_t giro)
void secado_horizontal()
{
    if(SH==1)
    {
        if(SO7==1&&S09=1)
        {
            if(S08==1)
            {
               Motor(M5, ENCENDIDO, IZQUIERDA); 
            }else
            {
                Motor(M5, APAGADO, DERECHA);
            }
        }else
        {
            Motor(M5, ENCENDIDO, DERECHA);
        }
    }
}