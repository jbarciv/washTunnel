/* FUNCION PARA LUZ INDICADORA DE ESTADO */ 

#include "luz.h"
#include "actuators.h"

extern seconds_t seconds;
extern bool LH;
extern bool LV;
extern bool SECADO;
extern bool coche; // para este podriamos hacer una macro como coche = LV || LH || SECADO
int ms_sin_coche=0;


void parpadeo(seconds_t ms, bool coche)
{
	if (coche)				//hay coche
	{
        ms_sin_coche = 0;   // se resetea la variable para que una vez deje de haber coche cuente 10s
		if(ms%2)			// en los medios segundos "pares" está encendida
        {
            luz(L1, ON);
        }
        else luz(L1, OFF);
	}
	else 
	{
        luz(L1, OFF);
		ms_sin_coche++;         //los medios segundos que pasan en modo standby
        if (!(ms_sin_coche%20)) // si han pasado 20 medios segunds (10s), se enciende medio segundo
        {
            luz(L1, ON);
        }
	}
}


