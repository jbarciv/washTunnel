void carLeavingTunnel (mode_t mode)
{
    switch (mode)
    {
        case STARTING:
            if (SO12_f && SO11_f && SO10_f)
            {
                semaforo(RED);
                ready |= (1 << OUT_MOD);
            }else
            {
                semaforo(GREEN);
                ready &= ~(1 << OUT_MOD);
            }
            break;
        case WAITING:
        case BUSY:
            if (SO12_f)  // No hay nada cortando el sensor. No esta detectando
            {
                if (prevState)
                {   // No detecta nada
                    prevState = TRUE;   
                }else if (!prevState)   // Esto es un flanco de subida. 
                {                       // Antes detectaba y ahora no.     
                    if (!SO11_f)    // Se produce un flanco de subida,  
                    {   // pero sigue habiendo coche dentro, estan dando
                        prevState = TRUE;   // marcha atras en la salida
                    }else if (SO11_f)   // el coche esta saliendo de verdad
                    {
                        carLeaving = FALSE;
                        semaforo(RED);
                        gestionCinta(BUSY);
                        prevState = TRUE;
                    }
                }
            }else if (!SO12_f)
            {
                prevState = FALSE;    
            }
			if (!SO11_f && !SO10_f )
			{
				semaforo(GREEN);
			}
            if (!SO10_f && !SO11_f && !SO12_f)
            {   // Si detecto
                carLeaving = TRUE;
            }   // Si hay un coche en el secado y otro en la salida...
            if (carLeaving && SH) // paramos la cinta para evitar choques
            {
                gestionCinta(WAITING);  
            }
            break;
        case EMERGENCY:
            semaforo(RED);
            break;
    }
}