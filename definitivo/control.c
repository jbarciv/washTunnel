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
}
