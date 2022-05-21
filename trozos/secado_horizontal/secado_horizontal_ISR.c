void secado_horizontal_ISR()
{
	if(SH==1)   //Bandera que indica si el secado horizontal esta activo
	{													
		if(SO7_f && SO9_f)  //Se comprueba si S07 y S09 estan detectando algo, si detectan algo el lavado tiene q subir							    
		{		
			if(SO8_f)   //Se comprueba si S08 sin detectando algo, si no detecta el lavado esta muy alto y tiene q bajar			
			{ 				
				M5_state = ON;
				M5_dir = IZQUIERDA;
			}
			else    //Si SO8 detecta y SO7 y SO9 el lavado esta en la posicion adecuada
			{
				M5_state = OFF;
			}
		}
		else    
		{
			M5_state = ON;
			M5_dir = DERECHA;
		}
	}
	else    //Si el la bandera SH esta a 0 y hay interrupcion se activa la bandera y se encienden los motores
	{
		SH = 1;
		M5_state = ON;
		M5_dir = DERECHA;
	}
}