/* ----------------------------------------------------------------------------
 * aquí se definen las funciones para el control
 * 
 * 
 * 
 * 
 * -------------------------------------------------------------------------- */


#include "control.h"

int Motor(motor_t motor, motor_status_t estado, direccion_t direccion)
{
    switch (motor)
    {
        case M1:
            if(estado == ENCENDIDO)
            {
                if (direccion == DERECHA) 
                {
                    PORTE = PORTE | 0x04;
                } 
                else PORTE = PORTE & 0xFB;
            } 
            else return 0;
            break;
        default:
            break;
    }
}