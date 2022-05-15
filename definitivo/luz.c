/* FUNCION PARA LUZ INDICADORA DE ESTADO */ 

#include "luz.h"
#include "actuators.h"

extern bool coche;
seconds_t s_sin_coche = 0;


void parpadeo(seconds_t ms, bool coche)
{
	if (coche)
	{
		if(ms % 2)			        // en los medios segundos "pares" está encendida
        {
            luz(L1, ON);
        }
        else luz(L1, OFF);
	}
	else 
	{
        luz(L1, OFF);
		s_sin_coche++;
        if ((s_sin_coche % 20) == 0) // si han pasado 20 medios de segundo (10s), se enciende
        {
            luz(L1, ON);
        }
	}
}


