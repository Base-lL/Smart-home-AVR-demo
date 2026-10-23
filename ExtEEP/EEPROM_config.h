
#ifndef EEPROM_CONFIG_H_
#define EEPROM_CONFIG_H_

#ifndef EEPROM_CFG_H_
#define EEPROM_CFG_H_

/* Select EEPROM Type:
 * 0 -> Internal EEPROM (ATmega32)
 * 1 -> External EEPROM (e.g., AT24C08 via I2C)
 */
#define EEPROM_TYPE   0

#if (EEPROM_TYPE == 1)
    /* Define I2C Address for External EEPROM */
    #define EEPROM_I2C_BASE_ADDRESS   0x50
#endif

#endif /* EEPROM_CFG_H_ */

#endif /* EEPROM_CONFIG_H_ */
