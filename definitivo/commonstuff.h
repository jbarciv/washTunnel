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
#define M1ENPORT PORT           //no faltan los DDR?
#define M1DIPORT PORT
// Motor  M2 -> DDR# y PORT#
#define M2ENPORT PORT
#define M2DIPORT PORT
// Motor  M3 -> DDR# y PORT# 
#define M3ENPORT PORT
#define M3DIPORT PORT
// Motor  M4 -> DDR# y PORT#
#define M4ENPORT PORT
#define M4DIPORT PORT
// Motor  M5 -> DDR# y PORT#
#define M5ENPORT PORT
#define M5DIPORT PORT
// Motor  M6 -> DDR# y PORT#
#define M6ENPORT PORT
#define M6DIPORT PORT

/* Etiquetas para los sensores opticos */
#define SO1  (PIND & 0b00000001) // PD0 -> Sensor de entrada "abajo"
#define SO2  (PIN & 0b00000100) // P -> Sensor de entrada barrera
#define SO3  (PIN & 0b00010000) // P -> Sensor lavado horiz. izqda.
#define SO4  (PIN & 0b01000000) // P -> Sensor lavado horiz. centro
#define SO5  (PIN & 0b00000001) // P -> Sensor lavado horiz. drcha.
#define SO6  (PIN & 0b00000100) // P -> ¡!sin utilidad definida
#define SO7  (PIN & 0b00010000) // P -> Sensor secado izqda.
#define SO8  (PIN & 0b01000000) // P -> Sensor secado centro.
#define SO9  (PIN & 0b00000010) // P -> Sensor secado drcha.
#define SO10 (PIN & 0b00001000) // P -> Sensor de "aviso" de salida
#define SO11 (PIN & 0b00100000) // P -> ¡!sin utilidad definida
#define SO12 (PIN & 0b10000000) // P -> Sensor de salida "definitiva"

/* Etiquetas para los sensores mecanicos (microinterruptores) */
#define SW1  (PIN & 0b00000001) // P -> Sensor apertura-cierre de barrera
#define SW2  (PIN & 0b00000100) // P -> Sensor finales de carrera lavado horiz.
#define SW3  (PIN & 0b00010000) // P -> Sensor finales de carrera secado
#define SW4  (PIN & 0b01000000) // P -> Sensor/botón para de emergencia
#define boton_emergencia SW4

/* Etiquetas para los LEDs */
#define L1  (PIN & 0b00000010) // P -> LED L1: WAITING or BUSY
#define L4  (PIN & 0b00001000) // P -> LED L4: semaforo verde
#define L5  (PIN & 0b00100000) // P -> LED L5: semaforo rojo

// LED L1 -> DDR# y PORT#
#define L1PORT PORT
// LED L4
#define L4PORT PORT
// LED L5
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