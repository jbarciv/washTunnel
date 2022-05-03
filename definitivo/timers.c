/* --------------------------------------------------------------------------
 * TIMERS PARA LA GESTIÓN DEL TIEMPO
 * - "miliseconds" varible global de tipo "unsigned long int", desborda a los
 * 50 días aproximadamente.
 * - "seconds" variable global de tipo "unsigned int", desborda a las 18 horas
 * aproximadamente.
 * -------------------------------------------------------------------------- */

#include "commonstuff.h"

extern miliseconds_t miliseconds;
extern seconds_t seconds;


/********************************************
INTERRUPCIÓN PERIÓDICA CADA 1 MILISEGUNDO
********************************************/
ISR (TIMER3_COMPA_vect)
{
    miliseconds++;
}

/********************************************
INTERRUPCIÓN PERIÓDICA CADA 1 SEGUNDO
********************************************/
ISR (TIMER4_COMPA_vect)
{
    seconds++;
}