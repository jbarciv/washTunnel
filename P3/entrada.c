/*
BARRERA ENTRADA AL TUNEL DE LAVADO
En esta funcion vamos a comprobar:
    Si algún coche está en la entrada
    Suma 1 coche por flanco de bajada (cuando pasa la parte trasera del coche)
En un futuro:
    Actualizará los datos del struct paramCar (dimensiones del coche)
De la apertura de la barrera es encargará otra función que maneje el motor consultando tunnelGotBusy()

La apertura de barrera debe ser controlada por consulta periódica 
porque puede que justo cuando llega el coche no pueda ser abierta porque 
hay otro que acaba de entrar. Al hacerlo por consulta periódica coseguimos 
que pueda haber un periodo de espera fuera de las interrupciones, simplificándolas. 
A tal efecto se ha creado la bandera carWaiting.
*/
#include "commonstuff.h"
#include "entrada.h"
#include "actuators.h"

extern miliseconds_t miliseconds;
extern char ready;

int barrierPulseCounter = 0;
bool barrierUp;
bool barrierDown;

bool carWaiting = FALSE;
seconds_t tPreviousCar = 0;

miliseconds_t antireb_S01 = 0;
miliseconds_t antireb_SW1 = 0;


/********************************************
MICROINTERRUPTOR SW1: contador pulsos barrera
- Activo por flanco de subida
********************************************/
ISR(INT0_vect) 
{   
    if ((miliseconds - antireb_SW1) > BOTON_DELAY) // antirrebotes del microinterruptor
    {   // se lleva la cuenta de los pulsos; cuando llega a cinco se resetea
        (barrierPulseCounter == 5) ? (barrierPulseCounter = 0) : barrierPulseCounter++ ;
        antireb_SW1 = miliseconds;  // se captura el tiempo  para el antirrebotes
    }

    if (barrierPulseCounter == 3)   // cuando esto se cumple la _barrera está levantada_
    {   // se controla el estado de la barrera con una bandera
        barrierUp = TRUE;
    }
    else 
    {
        barrierUp = FALSE;
    }
    if (SO2_f == FALSE)
    {
        barrierDown = TRUE;
		barrierPulseCounter = 0;
    }
}

/********************************************
SENSOR ÓPTICO SO1: detector llegada coche
- Activo por flanco de subida y bajada
********************************************/

ISR (INT1_vect)
{
	// Antirebotes
	if (miliseconds - antireb_S01 > SENSOR_DELAY)
	{
		/*
		La siguiente lógica supone que no nos vacilan,
		si quieres entrar en el túnel no debes dar marcha atrás
		en frente de la barrera...
		*/
		if (SO1_f) // Acaba de dejar de detectar (flanco de subida)
		{
			carWaiting = FALSE;
		}
		else if(!SO1_f) // Empieza a detectar (flanco de bajada)
		{
			carWaiting = TRUE;
		}
		antireb_S01 = miliseconds;
	}
}

void barrera(barrier_status_t estado)
{
    if (estado == UP)
    {
        barrierUp? barrierStop():barrierMove();
    }
    if (estado == DOWN)
    {
        barrierDown? barrierStop():barrierMove();
    }
    if (estado == WAIT)
    {
        barrierStop();
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

void barrierControl(mode_t modo)
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
				ready |= (1<<ENTRY_MOD);
			}
			break;
		
		case EMERGENCY:
			barrera(WAIT);
			break;
		
		case BUSY:
			if (carWaiting == TRUE /*&& LV == FALSE*/)
			{
				barrera(UP);	
			}
			else 
			{
				barrera(DOWN);
			}
			break;
		default:
			barrera(WAIT);
			break;			
	}
}