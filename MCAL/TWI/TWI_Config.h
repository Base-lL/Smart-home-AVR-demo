/*
 * TWI_Config.h
 *
 *  Created on: Sep 7, 2026
 *      Author: hesham
 */

#ifndef MCAL_TWI_TWI_CONFIG_H_
#define MCAL_TWI_TWI_CONFIG_H_

#define TWI_Mode     TWI_Master
#if TWI_Mode == TWI_Master
// SCL Freq = (Cpu freq )/ (16+2*(TWBR)*(4^TWPS))
/*
 * Prescaller Options
 * TWI_Prescaller1
 * TWI_Prescaller4
 * TWI_Prescaller16
 * TWI_Prescaller64 */
#define TWI_Prescaller   0
#define TWI_BitRate      2
#endif
/*
 * Reserved Address is
 * 1- General call 0000 000
 * 2- MSB  as High 1111 xxx
 * */
#define TWI_MyOwnAddress   0x02

#endif /* MCAL_TWI_TWI_CONFIG_H_ */
