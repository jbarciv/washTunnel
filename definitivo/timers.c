/* --------------------------------------------------------------------------
 * TIMERS PARA LA GESTIÓN DEL TIEMPO
 * - "miliseconds" varible global de tipo "unsigned long int", desborda a los
 * 50 días aproximadamente.
 * - "seconds" variable global de tipo "unsigned int", desborda a las 18 horas
 * aproximadamente.
 * -------------------------------------------------------------------------- */

#include "commonstuff.h"
#include "luz.h"


extern miliseconds_t miliseconds;
extern seconds_t seconds;
extern bool LV;
extern bool LH;
extern bool secado;

bool coche = FALSE;

/********************************************
INTERRUPCIÓN PERIÓDICA CADA 1 MILISEGUNDO
********************************************/
ISR (TIMER3_COMPA_vect)
{
    miliseconds++;
}

/********************************************
INTERRUPCIÓN PERIÓDICA CADA 0.5 SEGUNDOs
********************************************/
ISR (TIMER4_COMPA_vect)
{	
	coche = (!SO1_f || LV || LH || secado || !SO10_f || !SO11_f || !SO12_f);
    seconds++;
    parpadeo(seconds, coche);
}