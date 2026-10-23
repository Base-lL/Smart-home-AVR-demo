/*
 * TMR_interface.h
 *
 *  Created on: Aug 19, 2026
 *      Author: emad.yousry
 */

#ifndef MCAL_TMR_TMR_INTERFACE_H_
#define MCAL_TMR_TMR_INTERFACE_H_

void TMR0_vidOVModeInit(void);

void TMR0_vidSetPreLoad(u8 value);

void TMR0_vidSetCallback(void (*copy_pvCallback)(void));


void TMR0_vidCTCModeInit(void);

void TMR0_vidSetCompareMatchValue(u8 value);



void TMR1_vidInit(void);

void TMR1_vidSetTopValue(u16 topValue);
void TMR1_vidSetCompValueA(u16 compValue);

void TMR2_vidFastPWMInit(void);
void TMR2_vidSetCompareMatchValue(u8 copy_u8Value);


#endif /* MCAL_TMR_TMR_INTERFACE_H_ */
