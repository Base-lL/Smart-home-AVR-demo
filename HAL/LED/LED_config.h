#ifndef HAL_LED_CONFIG_H_
#define HAL_LED_CONFIG_H_

#define LED_ON  DIO_HIGH
#define LED_OFF DIO_LOW

typedef struct
{
    u8 port;
    u8 pin;
    u8 state;
}LED_t;


typedef enum
{
    LED_LIGHT1 = 0,
    LED_LIGHT2,
    LED_SYSTEM_ACTION,
    LED_SYSTEM_STATUS,
    LED_TOTAL_COUNT
} LED_ID_t;

static LED_t LED_Array[LED_TOTAL_COUNT] = 
{
    [LED_LIGHT1] = {
        .port   = DIO_PORTD,
        .pin    = DIO_PIN4,
        .state  = LED_OFF
    },
    [LED_LIGHT2] = {
        .port   = DIO_PORTD,
        .pin    = DIO_PIN6,
        .state  = LED_OFF
    },
    [LED_SYSTEM_ACTION] = {
        .port   = DIO_PORTC,
        .pin    = DIO_PIN0,
        .state  = LED_OFF
    },
    [LED_SYSTEM_STATUS] = {
        .port   = DIO_PORTB,
        .pin    = DIO_PIN0,
        .state  = LED_OFF
    },
};

#endif
