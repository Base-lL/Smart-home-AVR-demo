#include "std_types.h"

#include "DIO_interface.h"

#include "MTR_config.h"
#include "MTR_interface.h"
#define F_CPU 8000000UL
#include <util/delay.h>

void MTR_init()
{
    DIO_u8SetPinDirection(MTR_PORT,MTR_PIN1,DIO_OUTPUT);
    DIO_u8SetPinDirection(MTR_PORT,MTR_PIN2,DIO_OUTPUT);
}

void MTR_rotateCW()
{
    DIO_u8SetPinValue(MTR_PORT,MTR_PIN1,DIO_HIGH);
    DIO_u8SetPinValue(MTR_PORT,MTR_PIN2,DIO_LOW);
}


void MTR_rotateCCW()
{
    DIO_u8SetPinValue(MTR_PORT,MTR_PIN1,DIO_LOW);
    DIO_u8SetPinValue(MTR_PORT,MTR_PIN2,DIO_HIGH);
}


void MTR_stop()
{
    DIO_u8SetPinValue(MTR_PORT,MTR_PIN1,DIO_LOW);
    DIO_u8SetPinValue(MTR_PORT,MTR_PIN2,DIO_LOW);
}