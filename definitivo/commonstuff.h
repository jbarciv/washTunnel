/* ----------------------------------------------------------------------------
 * Aquí debe ir definido todos los pines y prototipos de funciones
 * 
 * 
 * 
 * 
 * -------------------------------------------------------------------------- */


#include <avr/io.h>
#include <avr/interrupt.h>



#ifndef LAVADERO_H_
#define LAVADERO_H_

// #define M2EN (PINE & 0b00000010) // Enable del motor
// #define M2DI (PINE & 0b00000100) // Direccion del motor
// #define SO5  (PINB & 0b00100000) // Sensor de "abajo"
// #define SW1  (PINB & 0b00001000) // Boton de emergencia, es activo por nivel bajo
// #define SW3  (PINB & 0b00000010) // Boton de inicio, es activo por nivel bajo
// #define L3   (PINB & 0b00000100) // Led de espera de cola
// #define L4   (PINB & 0b00010000) // Led de emergencia

// #define M2ENDDR DDRE
// #define M2DIDDR DDRE
// #define SO4DDR DDRB
// #define SO5DDR DDRB
// #define SW1DDR DDRB
// #define SW3DDR DDRB
// #define L3DDR DDRB
// #define L4DDR DDRB

// #define M2ENPORT PORTE
// #define M2DIPORT PORTE
// #define SO4PORT PORTB
// #define SO5PORT PORTE
// #define SW1PORT PORTB
// #define SW3PORT PORTB
// #define L3PORT PORTB
// #define L4PORT PORTB

// #define LIMITE_CUENTA_L3 1221 // 10 segundos
// #define LIMITE_CUENTA_ATRACCION 10990 // 45 segundos
// #define LIMITE_CUENTA_DOS_MINUTOS 14652
// #define LIMITE_CUENTA_MEDIO_SEGUNDO 61
// #define LIMITE_CUENTA_CINCO_SEGUNDOS 610

/* Etiquetas para los motores */
typedef enum {M1, M2, M3, M4, M5, M6} motor_t;
typedef enum {ENCENDIDO, APAGADO} motor_status_t;
typedef enum {DERECHA, IZQUIERDA} direccion_t;

/* Etiquetas para los 'estados' del tunel de lavado*/
typedef enum 
{
    RESTING,    // Estado de reposo, no se hace nada
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