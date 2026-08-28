/*
 * CALLIBRATION_Interface.h
 *
 *  Created on: Aug 28, 2026
 *      Author: DELL
 */

#ifndef HAL_CALLIBRATION_CALLIBRATION_INTERFACE_H_
#define HAL_CALLIBRATION_CALLIBRATION_INTERFACE_H_
#include"CALLIBRATION_Config.h"
#define EEPROM_CAL_VALID_ADDR     20
#define EEPROM_CAL_DATA_START     21
#define EEPROM_CAL_MAGIC_KEY      0xAA
static u16 Calibration_Baseline[CAL_SENSOR_COUNT];
void CALIBRATION_vidStart(void);

u16 CALIBRATION_u16GetBaseline(u8 SensorIndex);
uint8_t Calibration_Is_Valid(void)
{
    if (EEPROM_Read(EEPROM_CAL_VALID_ADDR) ==
        EEPROM_CAL_MAGIC_KEY)
    {
        return 1;
    }

    return 0;
}

#endif /* HAL_CALLIBRATION_CALLIBRATION_INTERFACE_H_ */
