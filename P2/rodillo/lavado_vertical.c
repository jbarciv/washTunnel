/*
 * GccApplication1.c
 *
 * Created: 27/04/2022 14:28:10
 * Author : Mar
 */ 

#include <avr/io.h>
#include "commonstuff.h"
#include "lavado_vertical.h"
#include <control.h>

void lavado_vertical()
{
	if(LV == 1 ){ //LV valdr� 1 despu�s de unos segundos tras abrirse la barrera
		
		Motor(M2,ON,DERECHA);
		
	} elsif(LV == 0){ //LV valdr� 0 despu�s de que el coche active el sensor S07
		
		Motor(M2,OFF,DERECHA);
		
	}
}

