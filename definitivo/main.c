/* ----------------------------------------------------------------------------
 * aquí se define el bucle principal, quizás también el setup
 * 
 * 
 * 
 * 
 * -------------------------------------------------------------------------- */

#include "commonstuff.h"

/********************* Variables globales ***********************************/
miliseconds_t   miliseconds = 0;
seconds_t       seconds = 0;
bool            SO1_f;          // estado real(filtrado) del sensor SO1

void motorSetup()
{
    DDRL |= 0xFF;
    DDRD |= 0xF0;
}


int main(void)
{
    motorSetup();
    
    
    while(1)
    {
    }
}