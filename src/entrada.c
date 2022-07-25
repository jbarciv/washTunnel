/* ----------------------------------------------------------------------------
 *               CONTROL DE LA ENTRADA AL TUNEL DE LAVADO

 *  - INTERRUPCION  -> MICROINTERRUPTOR SW1 :    ISR(INT0_vect)
 *  - INTERRUPCION  -> SENSOR OPTICO SO1    :    ISR (INT1_vect)
 *  - FUNCION       -> barrera(barrier_status_t estado),
 *                  -> barrierControl(mode_t modo) 
 * 
 * DATE:    11/05/2022
 * AUTHOR:  Gonzalo Quiros Torres
 *          Josep Maria Barbera Civera
 * -------------------------------------------------------------------------- */

#include "entrada.h"
#include "actuators.h"
#include "cinta.h"

extern miliseconds_t miliseconds;
extern seconds_t half_second;
extern bool LV;
extern bool barrier;
extern bool cinta;
extern char ready;

static bool antiCollision = FALSE;
static bool carWaiting = FALSE;
bool barrierUp;
bool barrierDown;

miliseconds_t antireb_S01 = 0;
miliseconds_t antireb_SW1 = 0;
seconds_t secondsLV = 0;
seconds_t secondsLVOff;
seconds_t tPreviousCar = 0;

char barrierPulseCounter = 0;


/********************************************
MICROINTERRUPTOR SW1: contador pulsos barrera
- Activo por flanco de subida
********************************************/
ISR(INT0_vect) 
{   
    if ((miliseconds - antireb_SW1) > BOTON_DELAY) // antirrebotes del microinterruptor
    {   
		// se lleva la cuenta de los pulsos de SW1
        barrierPulseCounter++ ;
        antireb_SW1 = miliseconds;  // se captura el tiempo  para el antirrebotes
    }

    if (barrierPulseCounter == 4)   // cuando esto se cumple la barrera está levantada
    {   
		// se controla el estado de la barrera con una bandera
        barrierUp = TRUE;
		// capturamos el tiempo para el inicio del Lavado Vertical
		secondsLV = half_second; 
    }
    else 
    {
        barrierUp = FALSE;
    }
	
	if (barrierPulseCounter == 5)
	{
		// capturamos el tiempo para apagar el Lavado Vertical
		secondsLVOff = half_second;
	}

    if (SO2_f == FALSE)
    {
        barrierDown = TRUE;
		secondsLVOff = half_second;
		barrierPulseCounter = 0;
    }
}


/********************************************
SENSOR ÓPTICO SO1: detector llegada coche
- Activo por flanco de subida y bajada
********************************************/
ISR (INT1_vect)
{
	if (miliseconds - antireb_S01 > SENSOR_DELAY) // antirrebotes del sensor optico
	{
		if (SO1_f) // Acaba de dejar de detectar (flanco de subida)
		{
			carWaiting = FALSE;
			antiCollision = FALSE;
		}
		else if(!SO1_f) // Empieza a detectar (flanco de bajada)
		{
			carWaiting = TRUE;
			barrier = TRUE;
			if (barrierPulseCounter > 3) // si la barrera esta bajando
			{
				// y el coche intenta entrar de nuevo la barrera se para
				barrierStop();
				antiCollision = TRUE;
			}
		}
		antireb_S01 = miliseconds; // se captura el tiempo  para el antirrebotes
	}
}


/********************************************
Funcion "barrera()". Se encarga de subir y 
bajar la barrera bajo ciertas condiciones
internamente implementadas.
********************************************/
void barrera(barrier_status_t estado)
{
	switch (estado)
	{
		case UP:
			if (barrierPulseCounter < 4)
        	{
				barrierMove();
        	}
			else
			{
				barrierStop();
			}
			barrier = TRUE;
			break;

		case DOWN:
			if (barrierDown)
			{
				barrierStop();
				barrier = FALSE;
			}
			else
			{
				if (antiCollision == FALSE)
				{
					barrierMove();
					barrier = TRUE;
				}
				else
				{
					barrierStop();
				}
			}
			break;

		case WAIT:
			barrierStop();
			barrier = FALSE;
			break;

		default:
			break;
	}
    
    if(SO2_f)
	{
		barrierDown = FALSE;
	}
	else
	{
		barrierDown = TRUE;
		barrier = FALSE;
		barrierPulseCounter = 0;
	}
}

void barrierMove()
{
    motor(M1,ON,IZQUIERDA);
}

void barrierStop()
{
    motor(M1,OFF,IZQUIERDA);
}


/********************************************
Funcion "gestionBarrera()". Se gestiona 
cuando la barrera debe subir o bajar.
********************************************/
void gestionBarrera(mode_t modo)
{
    switch (modo)
	{
		case STARTING:
			if (carWaiting == FALSE && SO2_f == 1)
			{
				barrera(DOWN);
			}
			
			if (SO2_f == 0 || barrierDown == TRUE)
			{
				barrera(WAIT);
				ready |= (1 << ENTRY_MOD);
			}
			break;
		
		case EMERGENCY:
			barrera(WAIT);
			break;
		
		case BUSY:
			if (carWaiting == TRUE && LV == FALSE)
			{
				barrera(UP);
			}
			else 
			{
				SO1_f ? barrera(DOWN) : barrera(WAIT);
			}
			gestionCinta(BUSY);
			break;

		default:
			barrera(WAIT);
			break;			
	}
	
}