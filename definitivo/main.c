/* ----------------------------------------------------------------------------
 *                                 WASHTUNNEL
 * -------------------------------------------------------------------------- */

#include "commonstuff.h"
#include "setup.h"
#include "entrada.h"
#include "salida.h"
#include "lavado_vertical.h"
#include "lavado_horizontal.h"
#include "secado_horizontal.h"
#include "cinta.h"

/********************* Variables globales ***********************************/
miliseconds_t   miliseconds = 0;
seconds_t       half_second = 0;

miliseconds_t  milisecondsFinal_LH = 0;
miliseconds_t  milisecondsFinal_SH = 0;
seconds_t seconds;

status_t M4_state = OFF;
status_t M3_state = OFF;
direccion_t M3_dir;


status_t M5_state = OFF;
direccion_t M5_dir;

bool LV;
bool LH;
bool LH_ready = 0;
bool LH_up_final = 0;
bool SH = 0;
bool SH_ready = 0;
bool SH_up_final = 0;
bool cinta;
bool barrier;

char ready = 0b00000000; //Variable encargada de registrar el proceso de STARTING del sistema

int main(void)
{   
	cli();
    entradaSetup();
	timerSetup();
	salidaSetup();
	motorSetup();
	emergenciaSetup();
	LHSetup();
	SHSetup();
	sei();
    
    while(1)
    {
        if (ready != 0b01101111)
		{
			gestionBarrera(STARTING);
			gestionLV(STARTING);
			gestionLH(STARTING);
			gestionSH(STARTING);
			gestionCinta(STARTING);
			carLeavingTunnel(STARTING);
		}
		else if (ready == 0b01101111)
		{
			gestionBarrera(BUSY);
			gestionLV(BUSY);
			gestionLH(BUSY);
			gestionSH(BUSY);
			carLeavingTunnel(BUSY);
		}
    }
}



