void lavado_horizontal_CP()
{
	if(LH_up_final == 0) 	//Bandera de que se esta subiendo a la posicion final
	{
		if((PINK & (1 << 6)) == (1 << 6))	//Mientras no se detecte nada en SW2 los motores funcionan con las baderas de lavado_horizontal_ISR
		{
			motor(M4,M4_state,DERECHA);
			motor(M3,M3_state,M3_dir);
		}
		else	//En cuanto detecta algo SW2 se inicia el ascenso a la posicion de reposo
		{
			M3_state = OFF;					
			M4_state = OFF;
			LH_up_final = 1;	//Se pone a 1 la banderade que se esta subiendo a la posicion final
			milisecondsFinal_LH = miliseconds;
			motor(M4,OFF,DERECHA);
			motor(M3,ON,DERECHA);
		}
	}
	else
	{
		if(milisecondsFinal_LH + 2500 < miliseconds)	//Cuando el lavado lleva 2500ms subiendo hacia la posicion final se paran los motors y se baja la bandera LH_up_final
		{
			LH_up_final = 0;
			LH = 0;
			motor(M3,OFF,DERECHA);
		}
	}
}