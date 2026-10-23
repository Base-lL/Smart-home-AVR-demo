

#ifndef MCAL_DIO_INTERFACE_H_
#define MCAL_DIO_INTERFACE_H_


#define DIO_PORTA   0
#define DIO_PORTB   1
#define DIO_PORTC   2
#define DIO_PORTD   3

#define DIO_OUTPUT  1
#define DIO_INPUT   0

#define DIO_PORT_OUTPUT  0xff
#define DIO_PORT_INPUT   0x00

#define DIO_HIGH    1
#define DIO_LOW     0

#define DIO_PORT_HIGH  0xff
#define DIO_PORT_LOW   0x00

#define DIO_PIN0    0
#define DIO_PIN1    1
#define DIO_PIN2    2
#define DIO_PIN3    3
#define DIO_PIN4    4
#define DIO_PIN5    5
#define DIO_PIN6    6
#define DIO_PIN7    7


u8 DIO_u8SetPortValue(u8 copy_u8Port, u8 copy_u8Value);
u8 DIO_u8SetPortDirection(u8 copy_u8Port, u8 copy_u8Value);

u8 DIO_u8SetPinValue(u8 copy_u8Port, u8 copy_u8Pin, u8 copy_u8Value);
u8 DIO_u8TogglePinValue(u8 copy_u8Port, u8 copy_u8Pin);
u8 DIO_u8SetPinDirection(u8 copy_u8Port, u8 copy_u8Pin, u8 copy_u8Value);

u8 DIO_u8GetPinValue(u8 copy_u8Port, u8 copy_u8Pin, u8 *copy_pu8Value);


#endif /* MCAL_DIO_INTERFACE_H_ */
