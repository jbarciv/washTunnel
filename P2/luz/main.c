/* FUNCION PARA LUZ INDICADORA DE ESTADO */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>

int i = 0;
int LUZ = 0;
int modo = 0;		// modo de funcionamiento (0 = standby, 1 = ON)


void setup_timer()
{
	cli();
		TCCR1A = 0b00000000;	// timer 16bits + prescalado 1024
		TCCR1B = 0B00001101;
		OCR1A = 3906;			// por comprobar
		TIMSK1 = 0b00000010;
	sei();
}

ISR(TIMER1_COMPA_vect)
{
	if (modo = 1)	// si queremos que conmute cada 0.5s
	{
		LUZ = !LUZ; 		
	}
	else 
	{
		i++;		// si queremos que cada 10s parpadee
		/* logica parpadeo */
	}
	
}
int main(void)
{
    setup_timer();
    while (1) 
    {
    }
}

