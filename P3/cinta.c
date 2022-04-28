/*

Esta función es la encargada del movimeinto de la cinta
    La velocidad en la primera versión será constante
    El control será de tipo todo-nada, sin PWM

En futuras versiones:
    Se podrá implementar un control PWM
    La velocidad podrá varir dependiendo de la situación de los vehículos dentro del tunel

*/

#include <commonstuff.h>
#include <control.h>

void gestionCinta (status_belt_t modo)
{
    switch (modo)
    {
        case NORMAL_OP:
            numberOfCars ? moveCinta() : stopCinta();
            break;
        
        case TEMP_SHUTDOWN:
            stopCinta();

    }

}

void moveCinta()
{
    Motor(M6,ON,DERECHA);
}

void stopCinta()
{
    Motor(M6,OFF,DERECHA);
}