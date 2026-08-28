/*
 * CALLIBRATION_Program.c
 *
 *  Created on: Aug 28, 2026
 *      Author: DELL
 */
#include"../../LIB/STD_Types.h"
#include"CALLIBRATION_Interface.h"
#include"CALLIBRATION_Private.h"
#include"CALLIBRATION_Config.h"
#include"../../MCAL/ADC/ADC_Interface.h"
#include"../../HAL/LCD/LCD_Interface.h"
/* Stores the calibrated neutral values */
static u16 Calibration_Baseline[CAL_SENSOR_COUNT];


/*
 * Start calibration
 *
 * Reads every flex sensor multiple times
 * and stores the average value.
 */
void CALIBRATION_vidStart(void)
{
    u8 SensorIndex;
    u8 SampleIndex;

    u32 Sum;


    for (SensorIndex = 0;
         SensorIndex < CAL_SENSOR_COUNT;
         SensorIndex++)
    {
        Sum = 0;


        for (SampleIndex = 0;
             SampleIndex < CAL_SAMPLE_COUNT;
             SampleIndex++)
        {
            /* Read current sensor */

            Sum += ADC_Read(SensorIndex);
        }


        /* Calculate average */

        Calibration_Baseline[SensorIndex] =
            (u16)(Sum / CAL_SAMPLE_COUNT);
    }
}


/*
 * Return the calibration baseline
 * for a specific sensor.
 */
u16 CALIBRATION_u16GetBaseline(u8 SensorIndex)
{
    if (SensorIndex < CAL_SENSOR_COUNT)
    {
        return Calibration_Baseline[SensorIndex];
    }

    return 0;
}
uint8_t Calibration_Is_Valid(void)
{
    if (EEPROM_Read(EEPROM_CAL_VALID_ADDR) ==
        EEPROM_CAL_MAGIC_KEY)
    {
        return 1;
    }

    return 0;
}
void EEPROM_Write_u16(uint16_t address, u16 data)
{
    EEPROM_Write(address, (u8)(data & 0xFF));

    EEPROM_Write(address + 1,
                 (u8)(data >> 8));
}
u16 EEPROM_Read_u16(uint16_t address)
{
    u16 data;

    data = EEPROM_Read(address);

    data |= ((u16)EEPROM_Read(address + 1) << 8);

    return data;
}
void Start_Calibration(void)
{
    u8 sensor;
    u8 sample;

    u32 sum;


    LCD_Send_Command(lcd_Clear);

    LCD_GoTo(1, 1);
    LCD_Send_String((u8*)"HOLD HAND STILL");

    LCD_GoTo(2, 1);
    LCD_Send_String((u8*)"CALIBRATING...");


    _delay_ms(1500);


    for (sensor = 0;
         sensor < CAL_SENSOR_COUNT;
         sensor++)
    {
        sum = 0;


        for (sample = 0;
             sample < CAL_SAMPLE_COUNT;
             sample++)
        {
            sum += ADC_Read(sensor);

            _delay_ms(10);
        }


        Calibration_Baseline[sensor] =
            (u16)(sum / CAL_SAMPLE_COUNT);
    }


    LCD_Send_Command(lcd_Clear);

    LCD_GoTo(1, 1);
    LCD_Send_String((u8*)"CALIBRATION");

    LCD_GoTo(2, 1);
    LCD_Send_String((u8*)"COMPLETE");


    _delay_ms(1000);
}
void Save_Calibration(void)
{
    u8 sensor;

    uint16_t address;


    for (sensor = 0;
         sensor < CAL_SENSOR_COUNT;
         sensor++)
    {
        address =
            EEPROM_CAL_DATA_START +
            (sensor * 2);


        EEPROM_Write_u16(
            address,
            Calibration_Baseline[sensor]
        );
    }


    EEPROM_Write(
        EEPROM_CAL_VALID_ADDR,
        EEPROM_CAL_MAGIC_KEY
    );
}
void Load_Calibration(void)
{
    u8 sensor;

    uint16_t address;


    for (sensor = 0;
         sensor < CAL_SENSOR_COUNT;
         sensor++)
    {
        address =
            EEPROM_CAL_DATA_START +
            (sensor * 2);


        Calibration_Baseline[sensor] =
            EEPROM_Read_u16(address);
    }
}
