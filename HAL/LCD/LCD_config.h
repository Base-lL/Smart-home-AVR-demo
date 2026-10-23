
#ifndef HAL_LCD_CONFIG_H_
#define HAL_LCD_CONFIG_H_

#define LCD_MODE_8BIT 0
#define LCD_MODE_4BIT 1
#define LCD_BIT_MODE LCD_MODE_4BIT


#define LCD_CTR_PORT    DIO_PORTB
#define LCD_RS          DIO_PIN1
#define LCD_RW          DIO_PIN2
#define LCD_E           DIO_PIN3

#if(LCD_BIT_MODE == LCD_MODE_8BIT)
    #define LCD_DATA_PORT   DIO_PORTA
#elif(LCD_BIT_MODE == LCD_MODE_4BIT)
    #define LCD_DATA_PORT   DIO_PORTB
    #define LCD_PIN4        DIO_PIN4
    #define LCD_PIN5        DIO_PIN5
    #define LCD_PIN6        DIO_PIN6
    #define LCD_PIN7        DIO_PIN7
#else
    #error invalid LCD mode selected, please choose either 4 bit or 8 bit mode
#endif




#endif /* HAL_LCD_CONFIG_H_ */
