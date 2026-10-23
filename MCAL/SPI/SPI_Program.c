/*
 * SPI_Program.c
 *
 *  Created on: Sep 2, 2026
 *      Author: hesham
 */

#include "bit_math.h"
#include "std_types.h"
#include <stddef.h>


#include "SPI_Private.h"
#include "SPI_Config.h"
#include "SPI_Interface.h"
#define SPI_MaxTimeOut  10000UL

void SPI_voidInit()
{
	SPCR = SPI_InterruptState|
		   SPI_State|
		   SPI_DataOrder|
		   SPI_ModeSelect|
		   SPI_ClockPOL|
		   SPI_ClockPHA|
		   SPI_ClockRate;
#if SPI_SpeedType==SPI_DoubleSpeed
	SET_BIT(SPSR,SPI2X);
#elif SPI_SpeedType==SPI_NormalSpeed
	CLR_BIT(SPSR,SPI2X);
#endif

}

void SPI_EnableOperation()
{
	SET_BIT(SPCR,SPE);
}



//Polling

void SPI_voidTransmitSync(u8 Copy_u8TxData)
{
	u32 Local_u32TimeOut = 0;
	SPDR = Copy_u8TxData;
	SPI_EnableOperation();
	// wait 1- flag is set or timeout is finished
	while((ReadFlag(SPSR,SPIF) == 0)&&(Local_u32TimeOut<SPI_MaxTimeOut))
	{
		Local_u32TimeOut++;
	}
	// Clear Flag
}
u8 SPI_voidReceiveSync(void)
{
	u32 Local_u32TimeOut = 0;
	SPDR=0xFF;// Dummy Value
	SPI_EnableOperation();
	while((ReadFlag(SPSR,SPIF) == 0)&&(Local_u32TimeOut<SPI_MaxTimeOut))
	{
		Local_u32TimeOut++;
	}
	if(Local_u32TimeOut< SPI_MaxTimeOut)
	{
		return SPDR;
	}
	return 0xFF; // Dummy Value
}


u8 SPI_u8TransceiveSync(u8 Copy_u8TxData)
{
	u32 Local_u32TimeOut = 0;
	SPDR=Copy_u8TxData;
	SPI_EnableOperation();
	while((ReadFlag(SPSR,SPIF) == 0)&&(Local_u32TimeOut<SPI_MaxTimeOut))
	{
		Local_u32TimeOut++;
	}
	if(Local_u32TimeOut< SPI_MaxTimeOut)
	{
		return SPDR;
	}
	return Copy_u8TxData;
}

//static u8 (*SPI_GPF)(void)=NULL;
//static void (*SPI_GPF)(void)=NULL;
static void (*SPI_GPF)(u8)=NULL;
// Interrupt
void SPI_u8TransimtAsynch(u8 Copy_u8TxData)
{
	SPDR=Copy_u8TxData;
	SPI_EnableOperation();

}
//void SPI_CallBackFunction(void(*PF)(void))
//void SPI_CallBackFunction(u8(*PF)(void))
void SPI_CallBackFunction(void(*PF)(u8))
{
	if(PF!=NULL)
	{
		SPI_GPF=PF;
	}
}

/*ISR */
void __vector_12(void) __attribute__((signal));
void __vector_12(void)
{
	u8 ReceiveDate = SPDR;
	if(SPI_GPF!=NULL)
	{
		SPI_GPF(ReceiveDate);
	}
}














