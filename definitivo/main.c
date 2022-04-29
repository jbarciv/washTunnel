/* ----------------------------------------------------------------------------
 * aquí se define el bucle principal, quizás también el setup
 * 
 * 
 * 
 * 
 * -------------------------------------------------------------------------- */

#include "commonstuff.h"


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