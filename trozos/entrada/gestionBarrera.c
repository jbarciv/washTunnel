void gestionBarrera(mode_t modo)
{
    switch (modo)
	{
		case STARTING:
			if (carWaiting == FALSE && SO2_f == 1)
			{
				barrera(DOWN);
			}
			
			if (SO2_f == 0 || barrierDown == TRUE)
			{
				barrera(WAIT);
				ready |= (1 << ENTRY_MOD);
			}
			break;
		
		case EMERGENCY:
			barrera(WAIT);
			break;
		
		case BUSY:
			if (carWaiting == TRUE && LV == FALSE)
			{
				barrera(UP);
			}
			else 
			{
				SO1_f ? barrera(DOWN) : barrera(WAIT);
			}
			gestionCinta(BUSY);
			break;

		default:
			barrera(WAIT);
			break;			
	}
}