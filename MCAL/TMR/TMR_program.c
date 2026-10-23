/*
 * TMR_program.c
 *
 *  Created on: Aug 19, 2026
 *      Author: emad.yousry
 */

#include "std_types.h"
#include "bit_math.h"
#include <stddef.h>

#include "TMR_private.h"
#include "TMR_interface.h"


static void (*TMR0_pvCallback)(void) = NULL;

void TMR0_vidOVModeInit(void)
{
	/*Select timer0 Overflow mode */
	CLR_BIT(TCCR0, TCCR0_WGM00);
	CLR_BIT(TCCR0, TCCR0_WGM01);

	/*Select Prescaller division factor by 8*/
	CLR_BIT(TCCR0, TCCR0_CS02);
	SET_BIT(TCCR0, TCCR0_CS01);
	CLR_BIT(TCCR0, TCCR0_CS00);

	/*Enable Overflow interrupt*/
	SET_BIT(TIMSK, TIMSK_TOIE0);
}

void TMR0_vidSetPreLoad(u8 value)
{
	TCNT0 = value;
}

void TMR0_vidCTCModeInit(void)
{
	/*Select timer0 CTC mode */
	CLR_BIT(TCCR0, TCCR0_WGM00);
	SET_BIT(TCCR0, TCCR0_WGM01);

	/*Select Prescaller division factor by 8*/
	CLR_BIT(TCCR0, TCCR0_CS02);
	SET_BIT(TCCR0, TCCR0_CS01);
	CLR_BIT(TCCR0, TCCR0_CS00);

	/*Enable OC interrupt*/
	SET_BIT(TIMSK, TIMSK_OCIE0);
}

void TMR0_vidSetCompareMatchValue(u8 value)
{
	OCR0 = value;
}

void TMR1_vidInit(void){

	/*Select timer1 FastPWM mode */
	CLR_BIT(TCCR1A, TCCR1A_WGM10);
	SET_BIT(TCCR1A, TCCR1A_WGM11);
	SET_BIT(TCCR1B, TCCR1B_WGM12);
	SET_BIT(TCCR1B, TCCR1B_WGM13);

	/*Select timer1 Fast PWM Non-inverting mode */
	SET_BIT(TCCR1A, TCCR1A_COM1A1);
	CLR_BIT(TCCR1A, TCCR1A_COM1A0);

	/*Select Prescaller division factor by 8*/
	CLR_BIT(TCCR1B, TCCR1B_CS12);
	SET_BIT(TCCR1B, TCCR1B_CS11);
	CLR_BIT(TCCR1B, TCCR1B_CS10);
}

void TMR1_vidSetTopValue(u16 topValue){
	ICR1 = topValue;
}
void TMR1_vidSetCompValueA(u16 compValue){
	OCR1A = compValue;
}



void TMR0_vidSetCallback(void (*copy_pvCallback)(void))
{
	if(copy_pvCallback != NULL){
		TMR0_pvCallback = copy_pvCallback;
	}
}

void TMR2_vidFastPWMInit(void)
{
    /* Select Timer 2 Fast PWM Mode (WGM21 = 1, WGM20 = 1) */
    SET_BIT(TCCR2, TCCR2_WGM20);
    SET_BIT(TCCR2, TCCR2_WGM21);

    /* Select Non-Inverting PWM Mode (COM21 = 1, COM20 = 0) */
    SET_BIT(TCCR2, TCCR2_COM21);
    CLR_BIT(TCCR2, TCCR2_COM20);

    /* Select Prescaler (e.g., Prescaler by 64 or 256 to tune frequency) */
    /* Example: Prescaler = 64 -> CS22 = 1, CS21 = 0, CS20 = 0 */
    SET_BIT(TCCR2, TCCR2_CS22);
    CLR_BIT(TCCR2, TCCR2_CS21);
    CLR_BIT(TCCR2, TCCR2_CS20);
}

void TMR2_vidSetCompareMatchValue(u8 copy_u8Value)
{
    OCR2 = copy_u8Value; // Controls the pulse width (duty cycle) for your servo on PD7
}


void __vector_11 (void) __attribute__ ((signal));

void __vector_11 (void)
{
	if(TMR0_pvCallback != NULL){
		TMR0_pvCallback();
	}

}


void __vector_10 (void) __attribute__ ((signal));

void __vector_10 (void)
{
	if(TMR0_pvCallback != NULL){
		TMR0_pvCallback();
	}

}
