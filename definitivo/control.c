/* ----------------------------------------------------------------------------
 * Control del Hardware: Motor
 * 
 * -------------------------------------------------------------------------- */

#include "control.h"

// extern variable_tiempo_antirrebotes_como_se_llame;

void Motor(motor_t motor, status_t estado, direccion_t giro)
{
    // creamos variables generales para el puerto del motor y su pin tanto para
    // el enable (EN), como la direccion (DI).
    char enPort, diPort, enPin, diPin; 
    switch (motor)
    {
        case M1: 
            enPort = M1ENPORT;
            enPin = M1ENpin;
            diPort = M1DIPORT;
            diPin = M1DIpin;
            break;
        case M2: 
            enPort = M2ENPORT;
            enPin = M2ENpin;
            diPort = M2DIPORT;
            diPin = M2DIpin;
            break;
        case M3: 
            enPort = M3ENPORT;
            enPin = M3ENpin;
            diPort = M3DIPORT;
            diPin = M3DIpin;
            break;
        case M4: 
            enPort = M4ENPORT;
            enPin = M4ENpin;
            diPort = M4DIPORT;
            diPin = M4DIpin;
            break;
        case M5: 
            enPort = M5ENPORT;
            enPin = M5ENpin;
            diPort = M5DIPORT;
            diPin = M5DIpin;
            break;
        case M6: 
            enPort = M6ENPORT;
            enPin = M6ENpin;
            diPort = M6DIPORT;
            diPin = M6DIpin;
            break;
    }

    if(estado == ON)
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

// estoy trabajando con los sensores por ahora no lo empleéis...
// ya os indicaré (si finalmente tiene sentido) cómo funcionan.
// algo tipo if(Sensor(SO4) == ON) ... Y Sensor() ya se encarga del antirrebotes y de devolverte ON o OFF...

status_t Sensor(sensor_t sensor)
{
    char s_PIN, s_pin; 
    switch (sensor)
    {
        case SO1: 
            s_PIN = SO1PIN;
            s_pin = SO1pin;
            break;
    }
    // en construcción... la intento llevar hecha para el mañana...
}