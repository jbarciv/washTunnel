/* ----------------------------------------------------------------------------
 *                                 WASHTUNNEL
 * -------------------------------------------------------------------------- */

#include "commonstuff.h"
#include "setup.h"
#include "entrada.h"
#include "salida.h"
#include "lavado_vertical.h"
#include "cinta.h"

/********************* Variables globales ***********************************/
miliseconds_t   miliseconds = 0;
seconds_t       half_second = 0;

bool LV;
bool LH;
bool cinta;
bool barrier;
bool secado;

char ready = 0b00000000; //Variable encargada de registrar el proceso de STARTING del sistema


int main(void)
{   
    entradaSetup();
	timerSetup();
	salidaSetup();
	motorSetup();
    
    while(1)
    {
        if (ready != 0b01100011)
		{
			gestionBarrera(STARTING);
			gestionLV(STARTING);
			gestionCinta(STARTING);
			carLeavingTunnel(STARTING);
		}
		else if (ready == 0b01100011)
		{
			gestionBarrera(BUSY);
			gestionLV(BUSY);
			carLeavingTunnel(BUSY);
		}
    }
}