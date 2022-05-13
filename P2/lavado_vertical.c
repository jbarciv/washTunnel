#include "lavado_vertical.h"
#include "actuators.h"

extern bool LV;
extern bool LH;
extern seconds_t secondsLV;
extern seconds_t secondsLVOff;
extern bool barrierUp;
extern bool barrierDown;
extern char ready;
extern seconds_t seconds;
extern bool cinta;

static seconds_t timeOff = TLV_Off;


void lavado_vertical()
{
	if(LV == 1 ){ //LV valdra 1 despues de unos segundos tras abrirse la barrera
		
		motor(M2,ON,IZQUIERDA);
		
	} 
	else if(LV == 0){ //LV se pone a 0 cuando secado se enciende
		
		motor(M2,OFF,DERECHA);
		
	}
}

void gestionLV(mode_t mode)
{
	switch(mode)
	{
		case STARTING:
			LV = 0;
			motor(M2,OFF,DERECHA);
			ready |= (1<<LV_MOD);
			break;
		
		case BUSY:
			if (barrierUp && !SO1_f && ((secondsLV + T_LV) < seconds))
			{
				LV = 1;
				
			}
			if (!cinta)
			{
				timeOff = timeOff-(seconds - secondsLVOff);
				secondsLVOff = seconds;
			}

			if (barrierDown && ((secondsLVOff + timeOff) < seconds) && LH)
			{
				LV = 0;
				timeOff = TLV_Off;
			}
			else if (barrierDown && ((secondsLVOff + timeOff) < seconds) && !LH)
			{
				LV = 0;
				timeOff = TLV_Off;
			}
			
			break;
		
		case EMERGENCY:
			LV = 0;
			motor(M2,OFF,DERECHA);
			break;
		
		default:
			LV = 0;
			motor(M2,OFF,DERECHA);
	}
	lavado_vertical();	
}

