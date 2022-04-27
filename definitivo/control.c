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

// A continuación hay dos versiones, la comentada es la que llamaré versión Gonzalo
// La segunda creo que la ha hecho Chema, hay que escoger una de las dos
// Si se escoge la de Chema, hay que cambiar "diPort |= (0 << diPin);" por
// "diPort &= (0 << diPin);" porque hacer un OR con 0 es como no hacer nada, no fuerzas el cambio a 0

/*
        case M1:
            if(estado == ENCENDIDO)
            {   
                if (giro == DERECHA) 
                {
                    M1PORT &= (0<<M1DIPORT);
                } 
                else
                {
                    M1PORT |= (1<<M1DIPORT);
                }
                M1PORT |= (1<<M1ENPORT);
            } 
            else
            {
                M1PORT &= (0<<M1ENPORT);
            }
        break;

        case M2:
            if(estado == ENCENDIDO)
            {   
                if (giro == DERECHA) 
                {
                    M2PORT &= (0<<M2DIPORT);
                } 
                else
                {
                    M2PORT |= (1<<M2DIPORT);
                }
                M2PORT |= (1<<M2ENPORT);
            } 
            else
            {
                M2PORT &= (0<<M2ENPORT);
            }
        break;

        case M3:
            if(estado == ENCENDIDO)
            {   
                if (giro == DERECHA) 
                {
                    M3PORT &= (0<<M3DIPORT);
                } 
                else
                {
                    M3PORT |= (1<<M3DIPORT);
                }
                M3PORT |= (1<<M3ENPORT);
            } 
            else
            {
                M3PORT &= (0<<M3ENPORT);
            }
        break;

        case M4:
            if(estado == ENCENDIDO)
            {   
                if (giro == DERECHA) 
                {
                    M4PORT &= (0<<M4DIPORT);
                } 
                else
                {
                    M4PORT |= (1<<M4DIPORT);
                }
                M4PORT |= (1<<M4ENPORT);
            } 
            else
            {
                M4PORT &= (0<<M4ENPORT);
            }
        break;

        case M5:
            if(estado == ENCENDIDO)
            {   
                if (giro == DERECHA) 
                {
                    M5PORT &= (0<<M5DIPORT);
                } 
                else
                {
                    M5PORT |= (1<<M5DIPORT);
                }
                M5PORT |= (1<<M5ENPORT);
            } 
            else
            {
                M5PORT &= (0<<M5ENPORT);
            }
        break;

        case M6:
            if(estado == ENCENDIDO)
            {   
                if (giro == DERECHA) 
                {
                    M6PORT &= (0<<M6DIPORT);
                } 
                else
                {
                    M6PORT |= (1<<M6DIPORT);
                }
                M6PORT |= (1<<M6ENPORT);
            } 
            else
            {
                M6PORT &= (0<<M6ENPORT);
            }
        break;
            
        default:
            M1PORT &= (0 << M1ENPORT);
            M2PORT &= (0 << M2ENPORT);
            M3PORT &= (0 << M3ENPORT);
            M4PORT &= (0 << M4ENPORT);
            M5PORT &= (0 << M5ENPORT);
            M6PORT &= (0 << M6ENPORT);

        break;
    }
*/
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
            diPort |= (0 << diPin);
        }
        enPort |= (1 << enPin); // despues encendemos el motor
    } 
    else
    {
        enPort |= (0 << enPin);
    }
}
