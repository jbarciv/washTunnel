/*
Esta función será llamada iterativamente por el bucle principal del programa. Es la función general
que engloba a todas las demás y gestiona los estados de funcionamiento del sistema. Se compondrá de
las siguientes funciones, que gestionarán cada una un módulo concreto.

    barrierControl()    -->Bandera de funcionamiento 
                        -->Estados de operación
                                - STARTING
                                - WAITING  (+) 
                                - BUSY     (+)    
                                - EMERGENCY
    
    lavadoVertical()    -->Bandera de funcionamiento
                                - bool LV = (true/false)
                        -->Estados de operación
                                - STARTING
                                - WAITING  (+) 
                                - BUSY     (+)    
                                - EMERGENCY
    
    lavadoHorizontal()  -->Bandera de funcionamiento
                                - bool LH = (true/false)
                        -->Estados de operación
                                - STARTING
                                - WAITING  (+) 
                                - BUSY     (+)    
                                - EMERGENCY

    secado()            -->Bandera de funcionamiento
                                - bool secado = (true/false)
                        -->Estados de operación
                                - STARTING
                                - WAITING  (+) 
                                - BUSY     (+)      
                                - EMERGENCY

    lightControl()      -->Bandera de funcionamiento
                                - no tiene
                        -->Estados de operación
                                - STARTING (+)
                                - WAITING  (+)
                                - BUSY    
                                - EMERGENCY

    gestionCinta()      -->Bandera de funcionamiento
                                - bool cinta = (true/false)
                        -->Estados de operación
                                - STARTING (+)
                                - WAITING  (+)
                                - BUSY    
                                - EMERGENCY
    
    carLeavingTunnel()  -->Bandera de funcionamiento
                                - bool secado = (true/false)
                        -->Estados de operación
                                - STARTING (+)
                                - WAITING  (+)
                                - BUSY    
                                - EMERGENCY

    (+) == estados idénticos, es decir, hacen lo mismo.

*/

void gestion()
{

    if (ready != 0b1111111) //un 1 por cada modulo/función
    {
        barrierControl(STARTING);
        lavadoVertical(STARTING);
        lavadoHorzontal(STARTING);
        secado(STARTING);
        lightControl(STARTING);
        gestionCinta(STARTING);
        carLeavingTunnel(STARTING);
    }
    
}
