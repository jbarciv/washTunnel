/* ----------------------------------------------------------------------------
 * Control del Hardware: Motor
 * 
 * -------------------------------------------------------------------------- */

#include "control.h"

void Motor(motor_t motor, motor_status_t estado, direccion_t giro)
{
    // creamos variables generales para el puerto del motor y su pin tanto para
    // el enable (EN), como la direccion (DI).
    char enPort, diPort, enPin, diPin; 
    switch (motor)
    {
        case M1: 
            enPort = M1ENPORT;
            enPin = M1ENPIN;
            diPort = M1DIPORT;
            diPin = M1DIPIN;
            break;
        case M2: 
            enPort = M2ENPORT;
            enPin = M2ENPIN;
            diPort = M2DIPORT;
            diPin = M2DIPIN;
            break;
        case M3: 
            enPort = M3ENPORT;
            enPin = M3ENPIN;
            diPort = M3DIPORT;
            diPin = M3DIPIN;
            break;
        case M4: 
            enPort = M4ENPORT;
            enPin = M4ENPIN;
            diPort = M4DIPORT;
            diPin = M4DIPIN;
            break;
        case M5: 
            enPort = M5ENPORT;
            enPin = M5ENPIN;
            diPort = M5DIPORT;
            diPin = M5DIPIN;
            break;
        case M6: 
            enPort = M6ENPORT;
            enPin = M6ENPIN;
            diPort = M6DIPORT;
            diPin = M6DIPIN;
            break;
    }

    if(estado == ENCENDIDO)
    {   
        if (giro == DERECHA) // primero establecemos la direccion (1=drcha. 0=izqda.)
        {
            diPort |= (1 << diPin);
        } 
        else
        {
            diPort &= (0 << diPin);
        }
        enPort |= (1 << enPin); // despues encendemos el motor
    } 
    else
    {
        enPort &= (0 << enPin);
    }
}
