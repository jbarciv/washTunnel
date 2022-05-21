void lavado_horizontal_ISR()
{	// Bandera que indica si el lavado horizontal esta activo
	if(LH == 1)		
	{	// Se comprueba si S03 y S05 estan detectando, si detectan, el lavado sube	
		if(SO3_f && SO5_f)	
		{	// Se comprueba si S04 detecta algo, si no detecta, el lavado baja
			if(SO4_f)
			{													
				M3_state = ON;
				M3_dir = IZQUIERDA;
			}
			else	// Si SO4 detecta y SO3 y SO5 tambien, entonces...	
			{		// ...el lavado esta en la posicion adecuada
				M3_state = OFF;
			}
		}
		else
		{
			M3_state = ON;
			M3_dir = DERECHA;
		}
	}		// Si la bandera LH esta a 0 y hay interrupcion,
	else	// se activa la bandera y se encienden los motores.
	{
		LH=1;
		M4_state = ON;
		M3_state = ON;
		M3_dir = DERECHA;
	}
}