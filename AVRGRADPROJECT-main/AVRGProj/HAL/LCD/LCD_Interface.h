/*
 * LCD_Interface.h
 *
 *  Created on: Aug 13, 2026
 *      Author: lojine
 */

#ifndef HAL_LCD_LCD_INTERFACE_H_
#define HAL_LCD_LCD_INTERFACE_H_




#include "../../MCAL/DIO/DIO_Interface.h"
#include "../../LIB/STD_Types.h"


#define EIGHT_BITS 	0x38

#define lcd_DisplayOn_CursorOff       0x0c          // display on, cursor off, don't blink character
#define lcd_DisplayOn_CursorOn        0x0e          // display on, cursor on, don't blink character
#define lcd_DisplayOff_CursorOff      0x08          // turn display off
#define lcd_Clear                     0x01          //replace all characters with ASCII 'space'
#define lcd_EntryMode                 0x06          // shift cursor from left to right on read/write
#define lcd_Home                      0x02          // return cursor to first position on first line
#define lcd_CGRAM                     0x40          // the first Place/Address at CGRAM
#define lcd_SetCursor                 0x80          // set cursor position
#define lcd_FunctionReset             0x30          // reset the LCD


/***************************************************************************************/
#define CLCD_ROW_1   1
#define CLCD_ROW_2   2

#define CLCD_COL_1   1
#define CLCD_COL_2   2
#define CLCD_COL_3   3
#define CLCD_COL_4   4
#define CLCD_COL_5   5
#define CLCD_COL_6   6
#define CLCD_COL_7   7
#define CLCD_COL_8   8
#define CLCD_COL_9   9
#define CLCD_COL_10  10
#define CLCD_COL_11  11
#define CLCD_COL_12  12
#define CLCD_COL_13  13
#define CLCD_COL_14  14
#define CLCD_COL_15  15
#define CLCD_COL_16  16

/***************************************************************************************/



void LCD_Init			(void);
void LCD_Send_Data		(u8 data);
void LCD_Send_Command	(u8 command);
void LCD_Send_String	(u8 *string);
void LCD_Send_Number	(u8 Number);



void LCD_Clear_Screen			(void);
void LCD_Send_Falling_Edge		(void );
void LCD_DisplaySpecialCharacter(u8 *pattern, u8 location);
#endif /* HAL_LCD_LCD_INTERFACE_H_ */
