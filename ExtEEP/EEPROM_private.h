
#ifndef EEPROM_PRIVATE_H_
#define EEPROM_PRIVATE_H_



/* AVR Internal EEPROM Registers */
#define EEARL   (*(volatile u8*)0x3F)
#define EEARH   (*(volatile u8*)0x40)
#define EEDR    (*(volatile u8*)0x3D)
#define EECR    (*(volatile u8*)0x3C)

/* EECR Bit Definitions */
#define EECR_EEWE   1   /* EEPROM Write Enable */
#define EECR_EEMWE  2   /* EEPROM Master Write Enable */
#define EECR_EERE   0   /* EEPROM Read Enable */

#endif /* EEPROM_PRIVATE_H_ */
