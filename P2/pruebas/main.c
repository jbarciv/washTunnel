/* FUNCIONAMIENTO BARRERA DE ENTRADA */ 

#include "commonstuff.h"

void setup()
{
	cli();
	SO1 = 0x00;
	M1ENDDR = 0xFF;
	M1DIDDR= 0xFF;
	EICRA = 0b00000010;
	
	
	
	sei();
}
ISR(SO1ON)
{
	
}

int main(void)
{
	
    /* Replace with your application code */
    while (1) 
    {
		
    }
}
