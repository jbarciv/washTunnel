/* ----------------------------------------------------------------------------
 *               CONTROL DE LA CINTA - DECLARACION DE FUNCIONES
 *  - gestionCinta
 *  - moveCinta
 *  - stopCinta
 * 
 * DATE: 02/05/2022
 * AUTHOR: Gonzalo Quiros Torres
 * -------------------------------------------------------------------------- */

#include "cinta.h"
#include "actuators.h"

extern bool cinta;
extern char ready;

void gestionCinta (mode_t modo)
{
    switch (modo)
    {
        case STARTING:
            stopCinta();
            ready |= (1<<BELT_MOD);
            break;

        case WAITING:
        case BUSY:
            cinta ? moveCinta() : stopCinta();
            break;

        case EMERGENCY:
            stopCinta();
            break;
        
        default:
            stopCinta();
            break;
    }

}

void moveCinta()
{
    motor(M6,ON,DERECHA);
    cinta = TRUE;
}

void stopCinta()
{
    motor(M6,OFF,DERECHA);
    cinta = FALSE;
}