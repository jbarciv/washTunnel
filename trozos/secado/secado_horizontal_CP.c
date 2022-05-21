void secado_horizontal_CP()
{
	if(SH_up_final == 0)	//Bandera de que se esta subiendo a la posicion final
	{
		if((PINK & (1 << 7)) == (1 << 7))
		{
			motor(M5,M5_state,M5_dir);
		}
		else
		{
			M5_state = OFF;
			SH_up_final = 1;
			milisecondsFinal_SH = miliseconds;
			motor(M5,ON,DERECHA);
		}
	}
	else
	{
		if(milisecondsFinal_SH + 1250 < miliseconds)
		{
			M5_state = OFF;
			SH_up_final = 0;
			SH = 0;
			motor(M5,OFF,DERECHA);
		}
	}	
}