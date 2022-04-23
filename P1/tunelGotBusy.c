/*

En esta funcion vamos a comprobar:
    Si algún coche está en la entrada
    Suma 1 coche por flanco de bajada (cuando pasa la parte trasera del coche)

En un futuro:
    Actualizará los datos del struct paramCar (dimensiones del coche)

De la apertura de la barrera es encargará otra función que maneje el motor consultando tunelGotBusy()

*/

#include <commonstuff.h>

// Aunque en esta función solo vamos a utilizar una PCINT, en el setup hay que activarlas todas para poder usarlas en otras funciones

cli();
// El SO1 es el DDRD1 y debe ir como entrada(0).
PCICR |= (1<<PCIE1);       // Activamos las PCINT(15:8)
PCMSK1 |= (1<<PCINT8);     // Habilitamos la interrupcion 
sei();                     //Habilitamos las interrupciones globales

//La apertura de barrera debe ser controlada por consulta periódica porque puede que justo cuando llega el coche no pueda ser abierta porque hay otro que acaba de entrar. Al hacerlo por consulta periódica coseguimos que pueda haber un periodo de espera fuera de las interrupciones, simplificándolas.

ISR(PCINT1_vect)
{
    if (antireb_S01 > 300 && tPreviousCar >)
    {
        barrierUp();
        tunelGotBusy();
    }
    else 
    {
        flag_S01 = 1;
    }
}

// Subrutina consulta periódica S01 en caso de no poder levantar la barrera en la interrupción

void barrierUp()
{
    barrierPulseCounter = 0;
    if (barrierPulseCounter < 3)
    {
        //establecemos motor encendido
        //establecemos dirección
    }
    
}

