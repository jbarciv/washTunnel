/********************************************
Funcion "barrera()". Se encarga de subir y 
bajar la barrera bajo ciertas condiciones
internamente implementadas.
********************************************/
void barrera(barrier_status_t estado)
{
	switch (estado)
	{
		case UP:
			if (barrierPulseCounter < 4)
        	{
				barrierMove();
        	}
			else
			{
				barrierStop();
			}
			barrier = TRUE;
			break;

		case DOWN:
			if (barrierDown)
			{
				barrierStop();
				barrier = FALSE;
			}
			else
			{
				if (antiCollision == FALSE)
				{
					barrierMove();
					barrier = TRUE;
				}
				else
				{
					barrierStop();
				}
			}
			break;

		case WAIT:
			barrierStop();
			barrier = FALSE;
			break;

		default:
			break;
	}
    
    if(SO2_f)
	{
		barrierDown = FALSE;
	}
	else
	{
		barrierDown = TRUE;
		barrier = FALSE;
		barrierPulseCounter = 0;
	}
}