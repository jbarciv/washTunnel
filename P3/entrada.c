/*
En esta funcion vamos a comprobar:
    Si algún coche está en la entrada
    Suma 1 coche por flanco de bajada (cuando pasa la parte trasera del coche)

En un futuro:
    Actualizará los datos del struct paramCar (dimensiones del coche)

De la apertura de la barrera es encargará otra función que maneje el motor consultando tunnelGotBusy()
*/

#include "commonstuff.h"
#include "actuators.h"
#include "entrada.h"

// Aunque en esta función solo vamos a utilizar una PCINT, en el setup hay que activarlas todas para poder usarlas en otras funciones

cli();
// El SO1 es el DDRD1 y debe ir como entrada(0).
PCICR |= (1<<PCIE1);       // Activamos las PCINT(15:8)
PCMSK1 |= (1<<PCINT8);     // Habilitamos la interrupcion

sei();                     //Habilitamos las interrupciones globales

void setup_timers()
{
    // setup del contador 3

    cli ();

    TCCR3B |= (1<<WGM32);               // Modo ctc

    TCCR3B |= (1<<CS31)|(1<<CS30);      // Preescalado clk/64 (periodo de 8 uS)
    OCR3A = ANTIREB_TIME;               // Contamos COUNTER_TIME periodos

    TIMSK3 |= (1<<OCIE3A);              // Habilitamos la interrupción por compare match

    // setup del contador 4

    TCCR3B |= (1<<WGM42);               // Modo ctc

    TCCR3B |= (1<<CS42);                // Preescalado clk/256 (periodo de 32 uS)
    OCR3A = REAL_TIME;                  // Contamos REAL_TIME periodos (=1 S)

    TIMSK3 |= (1<<OCIE4A);              // Habilitamos la interrupción por compare match

    sei();
}

//La apertura de barrera debe ser controlada por consulta periódica porque puede que justo cuando llega el coche no pueda ser abierta porque hay otro que acaba de entrar. Al hacerlo por consulta periódica coseguimos que pueda haber un periodo de espera fuera de las interrupciones, simplificándolas. A tal efecto se ha creado la bandera carWaiting.




ISR (TIMER3_COMPA_vect) // Interrumpe cada 1 ms
{
    miliseconds++;
}

ISR (TIMER4_COMPA_vect) // Interrumpe cada 1 s
{
    seconds++;
}


//Activo por flanco de subida
ISR(INTO_vect) // Microinterruptor SW1: contador pulsos barrera
{   
    if ((miliseconds - antireb_SW1) > BOTON_DELAY)
    {   
        (barrierPulseCounter == 5) ? (barrierPulseCounter = 0) : barrierPulseCounter++ ;
        antireb_SW1 = miliseconds;
    }
    if (barrierPulseCounter == 3)   // Barrera levantada
        barrierUp = true;
    }
    else 
    {
        barrierUp = false;
    }
    if (barrierPulseCounter == 5 || barrierPulseCounter == 0 || SO2_f == false)   // Barrera levantada
        barrierDown = true;
    }
}

//Activo por flanco de subida y bajada.
ISR (INT1_vect)
{
    // if ((PIND & (1<<PIND1) == 0) && antirreb_S01 > SENSOR_DELAY)
    if (miliseconds - antireb_S01 > BOTON_DELAY)
    {
    // if (seconds - tPreviousCar > T_ENTRE_COCHES)
    // {
        barrierMove();
    // }
    // else 
    // {
    //     carWaiting = TRUE;
    // }
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

void barrierMove()
{
    Motor(M1,ON,DERECHA);
}

void barrierStop()
{
    Motor(M1,OFF,DERECHA);
}

// void tunnelGotBusy()
// {
//     car++;    
// }


void isBarrierDown ()
{
    if (PINK & (1<<PINK1)==1)
}


void barrera(barrier_status_t estado)
{
    if (estado == UP)
    {
        barrierMove();
        if (barrierUp)
        {
            barrierStop();
        }
    }

    if (estado == DOWN)
    {
        barrierMove();
        if (barrierDown)
        {
            barrierStop();
        }
    }

    if (estado == WAIT)
    {
        barrierStop();
    }
    
    if (SO2_f == true)
    {
        barrierDown = false;
    }
}

void barrierControl(status_t modo)
{
    switch(modo)
    {
        case ...
    }
    barrera(UP);
}