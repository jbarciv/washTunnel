void secado_horizontal_CP()
{	// Bandera de que se esta subiendo a la posicion final 
	if(SH_up_final == 0)                                                  
	{	// Mientras no se detecte nada en SW3 los motores funcionan con las
		if((PINK & (1 << 7)) == (1 << 7))	// banderas de secado_horizontal_ISR
		{
			motor(M5,M5_state,M5_dir);
		}
		else // En cuanto detecta SW3 se inicia el ascenso a la posicion de reposo
		{
			M5_state = OFF;
			// Se pone a 1 la bandera de que se esta subiendo a la posicion final
			SH_up_final = 1;	
			milisecondsFinal_SH = miliseconds;
			motor(M5,ON,DERECHA);
		}
	}
	else	// Cuando el secado lleva 1250ms subiendo hacia la posicion final 
	{	 	// se paran los motores y se baja la bandera SH_up_final
		if(milisecondsFinal_SH + 1250 < miliseconds)
		{
			M5_state = OFF;
			SH_up_final = 0;
			SH = 0;
			motor(M5,OFF,DERECHA);
		}
	}	
}
