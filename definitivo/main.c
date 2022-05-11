/* ----------------------------------------------------------------------------
 *                                 WASHTUNNEL
 * -------------------------------------------------------------------------- */

#include "commonstuff.h"
#include "setup.h"
#include "entrada.h"
#include "actuators.h"

/********************* Variables globales ***********************************/
miliseconds_t   miliseconds = 0;
seconds_t       seconds = 0;

char ready = 0b00000000; //Variable encargada de registrar el proceso de STARTING del sistema


int main(void)
{   
    entradaSetup();
	timerSetup();
    
    while(1)
    {
        if (ready != 0b00000001)
		{
			barrierControl(STARTING);
		}
		else if (ready == 0b00000001)
		{
			barrierControl(BUSY);
		}
    }
}