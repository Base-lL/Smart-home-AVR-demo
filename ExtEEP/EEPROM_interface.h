
#ifndef EEPROM_INTERFACE_H_
#define EEPROM_INTERFACE_H_


void EEPROM_voidInit(void);
void EEPROM_voidWriteByte(u16 Copy_u16Address, u8 Copy_u8Data);
u8 EEPROM_u8ReadByte(u16 Copy_u16Address);
void EEPROM_voidWriteBlock(u16 Copy_u16Address, const u8 *Copy_pu8Data, u8 Copy_u8Length);
void EEPROM_voidReadBlock(u16 Copy_u16Address, u8 *Copy_pu8Data, u8 Copy_u8Length);

#endif /* EEPROM_INTERFACE_H_ */

