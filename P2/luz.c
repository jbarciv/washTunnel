/* FUNCION PARA LUZ INDICADORA DE ESTADO */ 

#include "commonstuff.h"
#include "luz.h"

int i = 0;
int modo = 0;		// modo de funcionamiento (SEGUN EL STATUS_T)



ISR(TIMER1_COMPA_vect) 
{
	switch modo
	{
		case WAITING:
		{
			L1PORT = 0;			// un poco ñapa, para que no se quede el port a 1 si cambia el estado cuando esté a 1
			i++;				//cada 10s parpadea
			parpadeo(i);
			break;
		}
		case BUSY:
		{
			L1PORT = !L1PORT; 	//conmuta cada 0.5s
			break;	
		}
		default: break;
	}
}

void parpadeo(int ms)
{
	if (ms%20 == 0)				//han pasado 10s (revisar, solo cuenta cuando está en waiting)
	{
		L1PORT = 1;
	}
	if ((ms-1)%20 == 0)
	{
		L1PORT = 0;
	}
}

