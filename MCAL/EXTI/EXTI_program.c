/*
 * EXTI_program.c
 *
 *  Created on: Aug 13, 2026
 *      Author: emad.yousry
 */

#include "bit_math.h"
#include "std_types.h"
#include <stddef.h>

#include "EXTI_private.h"
#include "EXTI_config.h"
#include "EXTI_interface.h"


void (*EXTI0_pvISRCallBack)(void) = NULL;
void (*EXTI1_pvISRCallBack)(void) = NULL;
void (*EXTI2_pvISRCallBack)(void) = NULL;


void EXTI_vidInt0Init(EXTI_TRIGGER_STATE trigger_state)
{
    if (trigger_state == EXTI_TRIGGER_RISING_EDGE)
    {
        SET_BIT(MCUCR, MCUCR_ISC01);
        SET_BIT(MCUCR, MCUCR_ISC00);
    }
    else if (trigger_state == EXTI_TRIGGER_FALLING_EDGE)
    {
        SET_BIT(MCUCR, MCUCR_ISC01);
        CLR_BIT(MCUCR, MCUCR_ISC00);
    }
    else if (trigger_state == EXTI_TRIGGER_ON_CHANGE)
    {
        CLR_BIT(MCUCR, MCUCR_ISC01);
        SET_BIT(MCUCR, MCUCR_ISC00);
    }
    else if (trigger_state == EXTI_TRIGGER_LOW_LEVEL)
    {
        CLR_BIT(MCUCR, MCUCR_ISC01);
        CLR_BIT(MCUCR, MCUCR_ISC00);
    }
    
    /* Enable INT0*/
    SET_BIT(GICR, GICR_INT0);
}

void EXTI_vidInt1Init(EXTI_TRIGGER_STATE trigger_state)
{
    if (trigger_state == EXTI_TRIGGER_RISING_EDGE)
    {
        SET_BIT(MCUCR, MCUCR_ISC11);
        SET_BIT(MCUCR, MCUCR_ISC10);
    }
    else if (trigger_state == EXTI_TRIGGER_FALLING_EDGE)
    {
        SET_BIT(MCUCR, MCUCR_ISC11);
        CLR_BIT(MCUCR, MCUCR_ISC10);
    }
    else if (trigger_state == EXTI_TRIGGER_ON_CHANGE)
    {
        CLR_BIT(MCUCR, MCUCR_ISC11);
        SET_BIT(MCUCR, MCUCR_ISC10);
    }
    else if (trigger_state == EXTI_TRIGGER_LOW_LEVEL)
    {
        CLR_BIT(MCUCR, MCUCR_ISC11);
        CLR_BIT(MCUCR, MCUCR_ISC10);
    }
    /* Enable INT1 */
    SET_BIT(GICR, GICR_INT1);
}

void EXTI_vidInt2Init(EXTI_TRIGGER_STATE trigger_state)
{
    if (trigger_state == EXTI_TRIGGER_RISING_EDGE)
    {
        SET_BIT(MCUCSR, MCUCSR_ISC2);
    }
    else if (trigger_state == EXTI_TRIGGER_FALLING_EDGE)
    {
        CLR_BIT(MCUCSR, MCUCSR_ISC2);
    }
    SET_BIT(GICR, GICR_INT2);
}

// ___________________
// INT0 PIN PD2 EXTI:
void EXI0_vidCallback(void (*ptr) (void))
{
	EXTI0_pvISRCallBack = ptr;
}

void __vector_1 (void) __attribute__((signal));

void __vector_1 (void){

	if(EXTI0_pvISRCallBack != 0)
	{
		EXTI0_pvISRCallBack();
	}
}

// ___________________
// INT1 PIN PD3 EXTI:
void EXI1_vidCallback(void (*ptr) (void))
{
	EXTI1_pvISRCallBack = ptr;
}

void __vector_2 (void) __attribute__((signal));

void __vector_2 (void){

	if(EXTI1_pvISRCallBack != 0)
	{
		EXTI1_pvISRCallBack();
	}
}

// ___________________
// INT2 PIN PB2 EXTI:
void EXI2_vidCallback(void (*ptr) (void))
{
	EXTI2_pvISRCallBack = ptr;
}

void __vector_3 (void) __attribute__((signal));

void __vector_3 (void){

	if(EXTI2_pvISRCallBack != 0)
	{
		EXTI2_pvISRCallBack();
	}
}
