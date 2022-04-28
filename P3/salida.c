/*

En este archivo se van a gestionar las acciones a llevar a cabo a la
salida del tunel:

    Paro de la cinta si es necesario
    Consulta de SO10 (INT) y SO12 (consulta periódica)
    Actualización del número de vehículos en el tunel

*/

#include <commonstuff.h>
#include <control.h>
#include <entrada.h>

bool carLeaving = false;
bool flag = true;

//Rutina de interrupción SO10 (activa por flanco de bajada)
ISR(INT0_vect)
{
    if(antireb_S10 > DELAY_SENSOR && carLeaving = false && SO11pin == 0)
    {
        carLeaving = true;
        Semaforo(GREEN);
        leavingTunnel(); //No me gusta este nombre
        gestionCinta();
    }
}

//Consulta periódica de SO12
void carLeavingTunnel (status_t mode)
{
    switch (mode)
    {
        case STARTING:
            if (SO12pin && SO11pin && SO10pin)
            {
                Semaforo(RED);
                ready |= (1 << OUT_MOD);
            }
            else
            {
                Semaforo(GREEN);
                ready &= ~(1 << OUT_MOD);
            }
            break;

        case WAITING:
        case BUSY:
            if (SO12pin) // No hay nada cortando el sensor. No está detectando nada
            {
                if (flag)
                {
                    flag = true; // No detecta nada
                }
                else if (!flag) // Esto es un flanco de bajada. Antes detectaba y ahora no.
                {
                    if (!SO11pin) // Se produce un flanco de bajada, pero sigue habiendo coche dentro => estan dando marcha atrás en la salida, ojo cuidao
                    {
                        flag = true;
                    }
                    else if (SO11pin) // Esta es la buena, aquí el coche está saliendo de verdad
                    {
                        carLeaving = false;
                        Semaforo(RED);
                        flag = true;
                    }
                }
            }
            else if (!SO12pin)
            {
                flag = false;
            }

            if (carLeaving && secado) // Si hay un coche en el secado y otro en la salida, paramos la cinta para evitar choques
            {
                gestionCinta(WAITING);
            }
            break;

        case EMERGENCY:
            Semaforo(RED);
            break;
    }
    
}
