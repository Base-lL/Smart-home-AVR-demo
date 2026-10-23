/*
 * SPI_Interface.h
 *
 *  Created on: Sep 2, 2026
 *      Author: hesham
 */

// Doxygen Style
/*
 * @breif
 * @param
 * @param
 * @return
 * */
#ifndef MCAL_SPI_SPI_INTERFACE_H_
#define MCAL_SPI_SPI_INTERFACE_H_

void SPI_voidInit();
void SPI_EnableOperation();
//Polling

void SPI_voidTransmitSync(u8 Copy_u8TxData);
u8 SPI_voidReceiveSync(void);
u8 SPI_u8TransceiveSync(u8 Copy_u8TxData);

// Interrupt
void SPI_u8TransimtAsynch(u8 Copy_u8TxData);
void SPI_CallBackFunction(void(*PF)(u8));




#endif /* MCAL_SPI_SPI_INTERFACE_H_ */
