void secado_horizontal_CP()
{
	if(SH_up_final == 0)	//Bandera de que se esta subiendo a la posicion final                                                   
	{
		if((PINK & (1 << 7)) == (1 << 7))	//Mientras no se detecte nada en SW3 los motores funcionan con las baderas de secado_horizontal_ISR									
		{
			motor(M5,M5_state,M5_dir);
		}
		else	//En cuanto detecta algo SW3 se inicia el ascenso a la posicion de reposo
		{
			M5_state = OFF;
			SH_up_final = 1;	//Se pone a 1 la banderade que se esta subiendo a la posicion final
			milisecondsFinal_SH = miliseconds;
			motor(M5,ON,DERECHA);
		}
	}
	else
	{
		if(milisecondsFinal_SH + 1250 < miliseconds)	//Cuando el lavado lleva 1250ms subiendo hacia la posicion final se paran los motors y se baja la bandera SH_up_final
		{
			M5_state = OFF;
			SH_up_final = 0;
			SH = 0;
			motor(M5,OFF,DERECHA);
		}
	}	
}
