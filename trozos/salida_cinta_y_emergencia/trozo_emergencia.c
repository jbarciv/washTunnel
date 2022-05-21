ISR(INT3_vect) 
{   // Espera bloqueante, será necesario resetear el micro.
    // Se entiede que el operario encargado del tunel de lavado
    // ha tenido que parar todo por un problema grave.
    while (1)  
    { 
        gestionBarrera(EMERGENCY);
        gestionCinta(EMERGENCY);
		gestionLV(EMERGENCY);
		gestionLH(EMERGENCY);
		gestionSH(EMERGENCY);
		carLeavingTunnel(EMERGENCY);
    }
    
}