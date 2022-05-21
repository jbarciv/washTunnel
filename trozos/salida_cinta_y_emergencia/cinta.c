void gestionCinta (mode_t modo)
{
    switch (modo)
    {
        case STARTING:
            stopCinta();
            ready |= (1<<BELT_MOD);
            break;

        case WAITING:
			stopCinta();
			break;
        case BUSY:
            cinta ? moveCinta() : stopCinta();
            break;

        case EMERGENCY:
            stopCinta();
            break;
        
        default:
            stopCinta();
            break;
    }

}