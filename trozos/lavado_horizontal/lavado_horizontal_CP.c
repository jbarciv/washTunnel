void lavado_horizontal_CP()
{
	if(LH_up_final == 0) //Bandera de que se esta subiendo a la posicion final
	{
		if((PINK & (1 << 6)) == (1 << 6))
		{
			motor(M4,M4_state,DERECHA);
			motor(M3,M3_state,M3_dir);
		}else
		{
			M3_state = OFF;
			M4_state = OFF;
			LH_up_final = 1;
			milisecondsFinal_LH = miliseconds;
			motor(M4,OFF,DERECHA);
			motor(M3,ON,DERECHA);
		}
	}else
	{
		if(milisecondsFinal_LH + 2500 < miliseconds)
		{
			LH_up_final = 0;
			LH = 0;
			motor(M3,OFF,DERECHA);
		}
	}
}