/* ----------------------------------------------------------------------------
 * Aquí debe ir definido todos los pines y prototipos de funciones
 * 
 * 
 * ¡!: AÚN NO ESTÁ CLARA LA DISTRIBUCIÓN DE PINES... CONFORME NECESITÉIS INTERRUPCIONES
 * PODÉIS IR MODIFICANDO ESTE DOCUMENTO...
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
// Motor  M1 -> DDR# y PORT#
#define M1ENDDR DDRC
#define M1DIDDR DDRC
#define M1ENPORT PORTC
#define M1DIPORT PORTC
// Motor  M2 -> DDR# y PORT#
#define M2ENDDR DDRC
#define M2DIDDR DDRC
#define M2ENPORT PORTC
#define M2DIPORT PORTC
// Motor  M3 -> DDR# y PORT#
#define M3ENDDR DDRA
#define M3DIDDR DDRA
#define M3ENPORT PORTA
#define M3DIPORT PORTA
// Motor  M4 -> DDR# y PORT#
#define M4ENDDR DDRA
#define M4DIDDR DDRA
#define M4ENPORT PORTA
#define M4DIPORT PORTA
// Motor  M5 -> DDR# y PORT#
#define M5ENDDR DDRC
#define M5DIDDR DDRC
#define M5ENPORT PORTC
#define M5DIPORT PORTC
// Motor  M6 -> DDR# y PORT#
#define M6ENDDR DDRC
#define M6DIDDR DDRC
#define M6ENPORT PORTC
#define M6DIPORT PORTC


/* Etiquetas para los sensores opticos */
#define SO1  (PINJ & 0b00000001) // PJ0 -> Sensor de entrada "abajo"
#define SO2  (PINJ & 0b00000100) // PJ2 -> Sensor de entrada barrera
#define SO3  (PINJ & 0b00010000) // PJ4 -> Sensor lavado horiz. izqda.
#define SO4  (PINJ & 0b01000000) // PJ6 -> Sensor lavado horiz. centro
#define SO5  (PINE & 0b00000001) // PE0 -> Sensor lavado horiz. drcha.
#define SO6  (PINE & 0b00000100) // PE2 -> ¡!sin utilidad definida
#define SO7  (PINE & 0b00010000) // PE4 -> Sensor secado izqda.
#define SO8  (PINE & 0b01000000) // PE6 -> Sensor secado centro.
#define SO9  (PINE & 0b00000010) // PE1 -> Sensor secado drcha.
#define SO10 (PINE & 0b00001000) // PE3 -> Sensor de "aviso" de salida
#define SO11 (PINE & 0b00100000) // PE5 -> ¡!sin utilidad definida
#define SO12 (PINE & 0b10000000) // PE7 -> Sensor de salida "definitiva"

// Sensor  SO1 -> DDR# y PORT#
#define SO1DDR DDRJ
#define SO1PORT PORTJ
// Sensor  SO2
#define SO2DDR DDRJ
#define SO2PORT PORTJ
// Sensor  SO3
#define SO3DDR DDRJ
#define SO3PORT PORTJ
// Sensor  SO4
#define SO4DDR DDRJ
#define SO4PORT PORTJ
// Sensor  SO5
#define SO5DDR DDRE
#define SO5PORT PORTE
// Sensor  SO6
#define SO6DDR DDRE
#define SO6PORT PORTE
// Sensor  SO7
#define SO7DDR DDRE
#define SO7PORT PORTE
// Sensor  SO8
#define SO8DDR DDRE
#define SO8PORT PORTE
// Sensor  SO9
#define SO9DDR DDRE
#define SO9PORT PORTE
// Sensor  SO10
#define SO10DDR DDRE
#define SO10PORT PORTE
// Sensor  SO11
#define SO11DDR DDRE
#define SO11PORT PORTE
// Sensor  SO12
#define SO12DDR DDRE
#define SO12PORT PORTE


/* Etiquetas para los sensores mecanicos (microinterruptores) */
#define SW1  (PINA & 0b00000001) // PA0 -> Sensor apertura-cierre de barrera
#define SW2  (PINA & 0b00000100) // PA2 -> Sensor finales de carrera lavado horiz.
#define SW3  (PINA & 0b00010000) // PA4 -> Sensor finales de carrera secado
#define SW4  (PINA & 0b01000000) // PA6 -> Sensor/botón para de emergencia
#define boton_emergencia SW4

// Sensor  SW1 -> DDR# y PORT#
#define SW1DDR DDRA
#define SW1PORT PORTA
// Sensor  SW2
#define SW2DDR DDRA
#define SW2PORT PORTA
// Sensor  SW3
#define SW3DDR DDRA
#define SW3PORT PORTA
// Sensor  SW4
#define SW4DDR DDRA
#define SW4PORT PORTA


/* Etiquetas para los LEDs */
#define L1  (PINJ & 0b00000010) // PJ1 -> LED L1: WAITING or BUSY
#define L4  (PINJ & 0b00001000) // PJ3 -> LED L4: semaforo verde
#define L5  (PINJ & 0b00100000) // PJ5 -> LED L5: semaforo rojo

// LED L1 -> DDR# y PORT#
#define L3DDR DDRJ
#define L3PORT PORTJ
// LED L4
#define L4DDR DDRJ
#define L4PORT PORTJ
// LED L5
#define L5DDR DDRJ
#define L5PORT PORTJ


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