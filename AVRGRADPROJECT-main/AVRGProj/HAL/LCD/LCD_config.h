/*
 * LCD_config.h
 *
 *  Created on: Aug 13, 2026
 *      Author: lojine
 */

#ifndef HAL_LCD_LCD_CONFIG_H_
#define HAL_LCD_LCD_CONFIG_H_

#include "../../MCAL/DIO/DIO_interface.h"

#define LCD_DATA_PORT		DIO_PORTD
#define LCD_CONTROL_PORT	DIO_PORTC

#define LCD_RS		DIO_PIN0
#define LCD_RW		DIO_PIN2
#define LCD_EN		DIO_PIN1


#endif /* HAL_LCD_LCD_CONFIG_H_ */
