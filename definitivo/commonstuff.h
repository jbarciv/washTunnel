/* ----------------------------------------------------------------------------
 *
 * 
 * -------------------------------------------------------------------------- */


#include <avr/io.h>
#include <avr/interrupt.h>



#ifndef LAVADERO_H_
#define LAVADERO_H_

#define DELAY_BOTON 50
#define DELAY_SENSOR 20
#define ANTIREB_TIME 125     // Con un preescalado de 64 --> 125 periodos es 1 ms
#define REAL_TIME 31250      // Con un preescalado de 256 --> 31250 periodos es 1 s
#define T_ENTRE_COCHES 5     // Dejamos 5 segundos al menos entre un coche y otro

typedef enum {ON, OFF} status_t;
/* Etiquetas para los motores */
typedef enum {M1, M2, M3, M4, M5, M6} motor_t;
typedef enum {DERECHA, IZQUIERDA} direccion_t;
/* Etiquetas para los sensores */
typedef enum {SO1, SO2, SO3, SO4, SO5, 
              SO6, SO7, SO8, SO9, SO10,
              SO11, SW1, SW2, SW3, SW4} sensor_t;

// Motor  M1 -> BARRERA ENTRADA {PL0, PL1}
#define M1ENPORT PORTL
#define M1ENpin 0
#define M1DIPORT PORTL
#define M1DIpin 1
// Motor  M2 -> LAVADO VERTICAL {PL2, PL3}
#define M2ENPORT PORTL
#define M2ENpin 2
#define M2DIPORT PORTL
#define M2DIpin 3
// Motor  M3 -> LAVADO HORIZONTAL
#define M3ENPORT PORTL
#define M3ENpin 4
#define M3DIPORT PORTL
#define M3DIpin 5
// Motor  M4 -> GIRO LAVADO HORIZONTAL
#define M4ENPORT PORTL
#define M4ENpin 6
#define M4DIPORT PORTL
#define M4DIpin 7
// Motor  M5 -> SECADO  
#define M5ENPORT PORTD
#define M5ENpin 4
#define M5DIPORT PORTD
#define M5DIpin 5
// Motor  M6 -> CINTA ARRASTRE
#define M6ENPORT PORTD
#define M6ENpin 6
#define M6DIPORT PORTD
#define M6DIpin 7

/* Etiquetas para los sensores opticos */
#define SO1PIN  PINK    // PK0 -> Sensor de entrada "abajo"
#define SO1pin  1
#define SO2PIN  PINK    // PK1 -> Sensor de entrada barrera
#define SO2pin  2
#define SO3PIN  PINK    // PK2 -> Sensor lavado horiz. izqda.
#define SO3pin  3   
#define SO4PIN  PINK    // PK3 -> Sensor lavado horiz. centro
#define SO4pin  4   
#define SO5PIN  PINK    // PK4 -> Sensor lavado horiz. drcha.
#define SO5pin  5   
#define SO6PIN  PINK    // PK5 -> ¡!sin utilidad definida
#define SO6pin  6   
#define SO7PIN  PINB    // PB0 -> Sensor secado izqda.
#define SO7pin  1   
#define SO8PIN  PINB    // PB1 -> Sensor secado centro.
#define SO8pin  2   
#define SO9PIN  PINB    // PB2 -> Sensor secado drcha.
#define SO9pin  3   
#define SO10PIN PINB    // PB3 -> Sensor de "aviso" de salida
#define SO10pin 4  
#define SO11PIN PINB    // PB4 -> ¡!sin utilidad definida
#define SO11pin 5  
#define SO12PIN PINB    // PB5 -> Sensor de salida "definitiva"
#define SO12pin 6

/* Etiquetas para los sensores mecanicos (microinterruptores) */
#define SW1  (PIND & 0b00000001) // PD0 -> Sensor apertura-cierre de barrera
#define SW2  (PIND & 0b00000100) // PD1 -> Sensor finales de carrera lavado horiz.
#define SW3  (PIND & 0b00010000) // PD2 -> Sensor finales de carrera secado
#define SW4  (PIND & 0b01000000) // PD3 -> Sensor/botón para de emergencia
#define boton_emergencia SW4

/* Etiquetas para los LEDs */
#define L1  (PIND & 0b00000010) // PD2 -> LED L1: WAITING or BUSY
#define L4  (PINB & 0b00001000) // PB6 -> LED L4: semaforo verde
#define L5  (PINB & 0b00100000) // PB7 -> LED L5: semaforo rojo
// Puertos para los LEDs
#define L1PORT PORTD
#define L4PORT PORTB
#define L5PORT PORTB


/* Etiquetas para los 'estados' del tunel de lavado*/
typedef enum 
{
    STARTING,   // Inicializando el sistema
    WAITING,    // Estado de reposo, no se hace nada
    BUSY,       // Estado de tunel funcionando
    EMERGENCY   // Estado de emergencia
} status_t;

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

#endif /* LAVADERO_H_ */