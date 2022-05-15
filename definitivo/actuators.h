/* ----------------------------------------------------------------------------
 *              CONTROL DEL HARDWARE - PROTOTIPO DE FUNCIONES
 *  - MOTOR
 *  - LUZ
 * 
 * DATE: 02/05/2022
 * AUTHOR: Josep María Barberá Civera
 * -------------------------------------------------------------------------- */


#include "commonstuff.h"

#ifndef ACTUATORS_H_
#define ACTUATORS_H_

void motor(motor_t, status_t, direccion_t);
void luz(luz_t, status_t);
void semaforo (status_luz_t);               

#endif /* ACTUATORS_H_ */