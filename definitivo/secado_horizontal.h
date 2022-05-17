/* ----------------------------------------------------------------------------
 *                       CONTROL DEL LAVADO HORIZONTAL
 * 
 * DATE:    12/05/2022
 * AUTHOR:  Mario Gómez Pozo
 *          Juan Galvañ Hernando
 * -------------------------------------------------------------------------- */

#include "commonstuff.h"

#ifndef SECADO_HORIZONTAL_H_
#define SECADO_HORIZONTAL_H_

void secado_horizontal_ISR();
void secado_horizontal_CP();
void gestionSH(mode_t modo);

#endif