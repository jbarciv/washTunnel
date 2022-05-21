void lavado_horizontal_ISR()
{	
	if(LH == 1)		//Bandera que indica si el lavado horizontal esta activo
	{		
		if(SO3_f && SO5_f)	//Se comprueba si S03 y S05 estan detectando algo, si detectan algo el lavado tiene q subir
		{						
			if(SO4_f)	//Se comprueba si S04 sin detectando algo, si no detecta el lavado esta muy alto y tiene q bajar			
			{													
				M3_state = ON;
				M3_dir = IZQUIERDA;
			}
			else	//Si SO4 detecta y SO3 y SO5 el lavado esta en la posicion adecuada
			{
				M3_state = OFF;
			}
		}
		else
		{
			M3_state = ON;
			M3_dir = DERECHA;
		}
	}
	else	//Si el la bandera LH esta a 0 y hay interrupcion se activa la bandera y se encienden los motores
	{
		LH=1;
		M4_state = ON;
		M3_state = ON;
		M3_dir = DERECHA;
	}
}