/* ----------------------------------------------------------------------------------
 *                     TIMERS PARA LA GESTIÓN DEL TIEMPO
 *
 *  --> miliseconds: varible global de tipo "unsigned long int", desborda a los
 *                   50 días aproximadamente.
 *  --> half_second: variable global de tipo "unsigned int", desborda a las 18 horas
 *                   aproximadamente.
 * --------------------------------------------------------------------------------- */

#include "commonstuff.h"
#include "luz.h"


extern miliseconds_t miliseconds;
extern seconds_t half_second;

extern bool LV;
extern bool LH;
extern bool SH;
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
    half_second++;
	coche = (barrier || LV || LH || SH || !SO10_f || !SO11_f || !SO12_f);
	cinta = (barrier || LV || LH || SH);
    parpadeo(half_second, coche);
}