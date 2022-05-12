/* ----------------------------------------------------------------------------
 *                                 WASHTUNNEL
 * -------------------------------------------------------------------------- */

#include "commonstuff.h"
#include "setup.h"
#include "entrada.h"
#include "actuators.h"
#include "salida.h"

/********************* Variables globales ***********************************/
miliseconds_t   miliseconds = 0;
seconds_t       seconds = 0;

bool LV;
bool cinta;
bool barrier;

char ready = 0b00000000; //Variable encargada de registrar el proceso de STARTING del sistema


int main(void)
{   
    entradaSetup();
	timerSetup();
	salidaSetup();
    
    while(1)
    {
        if (ready != 0b01000011)
		{
			gestionBarrera(STARTING);
			gestionLV(STARTING);
			carLeavingTunnel(STARTING);
		}
		else if (ready == 0b01000011)
		{
			gestionBarrera(BUSY);
			gestionLV(BUSY);
			carLeavingTunnel(BUSY);
		}
    }
}