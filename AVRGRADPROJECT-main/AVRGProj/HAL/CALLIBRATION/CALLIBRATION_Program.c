#define F_CPU 8000000UL

#include <avr/eeprom.h>
#include <stdint.h>
#include <util/delay.h>

#include "../../LIB/STD_Types.h"
#include "CALLIBRATION_Config.h"
#include "CALLIBRATION_Interface.h"
#include "../../MCAL/ADC/ADC_Interface.h"
#include "../../HAL/LCD/LCD_Interface.h"

#define EEPROM_CAL_VALID_ADDR  20
#define EEPROM_CAL_DATA_START  21
#define EEPROM_CAL_MAGIC_KEY   0xAA

static u16 Calibration_Baseline[CAL_SENSOR_COUNT];

void EEPROM_Write(u16 address, u8 data)
{
    eeprom_update_byte((u8 *)(uintptr_t)address, data);
}

u8 EEPROM_Read(u16 address)
{
    return eeprom_read_byte((const u8 *)(uintptr_t)address);
}

static void EEPROM_Write_u16(u16 address, u16 data)
{
    EEPROM_Write(address, (u8)(data & 0xFF));
    EEPROM_Write(address + 1, (u8)(data >> 8));
}

static u16 EEPROM_Read_u16(u16 address)
{
    u16 data = EEPROM_Read(address);
    data |= ((u16)EEPROM_Read(address + 1) << 8);
    return data;
}

u8 Calibration_Is_Valid(void)
{
    return (EEPROM_Read(EEPROM_CAL_VALID_ADDR) == EEPROM_CAL_MAGIC_KEY) ? 1 : 0;
}

void Start_Calibration(void)
{
    u8 sensor;
    u8 sample;
    u32 sum;

    LCD_Send_Command(lcd_Clear);
    LCD_GoTo(1, 1);
    LCD_Send_String((u8 *)"HOLD HAND STILL");
    LCD_GoTo(2, 1);
    LCD_Send_String((u8 *)"CALIBRATING...");

    _delay_ms(1500);

    for (sensor = 0; sensor < CAL_SENSOR_COUNT; sensor++)
    {
        sum = 0;
        for (sample = 0; sample < CAL_SAMPLE_COUNT; sample++)
        {
            sum += ADC_Read(sensor);
            _delay_ms(10);
        }
        Calibration_Baseline[sensor] = (u16)(sum / CAL_SAMPLE_COUNT);
    }

    LCD_Send_Command(lcd_Clear);
    LCD_GoTo(1, 1);
    LCD_Send_String((u8 *)"CALIBRATION");
    LCD_GoTo(2, 1);
    LCD_Send_String((u8 *)"COMPLETE");
    _delay_ms(1000);
}

void Save_Calibration(void)
{
    u8 sensor;
    u16 address;

    for (sensor = 0; sensor < CAL_SENSOR_COUNT; sensor++)
    {
        address = EEPROM_CAL_DATA_START + (sensor * 2);
        EEPROM_Write_u16(address, Calibration_Baseline[sensor]);
    }

    EEPROM_Write(EEPROM_CAL_VALID_ADDR, EEPROM_CAL_MAGIC_KEY);
}

void Load_Calibration(void)
{
    u8 sensor;
    u16 address;

    for (sensor = 0; sensor < CAL_SENSOR_COUNT; sensor++)
    {
        address = EEPROM_CAL_DATA_START + (sensor * 2);
        Calibration_Baseline[sensor] = EEPROM_Read_u16(address);
    }
}

u16 CALIBRATION_u16GetBaseline(u8 SensorIndex)
{
    if (SensorIndex < CAL_SENSOR_COUNT)
        return Calibration_Baseline[SensorIndex];

    return 0;
}
