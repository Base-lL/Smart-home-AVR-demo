
/* 1. Include Libraries */
#include "std_types.h"
#include "bit_math.h"

/* 2. Include Driver Files */
#include "EEPROM_interface.h"
#include "EEPROM_config.h"
#include "EEPROM_private.h"

/**
 * @brief  Initialize the EEPROM module.
 */
void EEPROM_voidInit(void)
{
    /*
     * Currently, internal EEPROM does not require special initialization.
     * If external EEPROM (via I2C) is used in the future,
     * I2C initialization code can be placed here based on EEPROM_TYPE.
     */
}

/**
 * @brief  Write a single byte to a specific memory address.
 */
void EEPROM_voidWriteByte(u16 Copy_u16Address, u8 Copy_u8Data)
{
    /* 1. Wait for completion of previous write */
    while (GET_BIT(EECR, EECR_EEWE) == 1);

    /* 2. Set up address and data registers */
    EEARL = (u8)Copy_u16Address;
    EEARH = (u8)(Copy_u16Address >> 8);
    EEDR  = Copy_u8Data;

    /* 3. Write logical one to EEMWE */
    SET_BIT(EECR, EECR_EEMWE);

    /* 4. Start EEPROM write by setting EEWE */
    SET_BIT(EECR, EECR_EEWE);
}

/**
 * @brief  Read a single byte from a specific memory address.
 */
u8 EEPROM_u8ReadByte(u16 Copy_u16Address)
{
    /* 1. Wait for completion of previous write */
    while (GET_BIT(EECR, EECR_EEWE) == 1);

    /* 2. Set up address registers */
    EEARL = (u8)Copy_u16Address;
    EEARH = (u8)(Copy_u16Address >> 8);

    /* 3. Start EEPROM read by setting EERE */
    SET_BIT(EECR, EECR_EERE);

    /* 4. Return data from data register */
    return EEDR;
}

/**
 * @brief  Write a block of data to EEPROM.
 */
void EEPROM_voidWriteBlock(u16 Copy_u16Address, const u8 *Copy_pu8Data, u8 Copy_u8Length)
{
    for (u8 i = 0; i < Copy_u8Length; i++)
    {
        EEPROM_voidWriteByte(Copy_u16Address + i, Copy_pu8Data[i]);
    }
}

/**
 * @brief  Read a block of data from EEPROM.
 */
void EEPROM_voidReadBlock(u16 Copy_u16Address, u8 *Copy_pu8Data, u8 Copy_u8Length)
{
    for (u8 i = 0; i < Copy_u8Length; i++)
    {
        Copy_pu8Data[i] = EEPROM_u8ReadByte(Copy_u16Address + i);
    }
}
