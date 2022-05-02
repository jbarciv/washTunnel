/* ----------------------------------------------------------------------------
CONTROL DEL HARDWARE - PROTOTIPO DE FUNCIONES
 *  - MOTOR
 *  - LUZ
 * 
 * DATE: 02/05/2022
 * AUTOR: Josep María Barberá Civera
 * -------------------------------------------------------------------------- */


#include "commonstuff.h"

#ifndef ACTUATORS_H_
#define ACTUATORS_H_

void motor(motor_t, status_t, direccion_t);
void luz(luz_t, status_t);
void semaforo (status_luz_t);                   // CREO QUE DEBE MOVERSE A OTRO SITIO (?)

// void moveCinta();                            // CREO QUE DEBEN MOVERSE A OTRO SITIO (?)
// void stopCinta();
// void gestionCinta();
// void tunnelGotBusy();

#endif /* ACTUATORS_H_ */