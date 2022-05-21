void timerSetup()
{
    // setup del contador 3
    cli ();
    TCCR3B |= (1<<WGM32);           // Modo ctc
    TCCR3B |= (1<<CS31)|(1<<CS30);  // Preescalado clk/64 (periodo de 8 uS)
    OCR3A = ANTIREB_TIME;           // Contamos COUNTER_TIME periodos (= 1 ms)
    TIMSK3 |= (1<<OCIE3A);          // Habilitamos la interrupcion por compare match
    // setup del contador 4
    TCCR4B |= (1<<WGM42);           // Modo ctc
    TCCR4B |= (1<<CS42);            // Preescalado clk/256 (periodo de 32 uS)
    OCR4A = REAL_TIME;              // Contamos REAL_TIME periodos (=0.5 s)
    TIMSK4 |= (1<<OCIE4A);          // Habilitamos la interrupcion por compare match
    sei();
}