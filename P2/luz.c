/* FUNCION PARA LUZ INDICADORA DE ESTADO */ 

#include "commonstuff.h"
#include "luz.h"
#include <control.h>

int halfsec = 0;
int modo = 0;		// modo de funcionamiento (SEGUN EL STATUS_T)
extern bool LH;
extern bool LV;
extern bool SECADO;
int coche;
int ms_sin_coche=0;


bool coche =  LV || LH || SECADO;

ISR(TIMER3_COMPA_vect) 
{
    halfsec++;

    parpadeo(halfsec, coche);
}

void parpadeo(int ms, bool coche)
{
	if (coche)				//hay coche
	{
		if(ms%2) 
        {
            luz(L1, ON);
        }
        else luz(L1, OFF);
	}
	else 
	{
        LUZ(L1, OFF);
		ms_sin_coche++;
        if (ms_sin_coche%20)
        {
            LUZ(L1, ON);
        }
	}
}

