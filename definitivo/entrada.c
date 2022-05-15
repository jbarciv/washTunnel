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
extern seconds_t seconds;
extern char ready;
extern bool LV;
extern bool barrier; //Indica si la barrera está (1) o no está activa (0)
extern bool cinta;

static bool carWaiting = FALSE;

bool barrierUp;
bool barrierDown;
int barrierPulseCounter = 0;
seconds_t secondsLV = 0;
seconds_t secondsLVOff;

miliseconds_t antireb_S01 = 0;
miliseconds_t antireb_SW1 = 0;



/********************************************
MICROINTERRUPTOR SW1: contador pulsos barrera
- Activo por flanco de subida
********************************************/
ISR(INT0_vect) 
{   
    if ((miliseconds - antireb_SW1) > BOTON_DELAY) // antirebotes del microinterruptor
    {   // se lleva la cuenta de los pulsos; cuando llega a cinco se resetea
        (barrierPulseCounter == 5) ? (barrierPulseCounter = 0) : barrierPulseCounter++ ;
        antireb_SW1 = miliseconds;  // se captura el tiempo  para el antirebotes
    }

    if (barrierPulseCounter == 3)   // barrera está levantada
    {   
        barrierUp = TRUE;
		secondsLV = seconds; 		// para inicio del lavado vertical
    }
    else 
    {
        barrierUp = FALSE;
    }

	if (barrierPulseCounter == 5)
	{
		secondsLVOff = seconds;		// para apagado del lavado vertical
	}

    if (!SO2_f)
    {
        barrierDown = TRUE;
		secondsLVOff = seconds;
		barrierPulseCounter = 0;
    }
}

/********************************************
SENSOR ÓPTICO SO1: detector llegada coche
- Activo por flanco de subida y bajada
********************************************/
ISR (INT1_vect)
{
	if (miliseconds - antireb_S01 > SENSOR_DELAY) // antirebotes del sensor optico
	{
		if (SO1_f) // Acaba de dejar de detectar (flanco de subida)
		{
			carWaiting = FALSE;
		}
		else if(!SO1_f) // Empieza a detectar (flanco de bajada)
		{
			carWaiting = TRUE;
			barrier = TRUE;
			secondsLV = seconds;
			if (barrierPulseCounter > 3)
			{
				barrierStop();
			}
		}
		antireb_S01 = miliseconds;
	}
}

void barrera(barrier_status_t estado)
{
    if (estado == UP)
    {
        barrierUp ? barrierStop() : barrierMove();
		barrier = TRUE;

    }
    if (estado == DOWN)
    {
		if ( !barrierDown && SO1_f )
		{
			barrierMove();
		}
		else 
		{
			barrierStop();
		}
		barrier = TRUE;
    }
    if (estado == WAIT)
    {
        barrierStop();
		barrier = FALSE;
    }
    if(SO2_f)
	{
		barrierDown = FALSE;
	}
	else
	{
		barrierDown = TRUE;
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
				barrera(DOWN);
			}
			gestionCinta(BUSY);
			break;
		default:
			barrera(WAIT);
			break;			
	}
	
}