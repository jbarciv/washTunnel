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

#include "actuators.h"
#include "entrada.h"
#include "commonstuff.h"

extern miliseconds_t miliseconds;

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
// !!!!!!!!SE TIENE QUE COMPROBAR CON LA MAQUETA Y EL OSCILOSCÓPIO CÓMO FUNCIONAN REALMENTE ESTOS PULSOS!!!!!
    if (barrierPulseCounter == 5 || barrierPulseCounter == 0 || SO2_f == FALSE)
    {
        barrierDown = TRUE;
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
        if (PIND1 == 1)
        {
            
        }
        carWaiting = TRUE;
        antireb_S01 = miliseconds;
    }
    // if ((PIND& (1<<PIND1) == 1) && antirreb_S01 > DELAY_SENSOR)
    // {
    //     if (!barrierUp)vs control
    //     {
    //         bajando=1;
    //     }
    //     barrierMove();
    // }
}

void barrera(barrier_status_t estado)
{
    if (estado == UP)
    {
        barrierMove();
        if (barrierUp == TRUE)
        {
            barrierStop();
        }
    }
    if (estado == DOWN)
    {
        barrierMove();
        if (barrierDown == TRUE)
        {
            barrierStop();
        }
    }
    if (estado == WAIT)
    {
        barrierStop();
    }
    if (SO2_f == TRUE)
    {
        barrierDown = FALSE;
    }
}

void barrierMove()
{
    motor(M1,ON,DERECHA);
}

void barrierStop()
{
    motor(M1,OFF,DERECHA);
}

// void tunnelGotBusy()
// {
//     car++;    
// }


// void isBarrierDown ()
// {
//     if (PINK & (1<<PINK1)==1)
// }


// void barrierControl(status_t modo)
// {
//     switch(modo)
//     {
//         case ...
//     }
//     barrera(UP);
// }