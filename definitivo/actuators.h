/* ----------------------------------------------------------------------------
 * aquí se define el prototipo de las funciones para control
 * 
 * 
 * 
 * 
 * -------------------------------------------------------------------------- */


#include "commonstuff.h"

#ifndef ACTUATORS_H_
#define ACTUATORS_H_

void Motor(motor_t, status_t, direccion_t);
void Luz(luz_t, status_t);
void Semaforo (status_luz_t);

// void moveCinta();
// void stopCinta();
// void gestionCinta();

// void tunnelGotBusy();

#endif /* ACTUATORS_H_ */