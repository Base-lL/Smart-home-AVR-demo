/*
 * DIO_program.c
 *
 *  Created on: Aug 5, 2026
 *      Author: emad.yousry
 */

#include "std_types.h"
#include "bit_math.h"

#include "DIO_private.h"
#include "DIO_interface.h"



u8  DIO_u8SetPortValue(u8 copy_u8Port, u8 copy_u8Value)
{
	u8 status_code = 0;
	switch(copy_u8Port)
	{
		case DIO_PORTA : PORTA = copy_u8Value; break;
		case DIO_PORTB : PORTB = copy_u8Value; break;
		case DIO_PORTC : PORTC = copy_u8Value; break;
		case DIO_PORTD : PORTD = copy_u8Value; break;
		default : status_code = 1;
	}

	return status_code;
}


u8  DIO_u8SetPortDirection(u8 copy_u8Port, u8 copy_u8Value)
{
	u8 status_code = 0;
	switch(copy_u8Port)
	{
		case DIO_PORTA : DDRA = copy_u8Value; break;
		case DIO_PORTB : DDRB = copy_u8Value; break;
		case DIO_PORTC : DDRC = copy_u8Value; break;
		case DIO_PORTD : DDRD = copy_u8Value; break;
		default : status_code = 1;
	}

	return status_code;
}


u8  DIO_u8SetPinValue(u8 copy_u8Port, u8 copy_u8Pin, u8 copy_u8Value)
{
	u8 status_code = 0;

	if(copy_u8Pin <= DIO_PIN7)
	{
		if(copy_u8Value == DIO_LOW)
		{
			switch(copy_u8Port)
			{
				case DIO_PORTA : CLR_BIT(PORTA, copy_u8Pin); break;
				case DIO_PORTB : CLR_BIT(PORTB, copy_u8Pin); break;
				case DIO_PORTC : CLR_BIT(PORTC, copy_u8Pin); break;
				case DIO_PORTD : CLR_BIT(PORTD, copy_u8Pin); break;
				default : status_code = 1;
			}

		}
		else if (copy_u8Value == DIO_HIGH)
		{
			switch(copy_u8Port)
			{
				case DIO_PORTA : SET_BIT(PORTA, copy_u8Pin); break;
				case DIO_PORTB : SET_BIT(PORTB, copy_u8Pin); break;
				case DIO_PORTC : SET_BIT(PORTC, copy_u8Pin); break;
				case DIO_PORTD : SET_BIT(PORTD, copy_u8Pin); break;
				default : status_code = 1;
			}
		}
		else
		{
			status_code = 1;
		}
	}
	else
	{
		status_code = 1;
	}

	return status_code;
}

u8 DIO_u8TogglePinValue(u8 copy_u8Port, u8 copy_u8Pin)
{
	u8 status_code = 0;
	
	if(copy_u8Pin <= DIO_PIN7)
	{
		switch(copy_u8Port)
		{
			case DIO_PORTA : TOG_BIT(PORTA, copy_u8Pin); break;
			case DIO_PORTB : TOG_BIT(PORTB, copy_u8Pin); break;
			case DIO_PORTC : TOG_BIT(PORTC, copy_u8Pin); break;
			case DIO_PORTD : TOG_BIT(PORTD, copy_u8Pin); break;
			default : status_code = 1;
		}
	}
	else
	{
		status_code = 1;
	}

	return status_code;
} 


u8  DIO_u8SetPinDirection(u8 copy_u8Port, u8 copy_u8Pin, u8 copy_u8Value)
{
	u8 status_code = 0;

	if(copy_u8Pin <= DIO_PIN7){
		if(copy_u8Value == DIO_INPUT)
		{
			switch(copy_u8Port)
			{
				case DIO_PORTA : CLR_BIT(DDRA, copy_u8Pin); break;
				case DIO_PORTB : CLR_BIT(DDRB, copy_u8Pin); break;
				case DIO_PORTC : CLR_BIT(DDRC, copy_u8Pin); break;
				case DIO_PORTD : CLR_BIT(DDRD, copy_u8Pin); break;
				default : status_code = 1;
			}

		}else if (copy_u8Value == DIO_OUTPUT){
			switch(copy_u8Port)
			{
				case DIO_PORTA : SET_BIT(DDRA, copy_u8Pin); break;
				case DIO_PORTB : SET_BIT(DDRB, copy_u8Pin); break;
				case DIO_PORTC : SET_BIT(DDRC, copy_u8Pin); break;
				case DIO_PORTD : SET_BIT(DDRD, copy_u8Pin); break;
				default : status_code = 1;
			}
		}else{
			status_code = 1;
		}
	}else{
		status_code = 1;
	}

	return status_code;
}


u8 DIO_u8GetPinValue(u8 copy_u8Port, u8 copy_u8Pin, u8 *copy_pu8Value)
{

	u8 status_code = 0;

	if(copy_u8Pin <= DIO_PIN7){

		switch(copy_u8Port)
		{
			case DIO_PORTA :  *copy_pu8Value = GET_BIT(PINA, copy_u8Pin); break;
			case DIO_PORTB :  *copy_pu8Value = GET_BIT(PINB, copy_u8Pin); break;
			case DIO_PORTC :  *copy_pu8Value = GET_BIT(PINC, copy_u8Pin); break;
			case DIO_PORTD :  *copy_pu8Value = GET_BIT(PIND, copy_u8Pin); break;
			default : status_code = 1;
		}

	}else{
		status_code = 1;
	}

	return status_code;

}


