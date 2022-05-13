/*

Esta función es la encargada del movimeinto de la cinta
    La velocidad en la primera versión será constante
    El control será de tipo todo-nada, sin PWM

En futuras versiones:
    Se podrá implementar un control PWM
    La velocidad podrá varir dependiendo de la situación de los vehículos dentro del tunel

*/

#include "commonstuff.h"
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
            cinta ? moveCinta() : stopCinta(); //numberOfCars se actualiza en tunnelGotBusy()
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