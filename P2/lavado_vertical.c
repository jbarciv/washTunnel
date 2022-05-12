#include "lavado_vertical.h"

extern bool LV;
extern int secondsLV;
extern bool barrierUp;
extern char ready;
extern seconds_t seconds;


void lavado_vertical()
{
	if(LV == 1 ){ //LV valdra 1 despues de unos segundos tras abrirse la barrera
		
		Motor(M2,ON,DERECHA);
		
	} elsif(LV == 0){ //LV se pone a 0 cuando secado se enciende
		
		Motor(M2,OFF,DERECHA);
		
	}
}

void gestionLV(mode_t mode){

	switch(mode)
	{
		case STARTING:
			LV = 0;
			Motor(M2,OFF,DERECHA);
			ready |= (1<<LV_MOD);
			break;
		
		case BUSY:
			if (barrierUp && SO1_f == 0 && secondsLV > (seconds + T_LV)){
				LV = 1;
			}
			break;
		
		case EMERGENCY:
			LV = 0;
			Motor(M2,OFF,DERECHA);
			break;
		
		default:
			LV = 0;
			Motor(M2,OFF,DERECHA);
	}	
}

