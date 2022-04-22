/* ----------------------------------------------------------------------------
 * aquí se definen las funciones para el control
 * 
 * -------------------------------------------------------------------------- */

#include "control.h"

void Motor(motor_t motor, motor_status_t estado, direccion_t giro)
{
    switch (motor)
    {
        case M1:
            if(estado == ENCENDIDO)
            {   
                if (giro == DERECHA) 
                {
                    // establecer giro motor M1 a derechas;
                } 
                else
                {
                    // establecer giro motor M1 a izquierdas;
                }
                // encender motor M1 -> notar cómo primero se establece el sentido de giro deseado y luego ya se enciende;
            } 
            else
            {
                // apagar motor M1; algo estilo esto: M1ENPORT &= 0xFD;
            }
            break;
            
        // ... una vez definido bien el motor M1 -> replicar para resto de motores

        default: // ¿tiene sentido poner default? ¿qué pondrías... un mensaje de error?
        break;
    }
    }
    
}
