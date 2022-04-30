/* ----------------------------------------------------------------------------
 *
 * 
 * -------------------------------------------------------------------------- */


// #include <avr/io.h>
// #include <avr/interrupt.h>


#ifndef LAVADERO_H_
#define LAVADERO_H_


#define BOTON_DELAY     50
#define SENSOR_DELAY    20
#define ANTIREB_TIME    125     // Con un preescalado de 64 --> 125 periodos es 1 ms
#define REAL_TIME       31250      // Con un preescalado de 256 --> 31250 periodos es 1 s
#define T_ENTRE_COCHES  5     // Dejamos 5 segundos al menos entre un coche y otro


typedef enum {false,true}               bool;
/* Etiquetas para los motores */
typedef enum {M1, M2, M3, M4, M5, M6}   motor_t;
typedef enum {ON, OFF}                  status_t;
typedef enum {DERECHA, IZQUIERDA}       direccion_t;
/* Etiquetas para los sensores */
typedef enum {SO1, SO2, SO3, SO4, SO5, 
              SO6, SO7, SO8, SO9, SO10,
              SO11,SW1, SW2, SW3, SW4} sensor_t;
/*Etiquetas para los LEDs*/
typedef enum {L1, L4, L5}               luz_t;
typedef enum {RED,GREEN}                estado_luz_t;
/*Etiquetas para la barrera*/
typedef enum {UP,DOWN}                  barrier_status_t;
/* Etiquetas para los 'estados' del tunel de lavado*/
typedef enum 
{
    STARTING,   // Inicializando el sistema
    WAITING,    // Estado de reposo, no se hace nada
    BUSY,       // Estado de tunel funcionando
    EMERGENCY   // Estado de emergencia
}                                       mode_t;

// Motor  M1 -> BARRERA ENTRADA {PL0, PL1}
#define M1ENPORT        PORTL
#define M1ENpin         0
#define M1DIPORT        PORTL
#define M1DIpin         1
// Motor  M2 -> LAVADO VERTICAL {PL2, PL3}
#define M2ENPORT        PORTL
#define M2ENpin         2
#define M2DIPORT        PORTL
#define M2DIpin         3
// Motor  M3 -> LAVADO HORIZONTAL {PL4, PL5}
#define M3ENPORT        PORTL
#define M3ENpin         4
#define M3DIPORT        PORTL
#define M3DIpin         5
// Motor  M4 -> GIRO LAVADO HORIZONTAL {PL6, PL7}
#define M4ENPORT        PORTL
#define M4ENpin         6
#define M4DIPORT        PORTL
#define M4DIpin         7
// Motor  M5 -> SECADO {PD4, PD5}  
#define M5ENPORT        PORTD
#define M5ENpin         4
#define M5DIPORT        PORTD
#define M5DIpin         5
// Motor  M6 -> CINTA ARRASTRE {PD6, PD7}
#define M6ENPORT        PORTD
#define M6ENpin         6
#define M6DIPORT        PORTD
#define M6DIpin         7

/* Etiquetas para los sensores opticos */
#define SO1PIN          PIND   // PD1 -> Sensor de entrada "abajo"
#define SO1pin          1
#define SO2PIN          PINK   // PK1 -> Sensor de entrada barrera
#define SO2pin          1
#define SO3PIN          PINK   // PK2 -> Sensor lavado horiz. izqda.
#define SO3pin          2   
#define SO4PIN          PINK   // PK3 -> Sensor lavado horiz. centro
#define SO4pin          3   
#define SO5PIN          PINK   // PK4 -> Sensor lavado horiz. drcha.
#define SO5pin          4   
#define SO6PIN          PINK   // PK5 -> ¡!sin utilidad definida
#define SO6pin          5   
#define SO7PIN          PINB   // PB0 -> Sensor secado izqda.
#define SO7pin          0   
#define SO8PIN          PINB   // PB1 -> Sensor secado centro.
#define SO8pin          1   
#define SO9PIN          PINB   // PB2 -> Sensor secado drcha.
#define SO9pin          2   
#define SO10PIN         PIND   // PD2 -> Sensor de "aviso" de salida
#define SO10pin         2  
#define SO11PIN         PINB   // PB4 -> ¡!sin utilidad definida
#define SO11pin         4 
#define SO12PIN         PINB   // PB5 -> Sensor de salida "definitiva"
#define SO12pin         5

/* Etiquetas para los sensores mecanicos (microinterruptores) */
#define SW1             PIND    // PD0 -> Sensor apertura-cierre de barrera
#define SW2             PINK    // PK6 -> Sensor finales de carrera lavado horiz.
#define SW3             PINK    // PK7 -> Sensor finales de carrera secado
#define SW4             PIND    // PD3 -> Sensor/botón para de emergencia
#define emergency_b     SW4

/* Etiquetas para los LEDs */
#define L1              PINB    // PB3 -> LED L1: WAITING or BUSY
#define L4              PINB    // PB6 -> LED L4: semaforo verde
#define L5              PINB    // PB7 -> LED L5: semaforo rojo
// Puertos para los LEDs
#define L1PORT          PORTB
#define L1pin           3
#define L4PORT          PORTB
#define L4pin           6
#define L5PORT          PORTB
#define L5pin           7

#define SEMAFORO_PORT   PORTB
#define GREEN_pin       6
#define RED_pin         7



// #define enableMotor() M2ENPORT |= 0x02
// #define disableMotor() M2ENPORT &= 0xFD
// #define isMotorEnabled() M2EN
// #define enableLedL3() L3PORT |= 0x04
// #define disableLedL3() L3PORT &= 0xFB
// #define isL3Enabled() L3
// #define enableLedL4() L4PORT |= 0x10
// #define disableLedL4() L4PORT &= 0xEF
// #define isL4Enabled() L4

// uint8_t isSW1pressed();
// uint8_t isSW3pressed();

// void setupAtraccion();
	
// void setMotorDirection(direccion_t direction);

// extern direccion_t getMotorDirection();

// extern void toggleMotorDirection();

// void startAtraccion();

// extern void emergencyBrake();

// void setOnStatusChangedListener(void (* foo) (status_t) );

// void setCurrentStatus(status_t newStatus);

// status_t getCurrentStatus();

#define ENTRY_MOD   0
#define LV_MOD      1
#define LH_MOD      2
#define DRYER_MOD   3
#define LIGHT_MOD   4
#define BELT_MOD    5
#define OUT_MOD     6

/*********************Variables globales***********************************/

char ready = 0b00000000; //Variable encargada de registrar el proceso de STARTING del sistema


#endif /* LAVADERO_H_ */