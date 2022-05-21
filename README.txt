washTunnel Project

Gestión de la maqueta del tunel de lavado

-->Módulo de entrada: barrera, sensores ópticos SO1 y SO2

    El funcionamiento del módulo de entrada se gestiona en el documento entrada.c, y tiene relacion con otros módulos y funciones:

    Indirectamente:
        gestionCinta();     [cinta.c]
        parpadeo();         [luz.c]
    
    Directamente:
        gestionLV();        [lavado_vertical.c]
        motor();            [actuators.c]

    El funcionamiento de la barrera se divide en dos comportamientos: 
    - El comportamiento durante la secuencia de inicialización, en el que la barrera bajará a no ser que un vehículo se lo impida, en cuyo caso pausará la bajada por seguridad. Hasta que la barrera no haya bajado hasta el final, no se dará por finalizada la secuencia de inicialización.
    - El modo de funcionamiento normal, en el que la barrera permitirá la entrada de vehículos siempre y cuando la estación de lavado vertical se haya desactivado tras acabar con el vehículo anterior. Si un vehículo solicita la entrada (corta SO1) antes de haber terminado el funcionamiento del lavado vertical, la barrera esperará hasta que el lavado vertical haya finalizado para permitir la entrada.

    Sobre la relación entre el módulo de entrada y el lavado vertical:
    - El encendido y apagado del lavado vertical se efectúa mediante una gestión temporal, debido a que el lavado vertical (LV) carece de sensores. Para efectuar un control robusto de la activación y desactivación del LV, es necesario supeditarlos a la detección de la presencia de los vehículos por parte de sensores en otros módulos. De esta forma podemos evitar encendidos innecesarios (falsas entradas), y apagar antes el LV ante rectificaciones de los clientes (salen marcha atrás antes de ser enganchados por la cinta).
    - El tamaño de los vehículos es variable, y por lo tanto el tiempo que permanece encendido el LV también debe serlo. Para tener en cuenta esta variabilidad, no se ha prefijado un tiempo de funcionamiento, sino que se han fijado los tiempos de encendido y apagado de los rodillos del LV, que serán invariables porque la velocidad de arrastre de la cinta es constante. El tiempo de encendido se ha establecido empíricamente como el tiempo en segundos que tarda un vehículo en llegar al LV desde que se le permite la entrada al tunel de lavado. Si transcurrido ese tiempo, que llamaremos T_LV, el sensor de entrada (SO1) sigue detectando, entonces la entrada resulta ser una entrada normal de vehículo, en caso contrario sería una rectificación y se procedería a un apagado anticipado de los rodillos para ahorrar energía. Por otro lado el tiempo de apagado, que llamaremos TLV_Off, es el tiempo transcurrido desde que la parte trasera del vehículo abandona el sensor de entrada (SO1) hasta que abandona los rodillos del LV.

        Limitaciones y líneas futuras de la relacion entre la entrada y el lavado vertical:
        - La principal limitación del diseño de éstos módulos tiene que ver con el tamaño de los vehículos. Como se desprende de la explicación anterior, si un vehículo no es los suficientemente largo como para seguir cortando el sensor de entrada (SO1) depués de transcurridos T_LV segundos, su entrada real será tomada como rectificación (salida marcha atrás) y los rodillos se apagarán prematuramente. Por esta razón, el diseño está limitado a vehículos que guarden la misma escala que con los que se ha probado y para los cuales se han diseñado todos los módulos.
        - En cuanto a las líneas futuras, la principal característica que no se ha podido implementar a tiempo debido a los problemas experimentados en el lavado horizontal (ruido en sensores debido al PWM), es la consulta del estado del LH para mejorar el apagado del LV ante rectificaciones de los clientes. Actualmente, la forma de comprobar si un cliente ha rectificado es consultar el estado del sensor de entrada (SO1) en el momento de encendido de los rodillos del LV. Si no detecta vehículo, se toma como rectificación. Veamos ahora el principal error que puede ocurrir:
            1.- Si el vehículo rectifica después del encendido del LV: para detectar esta situación, sería necesario consultar el estado del LH, si pasado cierto tiempo desde la entrada en el túnel, el LH sigue sin activarse (se activa por sensores, no por tiempo) entonces podemos tomarlo como una rectificación tardía del cliente. En este caso, el funcionamiento adecuado sería levantar la barrera para permitir la salida hacia atrás del cliente arrepentido y apagar de inmediato el LV.
