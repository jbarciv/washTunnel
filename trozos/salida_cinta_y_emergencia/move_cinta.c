void moveCinta()
{
    motor(M6,ON,DERECHA);
    cinta = TRUE;
}

void stopCinta()
{
    motor(M6,OFF,DERECHA);
    cinta = FALSE;
}