void secado_horizontal_ISR()
{
	if(SH==1)   //Comprueba si el secado esta activo
	{							
		if(SO7_f && SO9_f)	//Sensores S07 y S09 sin detectar nada
		{		
			if(SO8_f)       //Sensor S08 sin detectar nada
			{ 			    
				M5_state = ON;
				M5_dir = IZQUIERDA;
			}
			else
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
	else
	{
		SH = 1;
		M5_state = ON;
		M5_dir = DERECHA;
	}
}