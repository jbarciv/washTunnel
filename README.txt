washTunnel Project

Gestión de la maqueta del tunel de lavado

-->Módulo de entrada: barrera, sensores ópticos SO1 y SO2

    El funcionamiento del módulo de entrada se gestiona en el documento entrada.c, y tiene relacion con otros módulos y funciones:

    Indirectamente:
        gestionCinta();     [cinta.c]
        parpadeo();         [luz.c]
    
    Directamente:
        gestionLV();        [lavado_vertical.c]
    
