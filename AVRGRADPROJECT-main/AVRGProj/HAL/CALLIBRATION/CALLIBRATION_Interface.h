#ifndef HAL_CALLIBRATION_CALLIBRATION_INTERFACE_H_
#define HAL_CALLIBRATION_CALLIBRATION_INTERFACE_H_

#include "../../LIB/STD_Types.h"

void Start_Calibration(void);
void Save_Calibration(void);
void Load_Calibration(void);
u8 Calibration_Is_Valid(void);
u16 CALIBRATION_u16GetBaseline(u8 SensorIndex);

/* EEPROM byte access used by gesture storage. */
void EEPROM_Write(u16 address, u8 data);
u8 EEPROM_Read(u16 address);

#endif
