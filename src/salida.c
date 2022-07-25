/* ----------------------------------------------------------------------------
 *               SALIDA DEL TUNEL DE LAVADO - DECLARACION DE FUNCIONES
 *  - carLeavingTunnel

 * DATE: 08/05/2022
 * AUTHOR:  Gonzalo Quiros Torres
 *          Josep Maria Barbera
 * -------------------------------------------------------------------------- */

#include "actuators.h"
#include "entrada.h"
#include "salida.h"
#include "cinta.h"

extern char ready;
extern bool SH;
extern seconds_t half_second;
extern miliseconds_t miliseconds;
miliseconds_t antireb_S10 = 0;

bool carLeaving = FALSE;
static bool prevState = TRUE;




//Rutina de interrupción SO10 (activa por flanco de bajada)
ISR(INT2_vect)
{
    if((miliseconds-antireb_S10) > SENSOR_DELAY && carLeaving == FALSE && SO11_f == 1)
    {
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
            if (SO12_f)  // No hay nada cortando el sensor. No está detectando nada
            {
                if (prevState)
                {   // No detecta nada
                    prevState = TRUE;   
                }    
                else if (!prevState)    // Esto es un flanco de subida. Antes detectaba y ahora no. 
                {
                    if (!SO11_f)    // Se produce un flanco de subida, pero sigue habiendo coche dentro => 
                    {               // => estan dando marcha atrás en la salida
                        prevState = TRUE;
                    }
                    else if (SO11_f)    // Esta es la buena, aquí el coche está saliendo de verdad
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
                prevState = FALSE;    
            }
			if (!SO11_f && !SO10_f )
			{
				semaforo(GREEN);
			}
            if (!SO10_f && !SO11_f && !SO12_f)
            {   // Si detecto
                carLeaving = TRUE;
            }   // Si hay un coche en el secado y otro en la salida...
            if (carLeaving && SH) // paramos la cinta para evitar choques
            {
                gestionCinta(WAITING);  
            }
            break;

        case EMERGENCY:
            semaforo(RED);
            break;
    }
}
