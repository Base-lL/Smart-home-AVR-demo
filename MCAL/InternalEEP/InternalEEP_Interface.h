/*
 * InternalEEP_Interface.h
 *
 *  Created on: Sep 8, 2026
 *      Author: hesham
 */

#ifndef MCAL_INTERNALEEP_INTERNALEEP_INTERFACE_H_
#define MCAL_INTERNALEEP_INTERNALEEP_INTERFACE_H_


#include "../../LIB/std_types.h"
#include "../../LIB/bit_math.h"
#include "InternalEEP_Private.h"
#include "InternalEEP_Config.h"

/**
 * @fn      EEPROM_voidWriteByte
 * @brief   Writes a byte of data to a specific Address in the internal EEPROM
 * @param   ByteAddress  : the Memory Address (0 to 1023 for Atmega32)
 * @param   Data         : the Data byte to be written
 * @return  void
 */
void EEPROM_voidWriteByte(u16 ByteAddress , u8 Data );


/**
 * @fn
 * @brief
 * @param ByteAddress
 * @return
 */
u8 EEPROM_voidReadByte(u16 ByteAddress);





#endif /* MCAL_INTERNALEEP_INTERNALEEP_INTERFACE_H_ */
