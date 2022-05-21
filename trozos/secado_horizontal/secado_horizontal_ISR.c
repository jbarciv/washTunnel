void secado_horizontal_ISR()
{	// Bandera que indica si el secado horizontal esta activo
	if(SH==1)   
	{	// Se comprueba si S07 y S09 estan detectando algo, 							
		if(SO7_f && SO9_f)	// si detectan algo el lavado tiene que subir			    
		{	// Se comprueba si S08 detecta algo, si no detecta el lavado
			if(SO8_f)	// esta muy alto y tiene que bajar
			{ 				
				M5_state = ON;
				M5_dir = IZQUIERDA;
			}
			else	// Si SO8 detecta y SO7 y SO9 tambien el  
			{		// lavado esta en la posicion adecuada
				M5_state = OFF;
			}
		}
		else    
		{
			M5_state = ON;
			M5_dir = DERECHA;
		}
	}
	else    // Si el la bandera SH esta a 0 y hay interrupcion 
	{		// se activa la bandera y se encienden los motores
		SH = 1;
		M5_state = ON;
		M5_dir = DERECHA;
	}
}