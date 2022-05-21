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

-->Módulo de lavado vertical: rodillos LV, sensores ópticos SO1 y SO2

    El funcionamiento del módulo de LV se gestiona en el documento lavado_vertical.c, y tiene relacion con otros módulos y funciones:

    Indirectamente:
        gestionCinta();     [cinta.c]
        parpadeo();         [luz.c]
    
    Directamente:
        gestionBarrera();   [entrada.c]
        motor();            [actuators.c]

    El funcionamiento del LV se divide en dos comportamientos: 
    - El comportamiento durante la secuencia de inicialización apaga los rodillos si éstos estaban encendidos.
    - Durante el funcionamiento normal, los rodillos se activarán pasado un cierto tiempo (T_LV) desde que un vehículo entró en el túnel. Se apagarán cuando haya pasado un cierto tiempo (TLV_Off) desde que la parte trasera del vehículo abandona el sensor de entrada (SO1).

-->Módulo de lavado horizontal (LH) y secado: rodillo LH, motores de LH y secado, sensores ópticos SO3, SO4, SO5, SO7, SO8 y SO9

    El funcionamiento del módulo de LH se gestiona en el documento lavado_horizontal.c y el de secado(análogo al de LH) en secado_horizontal.c, y tiene relacion con otros módulos y funciones:

    Indirectamente:
        gestionCinta();     [cinta.c]
        carLeavingTunnel;   [salida.c]
        parpadeo();         [luz.c]
    
    Directamente:
        motor();            [actuators.c]

    El funcionamiento del LH y el del secado son análogos y se dividen en dos comportamientos: 
    - El comportamiento durante la secuencia de inicialización apaga los rodillos si éstos estaban encendidos. Además, baja los módulos (LH y secado) hasta que tocan el fin de carrera inferior y a partir de ahí los elevan hasta llegar a su posición de reposo a la espera del primer vehículo.
    - Durante el funcionamiento normal, el LH y el secado son independientes del funcionamiento del resto del túnel y siempre están activos, de esta forma pueden reaccionar ante cualquier imprevisto evitando el choque con un vehículo. Después de dejar de trabajar sobre un vehículo, los módulos vuelven de forma independiente a su posición de reposo siguiendo la misma rutina que durante la secuencia de inicialización.

-->Módulo de salida: motor de la cinta, sensores ópticos SO10, SO11 y SO12.

    El funcionamiento del módulo de salida se gestiona en el documento salida.c, y tiene relacion con otros módulos y funciones:

    Indirectamente:
        gestionCinta();     [cinta.c]
        parpadeo();         [luz.c]
    
    Directamente:
        semaforo();         [actuators.c]

    El funcionamiento de la salida se divide en dos comportamientos: 
    - El comportamiento durante la secuencia de inicialización permite la salida de un vehículo que corte cualquiera de los tres sensores de la salida (SO10, SO11 y SO12). Para ello deja el semáforo en verde hasta que el vehículo abandona la salida, entonces el semáforo cambia a rojo y se da por concluida la secuencia de inicialización.
    - Durante el funcionamiento normal, el semáforo estará normalmete en rojo, cambiando a verde cuando los dos primeros sensores (SO10 y SO11) detectan un vehículo, y solo volverá a rojo cuando se experimente un flanco de subida en el último sensor (SO12 deja de detectar) y además el sensor central (SO11) no detecte tampoco, pues si detecta un vehículo, se considerará falsa salida.

-->Luz y cinta: motor de la cinta y luz de funcionamiento.

    Tanto la luz de funcionamiento como la cinta se gestionan en el timer4 configurado como base de tiempos de medio segundo. Su funcionamiento global los relaciona indirectamente con todos los módulos.

    Indirectamente:
        gestionBarrera();   [entrada.c]
        gestionLV();        [lavado_vertical.c]
        gestionLH();        [lavado_horizontal.c]
        gestionSH();        [secado_horizontal.c]
        gestionCinta();     [cinta.c]
        carLeavingTunnel(); [salida.c]
    
    Directamente:
        luz();              [actuators.c]

    El funcionamiento de la luz se divide en dos comportamientos: 
    - El comportamiento cuando el tunel está vacío es el correspondiente al modo inactivo: un parpadeo cada 10 segundos.
    - Su funcionamiento cuando hay alguna estación en funcionamiento es un parpadeo de 1Hz. Para comprobar si alguna estación está en funcionamiento, se consulta el estado de las banderas de cada módulo así como de los sensores de la salida. Si alguna bandera está levantada (a 1) o si alguno de los sensores (SO10, SO11 o SO12) está detectando la presencia de un vehículo, entonces la luz de funcionamiento estará en modo activo.
