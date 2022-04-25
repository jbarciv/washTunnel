#include "commonstuff.h"
#include "lavado_horizontal.h"
//variable global LH?
//Motor(motor_t motor, motor_status_t estado, direccion_t giro)
//fucion que realiza el control del lavado por consulta periodica, tiene que estar en el bucle del main
void lavado_horizontal()
{
    if(LH==1)
    {
        if(SO3==1&&S05=1)
        {
            if(S04==1)
            {
               Motor(M3, ENCENDIDO, IZQUIERDA); 
            }else
            {
                Motor(M3, APAGADO, DERECHA);
            }
        }else
        {
            Motor(M3, ENCENDIDO, DERECHA);
        }
    }
}