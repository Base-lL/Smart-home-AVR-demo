#ifndef HAL_LCD_INTERFACE_H_
#define HAL_LCD_INTERFACE_H_

#include "LCD_config.h"

void LCD_vidSendCommand(u8 copy_u8Command);
void LCD_vidSendData(char copy_u8Data);
void LCD_vidSendDataXY(u8 copy_u8X, u8 copy_u8Y, u8 copy_u8Data);
void LCD_vidInit(void);
void LCD_vidClear();
void LCD_vidSendString(char* copy_u8string);
void LCD_vidSendStringXY(u8 copy_u8X, u8 copy_u8Y, char* copy_u8String);
void LCD_SendNumber(s16 copy_u16Data);
void LCD_vidShiftdisplayRight();
void LCD_vidShiftdisplayLeft();
void LCD_vidWriteNumber(u16 copy_u8num);


#endif /* HAL_LCD_INTERFACE_H_ */
