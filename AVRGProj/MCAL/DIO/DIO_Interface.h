/*
 * DIO_Interface.h
 *
 *  Created on: Aug 28, 2026
 *      Author: DELL
 */

#ifndef MCAL_DIO_DIO_INTERFACE_H_
#define MCAL_DIO_DIO_INTERFACE_H_
#include "DIO_Config.h"
#include "DIO_Private.h"
#include "../../LIB/STD_Types.h"
#include "../../LIB/BIT_Math.h"


// DIO Status
#define DIO_NOK 0
#define DIO_OK  1

// Port Defines
#define  DIO_PORTA  0
#define  DIO_PORTB  1
#define  DIO_PORTC  2
#define  DIO_PORTD  3


// PIN Defines
#define DIO_PIN0   0
#define DIO_PIN1   1
#define DIO_PIN2   2
#define DIO_PIN3   3
#define DIO_PIN4   4
#define DIO_PIN5   5
#define DIO_PIN6   6
#define DIO_PIN7   7


// PIN Directions
#define DIO_PIN_OUTPUT		1
#define DIO_PIN_INPUT	    0

// PIN Value Options
#define DIO_PIN_HIGH		1
#define DIO_PIN_LOW			0

// PORT Directions
#define DIO_PORT_OUTPUT		0xFF
#define DIO_PORT_INPUT		0

// PORT Value Options
#define DIO_PORT_HIGH 		0xFF
#define DIO_PORT_LOW  		0

//Pull UP
#define PUD   2


// IO Pins
void DIO_enumSetPinDirection      (u8 Copy_u8PORT, u8 Copy_u8PIN, u8 Copy_u8Direction     );
void DIO_enumSetPinValue          (u8 Copy_u8PORT, u8 Copy_u8PIN, u8 Copy_u8Value         );
void DIO_enumGetPinValue          (u8 Copy_u8PORT, u8 Copy_u8PIN, u8 * Copy_PtrData       );
void DIO_enumTogglePinValue       (u8 Copy_u8PORT, u8 Copy_u8PIN                          );

// IO Ports
void DIO_enumSetPortDirection     (u8 Copy_u8PORT, u8 Copy_u8Direction  );
void DIO_enumSetPortValue         (u8 Copy_u8PORT, u8 Copy_u8Value      );
void DIO_enumGetPortValue         (u8 Copy_u8PORT, u8 * Copy_PtrData    );
void DIO_enumTogglePortValue      (u8 Copy_u8PORT                       );


#endif /* MCAL_DIO_DIO_INTERFACE_H_ */
