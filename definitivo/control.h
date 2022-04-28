/* ----------------------------------------------------------------------------
 * aquí se define el prototipo de las funciones para control
 * 
 * 
 * 
 * 
 * -------------------------------------------------------------------------- */


#include <commonstuff.h>

#ifndef CONTROL_H_
#define CONTROL_H_

void Motor(motor_t, status_t, direccion_t);
status_t Sensor(sensor_t);
void moveCinta();
void stopCinta();
void gestionCinta();
void Semaforo (luz_t);
void tunnelGotBusy();

#endif /* CONTROL_H_ */