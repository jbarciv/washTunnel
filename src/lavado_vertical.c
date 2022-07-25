/* ----------------------------------------------------------------------------
 *                       CONTROL DEL LAVADO VERTICAL
 * 
 * DATE:    13/05/2022
 * AUTHOR:  Gonzalo Quiros Torres
 * 			María del Mar Martín Diaz
 *          Celia Ramos Ramírez
 * 			Josep María Barberá Civera
 * -------------------------------------------------------------------------- */

#include "lavado_vertical.h"
#include "actuators.h"

extern bool LV;
extern bool LH;
extern seconds_t secondsLV;
extern seconds_t secondsLVOff;
extern bool barrierUp;
extern bool barrierDown;
extern char ready;
extern seconds_t half_second;
extern bool cinta;

static seconds_t timeOff = TLV_Off;


void lavado_vertical()
{
	if(LV == 1 ){ //LV valdra 1 despues de unos segundos tras abrirse la barrera
		
		motor(M2,ON,IZQUIERDA);
		
	} 
	else if(LV == 0){ //LV se pone a 0 cuando pasa un tiempo de que la barrera se apaga
		
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
			if (barrierUp && !SO1_f && ((secondsLV + T_LV) < half_second))
			{
				LV = 1;
			}
			if (!cinta)
			{
				timeOff = timeOff-(half_second - secondsLVOff);
				secondsLVOff = half_second;
			}
			if (barrierDown && ((secondsLVOff + timeOff) < half_second))
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

