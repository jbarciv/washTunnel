/* --------------------------------------------------------------------------
 * TIMERS PARA LA GESTIÓN DEL TIEMPO
 * - "miliseconds" varible global de tipo "unsigned long int", desborda a los
 * 50 días aproximadamente.
 * - "half_second" variable global de tipo "unsigned int", desborda a las 18 horas
 * aproximadamente.
 * -------------------------------------------------------------------------- */

#include "commonstuff.h"
#include "luz.h"


extern miliseconds_t miliseconds;
extern seconds_t half_second;
extern bool LV;
extern bool LH;
extern bool secado;
extern bool cinta;
extern bool barrier;

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
	coche = (barrier || LV || LH || secado || !SO10_f || !SO11_f || !SO12_f);
    half_second++;
	coche ? (cinta=TRUE) : (cinta=FALSE);
    parpadeo(half_second, coche);
}