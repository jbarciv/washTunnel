/* FUNCION PARA LUZ INDICADORA DE ESTADO */ 

#include "commonstuff.h"
#include "luz.h"
#include <control.h>

int halfsec = 0;	
extern bool LH;
extern bool LV;
extern bool SECADO;
//extern bool BARRERA; -> falta algo que indique que la barrera se esta abriendo
int coche;              // me gustaria hacer una variable global que sea 1 en on y 0 en off
int ms_sin_coche=0;


bool coche =  1;

ISR(TIMER4_COMPA_vect) 
{
    halfsec++;

    parpadeo(halfsec, coche);
}

void parpadeo(int ms, bool coche)
{
	if (coche)				//hay coche
	{
        ms_sin_coche = 0; //resetea el timer del modo off
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

