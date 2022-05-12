/* ----------------------------------------------------------------------------
 *               CONTROL DEL HARDWARE - DECLARACIÓN DE FUNCIONES
 *  - MOTOR
 *  - LUZ
 * 
 * DATE: 02/05/2022
 * AUTHOR: Josep María Barberá Civera
 * -------------------------------------------------------------------------- */

#include "actuators.h"

/*************************************** 
MOTORES
    motor  -> {M1, M2, M3, M4, M5, M6}
    estado -> {ON, OFF}                 
    giro   -> {DERECHA, IZQUIERDA}
ej. motor(M1, ON, DERECHA);
***************************************/
void motor(motor_t motor, status_t estado, direccion_t giro)
{
    switch (motor)
    {
        case M1:
			if(estado == ON)
			{
				if (giro == DERECHA)    // Establecemos la direccion (1=drcha. 0=izqda.)
				{
					M1DIPORT |= (1 << M1DIpin);
				}
				else
				{
					M1DIPORT &= ~(1 << M1DIpin);
				}
				M1ENPORT |= (1 << M1ENpin); // Despues encendemos el motor
			}
			else
			{
				M1ENPORT &= ~(1 << M1ENpin);
			} 
            break;
        case M2: 
            if(estado == ON)
            {
	            if (giro == DERECHA)    // Establecemos la direccion (1=drcha. 0=izqda.)
	            {
		            M2DIPORT |= (1 << M2DIpin);
	            }
	            else
	            {
		            M2DIPORT &= ~(1 << M2DIpin);
	            }
	            M2ENPORT |= (1 << M2ENpin); // Despues encendemos el motor
            }
            else
            {
	            M2ENPORT &= ~(1 << M2ENpin);
            }
            break;
        case M3: 
            if(estado == ON)
            {
	            if (giro == DERECHA)    // Establecemos la direccion (1=drcha. 0=izqda.)
	            {
		            M3DIPORT |= (1 << M3DIpin);
	            }
	            else
	            {
		            M3DIPORT &= ~(1 << M3DIpin);
	            }
	            M3ENPORT |= (1 << M3ENpin); // Despues encendemos el motor
            }
            else
            {
	            M3ENPORT &= ~(1 << M3ENpin);
            }
            break;
        case M4: 
		
            if(estado == ON)
            {
	            if (giro == DERECHA)    // Establecemos la direccion (1=drcha. 0=izqda.)
	            {
		            M4DIPORT |= (1 << M5DIpin);
	            }
	            else
	            {
		            M4DIPORT &= ~(1 << M5DIpin);
	            }
	            M4ENPORT |= (1 << M4ENpin); // Despues encendemos el motor
            }
            else
            {
	            M4ENPORT &= ~(1 << M4ENpin);
            }
            break;
        case M5: 
            if(estado == ON)
            {
	            if (giro == DERECHA)    // Establecemos la direccion (1=drcha. 0=izqda.)
	            {
		            M5DIPORT |= (1 << M5DIpin);
	            }
	            else
	            {
		            M5DIPORT &= ~(1 << M5DIpin);
	            }
	            //M5ENPORT |= (1 << M5ENpin); // Despues encendemos el motor
				//M5PWMPORT |= (1 << M5PWMpin); // modo PWM
				OCR5B=2000;
            }
            else
            {
	            //M5ENPORT &= ~(1 << M5ENpin);
				//M5PWMPORT &= ~(1 << M5PWMpin); // modo PWM
				OCR5B=0;
            }
            break;
        case M6: 
            if(estado == ON)
            {
	            if (giro == DERECHA)    // Establecemos la direccion (1=drcha. 0=izqda.)
	            {
		            M6DIPORT |= (1 << M6DIpin);
	            }
	            else
	            {
		            M6DIPORT &= ~(1 << M6DIpin);
	            }
	            M6ENPORT |= (1 << M6ENpin); // Despues encendemos el motor
            }
            else
            {
	            M6ENPORT &= ~(1 << M6ENpin);
            }
            break;
    }

}

/***************************************
LUCES
    luz    -> {L1, L4, L5}
    estado -> {ON, OFF}                
ej. Luz(L1, ON);
***************************************/
void luz(luz_t luz, status_t estado)
{   
    char lPort, lPin;
    switch (luz)
    {
    case L1:
        lPort = L1PORT;
        lPin  = L1pin;
        break;
    case L4:
        lPort = L4PORT;
        lPin  = L4pin;
        break;
    case L5:
        lPort = L5PORT;
        lPin  = L5pin;
        break;
    }

    if(estado == ON)
    {
        lPort |= (1 << lPin);
    }
    else
    {
        lPort &= ~(1 << lPin);
    }
}

void semaforo(status_luz_t color)
{
    if (color == GREEN)
    {
        Luz(L4,ON);
        Luz(L5,OFF);
    }
    else if (color == RED)
    {
        Luz(L5,ON);
        Luz(L4,OFF); 
    }
}