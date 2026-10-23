#ifndef HAL_SRV_INTERFACE_H_
#define HAL_SRV_INTERFACE_H_

#define USED_TIMER 2

#if(USED_TIMER == 0)


#elif(USED_TIMER == 1)
    #define SRV_PORT    DIO_PORTD
    #define SRV_PIN     DIO_PIN5
#elif(USED_TIMER == 2)
    #define SRV_PORT    DIO_PORTD
    #define SRV_PIN     DIO_PIN7
#else
    #error invalid timer selected

#endif


#if(USED_TIMER == 0)


#elif(USED_TIMER == 1)
    #define SERVO_LOW_BOUND 450
    #define SERVO_HIGH_BOUND (2000+SERVO_LOW_BOUND)
    #define SERVO_INCREMENT 50
#elif(USED_TIMER == 2)
    #define SERVO_LOW_BOUND 52
    #define SERVO_HIGH_BOUND 180
    #define SERVO_INCREMENT 1
#endif

#if(USED_TIMER == 0)


#elif(USED_TIMER == 1)
    #define SRV_vidRotateServoAngle(copy_u8ServoAngle) TMR1_vidSetCompValueA(copy_u8ServoAngle)
#elif(USED_TIMER == 2)
    #define SRV_vidRotateServoAngle(copy_u8ServoAngle) TMR2_vidSetCompareMatchValue(copy_u8ServoAngle)
#endif

extern u16 SRV_CurrentServoAngle;
extern u16 SRV_CurrentAngle;

void SRV_vidInit();
void SRV_vidRotateAngle(u8 copy_u8Angle);
    


#endif /* HAL_LCD_INTERFACE_H_ */
