#include <avr/io.h>

#include "../../LIB/STD_Types.h"
#include "../../LIB/BIT_MATH.h"

#include "ADC_Interface.h"
#include "ADC_Private.h"


void ADC_Init(void)
{
    /* AVCC as reference voltage */
    ADMUX = (1 << REFS0);

    /* Enable ADC + Prescaler 128 */
    ADCSRA = (1 << ADEN) |
             (1 << ADPS2) |
             (1 << ADPS1) |
             (1 << ADPS0);
}


u16 ADC_Read(u8 channel)
{
    /* Select ADC channel */
    ADMUX = (ADMUX & 0xE0) | (channel & 0x07);

    /* Start conversion */
    ADCSRA |= (1 << ADSC);

    /* Wait for conversion */
    while(ADCSRA & (1 << ADSC));

    /* Read ADC result */
    u16 result;

    result = ADCL;
    result |= ((u16)ADCH << 8);

    return result;
}
