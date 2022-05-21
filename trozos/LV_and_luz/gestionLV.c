void gestionLV(mode_t mode)
{
	switch(mode)
	{
		case STARTING:
			LV = 0;
			motor(M2,OFF,DERECHA);
			ready |= (1<<LV_MOD);
			break;
		
		case BUSY:
			if (barrierUp && !SO1_f && ((secondsLV + T_LV) < half_second))
			{
				LV = 1;
			}
			if (!cinta)
			{
				timeOff = timeOff-(half_second - secondsLVOff);
				secondsLVOff = half_second;
			}
			if (barrierDown && ((secondsLVOff + timeOff) < half_second))
			{
				LV = 0;
				timeOff = TLV_Off;
			}
			
			break;
		
		case EMERGENCY:
			LV = 0;
			motor(M2,OFF,DERECHA);
			break;
		
		default:
			LV = 0;
			motor(M2,OFF,DERECHA);
	}
	lavado_vertical();	
}