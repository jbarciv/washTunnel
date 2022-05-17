/*

En este archivo se van a gestionar las acciones a llevar a cabo a la
salida del tunel:

    Paro de la cinta si es necesario
    Consulta de SO10 (INT) y SO12 (consulta periódica)
    Actualización del número de vehículos en el tunel

*/

#include "actuators.h"
#include "entrada.h"
#include "salida.h"
#include "cinta.h"

extern char ready;
extern bool secado;
extern seconds_t half_second;
extern miliseconds_t miliseconds;

bool carLeaving = FALSE;
static bool prevState = TRUE;



miliseconds_t antireb_S10 = 0;


//Rutina de interrupción SO10 (activa por flanco de bajada)
ISR(INT2_vect)
{
    if((miliseconds-antireb_S10) > SENSOR_DELAY && carLeaving == FALSE && SO11_f == 1)
    {
        semaforo(GREEN);
        gestionCinta(BUSY);
    }
    antireb_S10 = miliseconds;
}

//Consulta periódica de SO12
void carLeavingTunnel (mode_t mode)
{
    switch (mode)
    {
        case STARTING:
            if (SO12_f && SO11_f && SO10_f)
            {
                semaforo(RED);
                ready |= (1 << OUT_MOD);
            }
            else
            {
                semaforo(GREEN);
                ready &= ~(1 << OUT_MOD);
            }
            break;

        case WAITING:
        case BUSY:
            if (SO12_f) // No hay nada cortando el sensor. No está detectando nada
            {
                if (prevState)
                {
                    prevState = TRUE; // No detecta nada
                }
                else if (!prevState) // Esto es un flanco de subida. Antes detectaba y ahora no.
                {
                    if (!SO11_f) // Se produce un flanco de subida, pero sigue habiendo coche dentro => estan dando marcha atrás en la salida, ojo cuidao
                    {
                        prevState = TRUE;
                    }
                    else if (SO11_f) // Esta es la buena, aquí el coche está saliendo de verdad
                    {
                        carLeaving = FALSE;
                        semaforo(RED);
                        gestionCinta(BUSY);
                        prevState = TRUE;
                    }
                }
            }
            else if (!SO12_f)
            {
                prevState = FALSE; //aqui detecto
            }

            if (!SO10_f && !SO11_f && !SO12_f)
            {
                carLeaving = TRUE;
            }
            
            if (carLeaving && secado) // Si hay un coche en el secado y otro en la salida, paramos la cinta para evitar choques
            {
                gestionCinta(WAITING);
            }
            
            break;

        case EMERGENCY:
            semaforo(RED);
            break;
    }
    
}
