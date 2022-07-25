/* ----------------------------------------------------------------------------
 *                           PARADA DE EMERGENCIA * 
 * DATE:    10/05/2022
 * AUTHOR:  Gonzalo Quiros Torres
 *          Josep María Barberá Civera
 * -------------------------------------------------------------------------- */

#include "commonstuff.h"
#include "setup.h"
#include "entrada.h"
#include "luz.h"
#include "cinta.h"
#include "lavado_vertical.h"
#include "lavado_horizontal.h"
#include "secado_horizontal.h"
#include "salida.h"


/********************************************
MICROINTERRUPTOR SW4: parada de emergencia
- Activo por flanco de subida y bajada
********************************************/
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