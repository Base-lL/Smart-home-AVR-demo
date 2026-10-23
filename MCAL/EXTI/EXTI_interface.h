/*
 * EXTI_interface.h
 *
 *  Created on: Aug 13, 2026
 *      Author: emad.yousry
 */

#ifndef MCAL_EXTI_EXTI_INTERFACE_H_
#define MCAL_EXTI_EXTI_INTERFACE_H_

typedef enum
{
    EXTI_TRIGGER_FALLING_EDGE,
    EXTI_TRIGGER_RISING_EDGE,
    EXTI_TRIGGER_ON_CHANGE,
    EXTI_TRIGGER_LOW_LEVEL
}EXTI_TRIGGER_STATE;

void EXTI_vidInt0Init(EXTI_TRIGGER_STATE trigger_state);
void EXTI_vidInt1Init(EXTI_TRIGGER_STATE trigger_state);
void EXTI_vidInt2Init(EXTI_TRIGGER_STATE trigger_state);

void EXI0_vidCallback(void (*ptr) (void));
void EXI1_vidCallback(void (*ptr) (void));
void EXI2_vidCallback(void (*ptr) (void));


#endif /* MCAL_EXTI_EXTI_INTERFACE_H_ */
