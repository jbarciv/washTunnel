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

#endif /* CONTROL_H_ */