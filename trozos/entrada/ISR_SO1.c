ISR (INT1_vect)
{
	if (miliseconds - antireb_S01 > SENSOR_DELAY) // antirrebotes del sensor optico
	{
		if (SO1_f) // Acaba de dejar de detectar (flanco de subida)
		{
			carWaiting = FALSE;
			antiCollision = FALSE;
		}
		else if(!SO1_f) // Empieza a detectar (flanco de bajada)
		{
			carWaiting = TRUE;
			barrier = TRUE;
			if (barrierPulseCounter > 3) // si la barrera esta bajando
			{
				// y el coche intenta entrar de nuevo la barrera se para
				barrierStop();
				antiCollision = TRUE;
			}
		}
		antireb_S01 = miliseconds; // se captura el tiempo  para el antirrebotes
	}
}