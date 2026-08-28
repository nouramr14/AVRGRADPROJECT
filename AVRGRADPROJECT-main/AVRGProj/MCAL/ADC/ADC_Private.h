/*
 * ADC_Private.h
 *
 * Created on: Aug 18, 2026
 * Author: lojine
 */

#ifndef MCAL_ADC_ADC_PRIVATE_H_
#define MCAL_ADC_ADC_PRIVATE_H_

#define ADMUX    *((volatile u8*)0x27)
#define ADCSRA   *((volatile u8*)0x26)
#define ADCH     *((volatile u8*)0x25)
#define ADCL     *((volatile u8*)0x24)

#endif /* MCAL_ADC_ADC_PRIVATE_H_ */
