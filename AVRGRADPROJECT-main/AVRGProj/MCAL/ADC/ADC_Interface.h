/*
 * ADC_Interface.h
 *
 *  Created on: Aug 18, 2026
 *      Author: lojine
 */

#ifndef MCAL_ADC_ADC_INTERFACE_H_
#define MCAL_ADC_ADC_INTERFACE_H_
#include "../../LIB/STD_Types.h"

#define ADC_CHANNEL_0			0
#define ADC_CHANNEL_1			1
#define ADC_CHANNEL_2			2
#define ADC_CHANNEL_3			3
#define ADC_CHANNEL_4			4
#define ADC_CHANNEL_5			5
#define ADC_CHANNEL_6			6
#define ADC_CHANNEL_7			7

u16  ADC_Read(u8 channel);

void ADC_Init(void);

#endif /* MCAL_ADC_ADC_INTERFACE_H_ */
