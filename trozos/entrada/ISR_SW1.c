ISR(INT0_vect) 
{   // antirrebotes del microinterruptor
    if ((miliseconds - antireb_SW1) > BOTON_DELAY) 
    {   // se lleva la cuenta de los pulsos de SW1
        barrierPulseCounter++ ;
        antireb_SW1 = miliseconds;  // se captura el tiempo  para el antirrebotes
    }

    if (barrierPulseCounter == 4)   // barrera esta levantada
    {   // se controla el estado de la barrera con una bandera
        barrierUp = TRUE;
		// capturamos el tiempo para el inicio del Lavado Vertical
		secondsLV = half_second; 
    }
    else 
    {
        barrierUp = FALSE;
    }
	if (barrierPulseCounter == 5)
	{   // capturamos el tiempo para apagar el Lavado Vertical
		secondsLVOff = half_second;
	}
    if (SO2_f == FALSE)
    {
        barrierDown = TRUE;
		secondsLVOff = half_second;
		barrierPulseCounter = 0;
    }
}