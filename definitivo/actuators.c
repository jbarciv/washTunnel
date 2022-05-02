/* ----------------------------------------------------------------------------
 * Control del Hardware: Motor, Luz
 * 
 * -------------------------------------------------------------------------- */

#include "actuators.h"

/* USO DE MOTOR()
    motor  -> {M1, M2, M3, M4, M5, M6}
    estado -> {ON, OFF}                 
    giro   -> {DERECHA, IZQUIERDA}
ej. Motor(M1, ON, DERECHA);
*/
void Motor(motor_t motor, status_t estado, direccion_t giro)
{
    char enPort, diPort, enPin, diPin; 
    switch (motor)
    {
        case M1: 
            enPort = M1ENPORT;
            enPin  = M1ENpin;
            diPort = M1DIPORT;
            diPin  = M1DIpin;
            break;
        case M2: 
            enPort = M2ENPORT;
            enPin  = M2ENpin;
            diPort = M2DIPORT;
            diPin  = M2DIpin;
            break;
        case M3: 
            enPort = M3ENPORT;
            enPin  = M3ENpin;
            diPort = M3DIPORT;
            diPin  = M3DIpin;
            break;
        case M4: 
            enPort = M4ENPORT;
            enPin  = M4ENpin;
            diPort = M4DIPORT;
            diPin  = M4DIpin;
            break;
        case M5: 
            enPort = M5ENPORT;
            enPin  = M5ENpin;
            diPort = M5DIPORT;
            diPin  = M5DIpin;
            break;
        case M6: 
            enPort = M6ENPORT;
            enPin  = M6ENpin;
            diPort = M6DIPORT;
            diPin  = M6DIpin;
            break;
    }

    if(estado == ON)
    {   
        if (giro == DERECHA)    // Establecemos la direccion (1=drcha. 0=izqda.)
        {
            diPort |= (1 << diPin);
        }
        else 
        {
            diPort &= ~(1 << diPin);
        }
        enPort |= (1 << enPin); // Despues encendemos el motor
    } 
    else
    {
        enPort &= ~(1 << enPin);
    }
}

/* USO DE LUZ()
    luz    -> {L1, L4, L5}
    estado -> {ON, OFF}                
ej. Luz(L1, ON);
*/
void Luz(luz_t luz, status_t estado)
{   
    char lPort, lPin;
    switch (luz)
    {
    case L1:
        lPort = L1PORT;
        lPin  = L1pin;
        break;
    case L4:
        lPort = L4PORT;
        lPin  = L4pin;
        break;
    case L5:
        lPort = L5PORT;
        lPin  = L5pin;
        break;
    }

    if(estado == ON)
    {
        lPort |= (1 << lPin);
    }
    else
    {
        lPort &| ~(1 << lPin);
    }
}


void Semaforo(status_luz_t color)
{
    if (color == GREEN)
    {
        Luz(L4,ON);
        Luz(L5,OFF);
    }
    else if (color == RED)
    {
        Luz(L5,ON);
        Luz(L4,OFF); 
    }
}