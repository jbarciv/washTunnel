/* ----------------------------------------------------------------------------
 *
 * 
 * -------------------------------------------------------------------------- */


#include <avr/io.h>
#include <avr/interrupt.h>



#ifndef LAVADERO_H_
#define LAVADERO_H_

// #define LIMITE_CUENTA_L3 1221 // 10 segundos
// #define LIMITE_CUENTA_ATRACCION 10990 // 45 segundos
// #define LIMITE_CUENTA_DOS_MINUTOS 14652
// #define LIMITE_CUENTA_MEDIO_SEGUNDO 61
// #define LIMITE_CUENTA_CINCO_SEGUNDOS 610

/* Etiquetas para los motores */
typedef enum {M1, M2, M3, M4, M5, M6} motor_t;
typedef enum {ENCENDIDO, APAGADO} motor_status_t;
typedef enum {DERECHA, IZQUIERDA} direccion_t;
// Motor  M1 -> BARRERA ENTRADA
#define M1ENPORT PORTL  // PL0
#define M1DIPORT PORTL  // PL1
// Motor  M2 -> LAVADO VERTICAL
#define M2ENPORT PORTL  // PL2
#define M2DIPORT PORTL  // PL3
// Motor  M3 -> LAVADO HORIZONTAL
#define M3ENPORT PORTL  // PL4
#define M3DIPORT PORTL  // PL5
// Motor  M4 -> GIRO LAVADO HORIZONTAL
#define M4ENPORT PORTL  // PL6
#define M4DIPORT PORTL  // PL7
// Motor  M5 -> SECADO  
#define M5ENPORT PORTD  // PD4
#define M5DIPORT PORTD  // PD5
// Motor  M6 -> CINTA ARRASTRE
#define M6ENPORT PORTD  // PD6
#define M6DIPORT PORTD  // PD7

/* Etiquetas para los sensores opticos */
#define SO1  (PINK & 0b00000001) // PK0 -> Sensor de entrada "abajo"
#define SO2  (PINK & 0b00000100) // PK1 -> Sensor de entrada barrera
#define SO3  (PINK & 0b00010000) // PK2 -> Sensor lavado horiz. izqda.
#define SO4  (PINK & 0b01000000) // PK3 -> Sensor lavado horiz. centro
#define SO5  (PINK & 0b00000001) // PK4 -> Sensor lavado horiz. drcha.
#define SO6  (PINK & 0b00000100) // PK5 -> ¡!sin utilidad definida
#define SO7  (PINB & 0b00010000) // PB0 -> Sensor secado izqda.
#define SO8  (PINB & 0b01000000) // PB1 -> Sensor secado centro.
#define SO9  (PINB & 0b00000010) // PB2 -> Sensor secado drcha.
#define SO10 (PINB & 0b00001000) // PB3 -> Sensor de "aviso" de salida
#define SO11 (PINB & 0b00100000) // PB4 -> ¡!sin utilidad definida
#define SO12 (PINB & 0b10000000) // PB5 -> Sensor de salida "definitiva"

/* Etiquetas para los sensores mecanicos (microinterruptores) */
#define SW1  (PIND & 0b00000001) // PD0 -> Sensor apertura-cierre de barrera
#define SW2  (PIND & 0b00000100) // PD1 -> Sensor finales de carrera lavado horiz.
#define SW3  (PIND & 0b00010000) // PD2 -> Sensor finales de carrera secado
#define SW4  (PIND & 0b01000000) // PD3 -> Sensor/botón para de emergencia
#define boton_emergencia SW4

/* Etiquetas para los LEDs */
#define L1  (PIN & 0b00000010) // P -> LED L1: WAITING or BUSY
#define L4  (PIN & 0b00001000) // P -> LED L4: semaforo verde
#define L5  (PIN & 0b00100000) // P -> LED L5: semaforo rojo
// Puertos para los LEDs
#define L1PORT PORT
#define L4PORT PORT
#define L5PORT PORT


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