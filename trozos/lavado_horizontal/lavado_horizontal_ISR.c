void lavado_horizontal_ISR()
{	//Bandera que indica si el lavado horizontal esta activo
	if(LH == 1)
	{		
		if(SO3_f && SO5_f)	//Se comprueba si S03 y S05 estan detectando algo
		{						
			if(SO4_f)		//Se comprueba si S04 sin detectando algo			
			{													
				M3_state = ON;
				M3_dir = IZQUIERDA;
			}else
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
	else
	{
		LH=1;
		M4_state = ON;
		M3_state = ON;
		M3_dir = DERECHA;
	}
}