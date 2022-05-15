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
                if (giro == DERECHA)        // Establecemos la direccion (1=drcha. 0=izqda.)
                {
                    M1DIPORT |= (1 << M1DIpin);
                }
                else 
                {
                    M1DIPORT &= ~(1 << M1DIpin);
                }
                M1ENPORT |= (1 << M1ENpin);  // Despues encendemos el motor
            } 
            else
            {
                M1ENPORT &= ~(1 << M1ENpin);
            }
            break;
        case M2: 
            if(estado == ON)
            {   
                if (giro == DERECHA)        
                {
                    M2DIPORT |= (1 << M2DIpin);
                }
                else 
                {
                    M2DIPORT &= ~(1 << M2DIpin);
                }
                M2ENPORT |= (1 << M2ENpin);  
            } 
            else
            {
                M2ENPORT &= ~(1 << M2ENpin);
            }
            break;
        case M3: 
            if(estado == ON)
            {   
                if (giro == DERECHA)        
                {
                    M3DIPORT |= (1 << M3DIpin);
                }
                else 
                {
                    M3DIPORT &= ~(1 << M3DIpin);
                }
                M3ENPORT |= (1 << M3ENpin);  
            } 
            else
            {
                M3ENPORT &= ~(1 << M3ENpin);
            }
            break;
        case M4: 
            if(estado == ON)
            {   
                if (giro == DERECHA)        
                {
                    M4DIPORT |= (1 << M4DIpin);
                }
                else 
                {
                    M4DIPORT &= ~(1 << M4DIpin);
                }
                M4ENPORT |= (1 << M4ENpin);  
            } 
            else
            {
                M4ENPORT &= ~(1 << M4ENpin);
            }
            break;
        case M5: 
            if(estado == ON)
            {   
                if (giro == DERECHA)        
                {
                    M5DIPORT |= (1 << M5DIpin);
                }
                else 
                {
                    M5DIPORT &= ~(1 << M5DIpin);
                }
                //M5ENPORT |= (1 << M5ENpin); 
                OCR5B=2000; 
            } 
            else
            {
                //M5ENPORT &= ~(1 << M5ENpin);
                OCR5B=0;
            }
            break;
        case M6: 
            if(estado == ON)
            {   
                if (giro == DERECHA)        
                {
                    M6DIPORT |= (1 << M6DIpin);
                }
                else 
                {
                    M6DIPORT &= ~(1 << M6DIpin);
                }
                M6ENPORT |= (1 << M6ENpin);  
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
    switch (luz)
    {
    case L1:
        if(estado == ON)
        {
            L1PORT |= (1 << L1pin);
        }
        else
        {
            L1PORT &= ~(1 << L1pin);
        }
        break;
    case L4:
        if(estado == ON)
        {
            L4PORT |= (1 << L4pin);
        }
        else
        {
            L4PORT &= ~(1 << L4pin);
        }
        break;
    case L5:
        if(estado == ON)
        {
            L5PORT |= (1 << L5pin);
        }
        else
        {
            L5PORT &= ~(1 << L5pin);
        }
        break;
    }
}

void semaforo(status_luz_t color)
{
    if (color == GREEN)
    {
        luz(L4,ON);
        luz(L5,OFF);
    }
    else if (color == RED)
    {
        luz(L5,ON);
        luz(L4,OFF); 
    }
}