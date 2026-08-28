#define F_CPU 8000000UL
#include <util/delay.h>

#include "LCD_Interface.h"
#include "LCD_Config.h"

void LCD_Init			(void)
{
	// 1- must wait more than 30 ms before any action (VDD rises to 4.5 v)
	_delay_ms(50);
	// All Pins as OutPut pins
	DIO_enumSetPortDirection(LCD_DATA_PORT, DIO_PORT_OUTPUT);
	DIO_enumSetPinDirection(LCD_CONTROL_PORT, LCD_RS, DIO_PIN_OUTPUT);
	DIO_enumSetPinDirection(LCD_CONTROL_PORT, LCD_RW, DIO_PIN_OUTPUT);
	DIO_enumSetPinDirection(LCD_CONTROL_PORT, LCD_EN, DIO_PIN_OUTPUT);

	/* Return cursor to the first position on the first line  */
	LCD_Send_Command(lcd_Home);
	_delay_ms(1);

	/*FUNCTION SET Command : 2 lines , 5*8 font size */
	LCD_Send_Command(EIGHT_BITS); // 8 Bit Mode ==> 0x38
	_delay_ms(1); // wait more than 39 Ms

	/* DISPLAY & Cursor (ON / OFF) Control */
	LCD_Send_Command( lcd_DisplayOn_CursorOff);
	_delay_ms(1);

	/* DISPLAY CLEAR */
	LCD_Clear_Screen();

	/* ENTRY MODE  SET*/
	LCD_Send_Command( lcd_EntryMode);
	_delay_ms(1);
}

void LCD_Send_Data		(u8 data)
{
	// 1 - Send Data at data pins (D0 -D7)
	DIO_enumSetPortValue(LCD_DATA_PORT , data);
	// 2 - Select Register from RS pin
	DIO_enumSetPinValue(LCD_CONTROL_PORT , LCD_RS , DIO_PIN_HIGH);
	// 3 - Select read or write using R/W pin
	DIO_enumSetPinValue(LCD_CONTROL_PORT , LCD_RW , DIO_PIN_LOW);
	// 4 - Enable to EN pin by Falling edge
	LCD_Send_Falling_Edge();
}

void LCD_Send_Command	(u8 command)
{
	// 1 - Send Data at data pins (D0 -D7)
		DIO_enumSetPortValue(LCD_DATA_PORT , command);
		// 2 - Select Register from RS pin
		DIO_enumSetPinValue(LCD_CONTROL_PORT , LCD_RS , DIO_PIN_LOW);
		// 3 - Select read or write using R/W pin
		DIO_enumSetPinValue(LCD_CONTROL_PORT , LCD_RW , DIO_PIN_LOW);
		// 4 - Enable to EN pin by Falling edge
		LCD_Send_Falling_Edge();
}

void LCD_Send_String	(u8 *string)
{
	u8 LOC_u8Iterator = 0 ;

	while( string[LOC_u8Iterator] != '\0' ){

		LCD_Send_Data( string[LOC_u8Iterator] );
		LOC_u8Iterator++ ;

	}
}

void LCD_Send_Number	(u8 Number)
{
	u64 LOC_u64Reversed = 1 ;

	if( Number == 0 ){ LCD_Send_Data('0'); }

	else{

		while( Number != 0 ){

			LOC_u64Reversed = ( LOC_u64Reversed * 10 ) + ( Number % 10 );
			Number /= 10 ;

		}
		while( LOC_u64Reversed != 1 ){

			LCD_Send_Data( ( LOC_u64Reversed % 10 ) + 48 );
			LOC_u64Reversed /= 10 ;

		}

	}
}

void LCD_Clear_Screen	(void)
{
	LCD_Send_Command(lcd_Clear);
}

void LCD_Send_Falling_Edge		(void )
{
	DIO_enumSetPinValue(LCD_CONTROL_PORT , LCD_EN , DIO_PIN_HIGH);
	_delay_ms(1);
	DIO_enumSetPinValue(LCD_CONTROL_PORT , LCD_EN , DIO_PIN_LOW);
	_delay_ms(1);
}
void LCD_DisplaySpecialCharacter(u8 *pattern, u8 location)
{
    u8 LOC_u8Iterator;

    /* Go to CGRAM */
    LCD_Send_Command(lcd_CGRAM + (location * 8));

    /* Send the 8 rows of the character */
    for(LOC_u8Iterator = 0; LOC_u8Iterator < 8; LOC_u8Iterator++)
    {
        LCD_Send_Data(pattern[LOC_u8Iterator]);
    }

    /* Return to DDRAM */
    LCD_Send_Command(lcd_SetCursor);
}
