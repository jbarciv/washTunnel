void parpadeo(seconds_t ms, bool coche)
{
	if (coche)
	{
		if(ms % 2)  // en los medios segundos "pares" esta encendida
        {
            luz(L1, ON);
        }
        else luz(L1, OFF);
	}
	else 
	{
        luz(L1, OFF);
		s_sin_coche++;
        // si han pasado 20 medios de segundo (10s), se enciende
        if ((s_sin_coche % 20) == 0) 
        {
            luz(L1, ON);
            s_sin_coche = 0;
        }
	}
}