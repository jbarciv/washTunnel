



#include "commonstuff.h"
#include "setup.h"
#include "entrada.h"
#include "luz.h"
#include "cinta.h"
#include "lavado_vertical.h"
#include "lavado_horizontal.h"
#include "secado.h"
#include "salida.h"

/********************************************
MICROINTERRUPTOR SW4: parada de emergencia
- Activo por flanco de subida y bajada
********************************************/
ISR(INT3_vect) 
{   
    while (1)
    {
        gestionBarrera(EMERGENCY);
        gestionCinta(EMERGENCY);
        
    }
    
}