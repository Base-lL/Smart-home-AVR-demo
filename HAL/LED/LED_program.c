#include "std_types.h"

#include "DIO_interface.h"

#include "LED_config.h"
#include "LED_interface.h"

void LED_vidArrayInit()
{
    for(u8 i = 0 ; i < LED_TOTAL_COUNT ; i++)
    {
        DIO_u8SetPinDirection(
            LED_Array[i].port,
            LED_Array[i].pin,
            DIO_OUTPUT
        );

        DIO_u8SetPinValue(
            LED_Array[i].port,
            LED_Array[i].pin,
            LED_Array[i].state
        );
    }
}
void LED_vidArrayLightAll()
{
    for(u8 i = 0 ; i < LED_TOTAL_COUNT ; i++)
    {
        LED_vidLightON(i);
    }
}

void LED_vidArrayCloseAll()
{
    for(u8 i = 0 ; i < LED_TOTAL_COUNT ; i++)
    {
        LED_vidLightOFF(i);
    }
}

void LED_vidLightON(u8 copy_u8Led)
{
    LED_Array[copy_u8Led].state = LED_ON;
    DIO_u8SetPinValue(LED_Array[copy_u8Led].port,LED_Array[copy_u8Led].pin,LED_Array[copy_u8Led].state);
}
void LED_vidLightOFF(u8 copy_u8Led)
{
    LED_Array[copy_u8Led].state = LED_OFF;
    DIO_u8SetPinValue(LED_Array[copy_u8Led].port,LED_Array[copy_u8Led].pin,LED_Array[copy_u8Led].state);
}
void LED_vidLightSetState(u8 copy_u8Led, u8 copy_u8State)
{
    LED_Array[copy_u8Led].state = copy_u8State;
    DIO_u8SetPinValue(LED_Array[copy_u8Led].port, LED_Array[copy_u8Led].pin, copy_u8State);
}
void LED_vidLightToggle(u8 copy_u8Led)
{
    if(LED_Array[copy_u8Led].state == LED_ON)
    {
        LED_vidLightOFF(copy_u8Led);
    }
    else
    {
        LED_vidLightON(copy_u8Led);
    }
}
void LED_vidArrayLightonly(u8 copy_u8Led)
{
    LED_vidArrayCloseAll();
    LED_vidLightON(copy_u8Led);
}