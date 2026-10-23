#include "std_types.h"
#include "bit_math.h"

#include "DIO_interface.h"

#include "LCD_config.h"
#include "LCD_interface.h"

# define F_CPU 8000000UL
#include <util/delay.h>

#if (LCD_BIT_MODE == LCD_MODE_4BIT)
//Private Helper: Send 4-bit Nibble (Used only in 4-bit mode)
static void LCD_vidSendNibble(u8 copy_u8Nibble)
{
    /* Write lower 4 bits of input parameter to LCD_D4..LCD_D7 (Upper nibble of LCD_DATA_PORT) */
    DIO_u8SetPinValue(LCD_DATA_PORT, LCD_PIN4, (copy_u8Nibble >> 0) & 0x01);
    DIO_u8SetPinValue(LCD_DATA_PORT, LCD_PIN5, (copy_u8Nibble >> 1) & 0x01);
    DIO_u8SetPinValue(LCD_DATA_PORT, LCD_PIN6, (copy_u8Nibble >> 2) & 0x01);
    DIO_u8SetPinValue(LCD_DATA_PORT, LCD_PIN7, (copy_u8Nibble >> 3) & 0x01);

    /* Pulse Enable Pin (E) */
    DIO_u8SetPinValue(LCD_CTR_PORT, LCD_E, DIO_HIGH);
    _delay_us(2);
    DIO_u8SetPinValue(LCD_CTR_PORT, LCD_E, DIO_LOW);
    _delay_us(100);
}
#endif

void LCD_vidSendCommand(u8 copy_u8Command)
{
	DIO_u8SetPinValue(LCD_CTR_PORT, LCD_RS, DIO_LOW);
	DIO_u8SetPinValue(LCD_CTR_PORT, LCD_RW, DIO_LOW);

#if (LCD_BIT_MODE == LCD_MODE_8BIT)
    /* 8-Bit Mode: Send full byte across 8 parallel lines */
    DIO_u8SetPortValue(LCD_DATA_PORT, copy_u8Command);

    DIO_u8SetPinValue(LCD_CTR_PORT, LCD_E, DIO_HIGH);
    _delay_ms(2);
    DIO_u8SetPinValue(LCD_CTR_PORT, LCD_E, DIO_LOW);
    _delay_ms(2);

#elif (LCD_BIT_MODE == LCD_MODE_4BIT)
    /* 4-Bit Mode: Send High Nibble first, then Low Nibble */
    LCD_vidSendNibble(copy_u8Command >> 4);
    LCD_vidSendNibble(copy_u8Command & 0x0F);
    _delay_ms(2);
#endif

}

void LCD_vidSendData(char copy_u8Data)
{
    DIO_u8SetPinValue(LCD_CTR_PORT, LCD_RS, DIO_HIGH);
    DIO_u8SetPinValue(LCD_CTR_PORT, LCD_RW, DIO_LOW);

#if (LCD_BIT_MODE == LCD_MODE_8BIT)
    DIO_u8SetPortValue(LCD_DATA_PORT, copy_u8Data);

    DIO_u8SetPinValue(LCD_CTR_PORT, LCD_E, DIO_HIGH);
    _delay_ms(2);
    DIO_u8SetPinValue(LCD_CTR_PORT, LCD_E, DIO_LOW);
    _delay_ms(2);

#elif (LCD_BIT_MODE == LCD_MODE_4BIT)
    LCD_vidSendNibble(copy_u8Data >> 4);
    LCD_vidSendNibble(copy_u8Data & 0x0F);
    _delay_ms(2);
#endif
}

void LCD_vidSendDataXY(u8 copy_u8X, u8 copy_u8Y, u8 copy_u8Data)
{
    u8 local_u8Address = 0;

    if (copy_u8Y == 0)
    {
        local_u8Address = copy_u8X;
    }
    else if (copy_u8Y == 1)
    {
        local_u8Address = copy_u8X + 0x40;
    }
	else
	{
		return;
	}

    LCD_vidSendCommand(0x80 + local_u8Address);
	LCD_vidSendData(copy_u8Data);
}

void LCD_vidInit(void)
{
    DIO_u8SetPinDirection(LCD_CTR_PORT, LCD_RS, DIO_OUTPUT);
    DIO_u8SetPinDirection(LCD_CTR_PORT, LCD_RW, DIO_OUTPUT);
    DIO_u8SetPinDirection(LCD_CTR_PORT, LCD_E, DIO_OUTPUT);

#if (LCD_BIT_MODE == LCD_MODE_8BIT)
    /* Set all 8 bits of DATA_PORT as outputs */
    DIO_u8SetPortDirection(LCD_DATA_PORT, DIO_PORT_OUTPUT);
    _delay_ms(40);

    /* 8-Bit Function Set: 2 lines, 5x8 font */
    LCD_vidSendCommand(0b00111000);

#elif (LCD_BIT_MODE == LCD_MODE_4BIT)
    /* Set only pins D4-D7 as outputs */
    DIO_u8SetPinDirection(LCD_DATA_PORT, LCD_PIN4, DIO_OUTPUT);
    DIO_u8SetPinDirection(LCD_DATA_PORT, LCD_PIN5, DIO_OUTPUT);
    DIO_u8SetPinDirection(LCD_DATA_PORT, LCD_PIN6, DIO_OUTPUT);
    DIO_u8SetPinDirection(LCD_DATA_PORT, LCD_PIN7, DIO_OUTPUT);
    _delay_ms(40);

    /* HD44780 4-Bit Reset Initialization Sequence */
    LCD_vidSendNibble(0x03);
    _delay_ms(5);

    LCD_vidSendNibble(0x03);
    _delay_ms(1);

    LCD_vidSendNibble(0x03);
    _delay_ms(1);

    /* Switch interface to 4-bit mode */
    LCD_vidSendNibble(0x02);
    _delay_ms(1);

    /* 4-Bit Function Set: 2 lines, 5x8 font (0x28) */
    LCD_vidSendCommand(0b00101000);
#endif

    /* Send Display ON/OFF Control (Display ON, Cursor OFF, Blink OFF) */
    LCD_vidSendCommand(0b00001100);

    /* Send Display Clear */
    LCD_vidSendCommand(0b00000001);
    _delay_ms(2);

    /* Send Entry Mode Set (Increment cursor to the right) */
    LCD_vidSendCommand(0b00000110);
}

void LCD_vidClear()
{
	LCD_vidSendCommand(0b00000001);
}

void LCD_vidSendString(char* copy_u8String)
{

	if(copy_u8String == NULL) return;
	u8 i = 0;
	while(copy_u8String[i] != '\0')
	{
		LCD_vidSendData(copy_u8String[i++]);
	}
}

void LCD_SendNumber(s16 copy_u16Number)
{
    // buffer defined with 6 sincethe largest
    // possible number to print with u16 is -32,768
	char buffer[6] = {0};
    if(copy_u16Number<0)
    {
        LCD_vidSendData('-');
        copy_u16Number *= -1;
    }
	uint8_t i = 0;

	if(copy_u16Number == 0)
	{
		LCD_vidSendData('0');
		return;
	}

	while(copy_u16Number>0)
	{
		buffer[i++] = copy_u16Number%10 + '0';
		copy_u16Number /= 10;
	}
	while(i>0)
	{
        LCD_vidSendData(buffer[--i] );
	}
}

void LCD_vidSendStringXY(u8 copy_u8X, u8 copy_u8Y, char* copy_u8String)
{
    u8 local_u8Address = 0;

    if (copy_u8Y == 0)
    {
        local_u8Address = copy_u8X;
    }
    else if (copy_u8Y == 1)
    {
        local_u8Address = copy_u8X + 0x40;
    }
	else
	{
		return;
	}

    LCD_vidSendCommand(0x80 + local_u8Address);
	LCD_vidSendString(copy_u8String);
}

void LCD_vidShiftdisplayRight()
{
	LCD_vidSendCommand(0b00011000);
}

void LCD_vidShiftdisplayLeft()
{
	LCD_vidSendCommand(0b00011100);
}
