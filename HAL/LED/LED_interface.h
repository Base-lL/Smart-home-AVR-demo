#ifndef HAL_LED_INTERFACE_H_
#define HAL_LED_INTERFACE_H_

#include "LED_config.h"

void LED_vidArrayInit();
void LED_vidArrayLightAll();
void LED_vidArrayCloseAll();
void LED_vidLightON(u8 copy_u8Led);
void LED_vidLightOFF(u8 copy_u8LedP);
void LED_vidLightSetState(u8 copy_u8Led, u8 copy_u8State);
void LED_vidLightToggle(u8 copy_u8Led);
void LED_vidArrayLightonly(u8 copy_u8Led);

// to be added
// led light patterns

#endif /* HAL_LCD_INTERFACE_H_ */
