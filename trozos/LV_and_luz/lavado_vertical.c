void lavado_vertical()
{
	if(LV == 1 ){ //LV valdra 1 despues de unos segundos tras abrirse la barrera
		
		motor(M2,ON,IZQUIERDA);
		
	} 
	else if(LV == 0){ //LV se pone a 0 cuando pasa un tiempo de que la barrera se apaga
		
		motor(M2,OFF,DERECHA);
		
	}
}