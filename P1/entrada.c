/*

En esta funcion vamos a comprobar:
    Si algún coche está en la entrada
    Suma 1 coche por flanco de bajada (cuando pasa la parte trasera del coche)

En un futuro:
    Actualizará los datos del struct paramCar (dimensiones del coche)

De la apertura de la barrera es encargará otra función que maneje el motor consultando tunelGotBusy()

*/

#include <commonstuff.h>

#define DELAY_BOTON 50
#define DELAY_SENSOR 20
#define ANTIREB_TIME 125            // Con un preescalado de clk/64, 125 periodos es 1 ms
#define REAL_TIME 31250             // Con un preescalado de clk/256, 31250 periodos es 1 s
#define T_ENTRE_COCHES 5            // Dejamos 5 segundos al menos entre un coche y otro


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

int barrierPulseCounter = 0;
int carWaiting = false;

int tPreviousCar = 0;

int antireb_S01 = 0;
int antireb_S02 = 0;
int antireb_S03 = 0;
int antireb_S04 = 0;
int antireb_S05 = 0;
int antireb_S06 = 0;
int antireb_S07 = 0;
int antireb_S08 = 0;
int antireb_S09 = 0;
int antireb_S10 = 0;
int antireb_S11 = 0;
int antireb_S12 = 0;


int antireb_SW1 = 0;
int antireb_SW2 = 0;
int antireb_SW3 = 0;
int antireb_SW4 = 0;


ISR (TIMER3_COMPA_vect)
{
    antireb_SW1++;
    antireb_SW2++;
    antireb_SW3++;
    antireb_SW4++;

    antireb_S01++;
    antireb_S02++;
    antireb_S03++;
    antireb_S04++;
    antireb_S05++;
    antireb_S06++;
    antireb_S07++;
    antireb_S08++;
    antireb_S09++;
    antireb_S10++;
    antireb_S11++;
    antireb_S12++;
}

ISR (TIMER4_COMPA_vect)
{
    tPreviousCar++;
}


ISR(INTO_vect)
{
    if(antireb_SW1 > DELAY_BOTON)
    {
        barrierPulseCounter == 5? barrierPulseCounter = 1 : barrierPulseCounter++; //Movemos el motor siempre en el mismo sentido
        antireb_SW1 = 0;
    }
    if (barrierPulseCounter == 3)
        barrierStop();
}

ISR (PCINT2_vect)       // PCINT(23:16), puerto K
{
    if ((PINK & (1<<PINK0) == 0) && antirreb_S01 > DELAY_SENSOR)
    {
        if ( tPreviousCar > T_ENTRE_COCHES )
        {
            moveBarrier();
            tunelGotBusy();
        }
        else 
        {
            carWaiting = true;
        }
        antireb_S01 = 0;
    }

    if ((PINK & (1<<PINK1) == 0) && antirreb_S02 > DELAY_SENSOR)
    {
        barrierStop();
        tPreviousCar = 0;
        antireb_S02 = 0;
    }
}

void moveBarrier()
{
    //establecemos motor encendido
    PORTL |= (1<<PORTL0);
    //establecemos dirección
    PORTL |= (1<<PORTL1)
}

void barrierStop()
{
    PORTL &= (0<<PORTL0);
}

void tunelGotBusy()
{
    
}