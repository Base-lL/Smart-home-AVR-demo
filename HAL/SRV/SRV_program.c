#include "std_types.h"

#include "SRV_interface.h"

#include "DIO_interface.h"
#include "TMR_interface.h"

u16 SRV_CurrentServoAngle = SERVO_LOW_BOUND;
u16 SRV_CurrentAngle = 0;


void SRV_vidInit()
{
    DIO_u8SetPinDirection(SRV_PORT, SRV_PIN, DIO_OUTPUT);
#if(USED_TIMER == 0)
    TMR1_vidInit();
    TMR1_vidSetTopValue(20000);
#elif(USED_TIMER == 1)
    
#elif(USED_TIMER == 2)
    TMR2_vidFastPWMInit();
#endif
    SRV_vidRotateServoAngle(SRV_CurrentServoAngle);

}
    
void SRV_vidRotateAngle(u8 copy_u8Angle)
{
    if(copy_u8Angle > 180)
    {
        copy_u8Angle = 0;
    }
    SRV_CurrentAngle = copy_u8Angle;
    SRV_CurrentServoAngle =  SERVO_LOW_BOUND + ( (u32)copy_u8Angle * (SERVO_HIGH_BOUND-SERVO_LOW_BOUND)/180 );
    SRV_vidRotateServoAngle(copy_u8Angle);
}
    
