/*
 * Uart_Program.c
 *
 *  Created on: Sep 1, 2026
 *      Author: hesham
 */
#include "bit_math.h"
#include "std_types.h"
#include <stddef.h>

#include "UART_Private.h"
#include "UART_config.h"
#include "UART_Interface.h"



static void UART_SetBaudRate(u32 BaudRate)
{
	// BaudRate -> UBRR
	u16 UBRR_Temp = (u16)(FCPU/(16UL*BaudRate)) - 1 ;
	UBRRL = (u8)UBRR_Temp;
	UBRRH = (u8)(UBRR_Temp>>8)&~(1<<URSEL);
}

void UART_Init()
{
	UART_SetBaudRate(UART_BaudRate);

	u8 UCSRC_Temp=(1<<URSEL)|
				  UART_Mode |
				  UART_ParityMode|
				  UART_StopBit;

#if UART_DataSize==Uart_9BitSize
	SET_BIT(UCSRB,UCSZ2);
	SET_BIT(UCSRC_Temp,UCSZ1);
	SET_BIT(UCSRC_Temp,UCSZ0);
#else
	CLR_BIT(UCSRB,UCSZ2);
	UCSRC_Temp|=UART_DataSize;
#endif

	UCSRC= UCSRC_Temp ;
	UART_RxEnable();
	UART_TxEnable();
}

void UART_TxEnable()
{
	SET_BIT(UCSRB,TXEN);
}
void UART_TxDisable()
{
	CLR_BIT(UCSRB,TXEN);
}
void UART_RxEnable()
{
	SET_BIT(UCSRB,RXEN);
}
void UART_RxDisable()
{
	CLR_BIT(UCSRB,RXEN);
}

/*
 * 15 14 13 12 11 10 9 8
 * 7  6  5  4  3  2  1 0
 * */
void UART_SendBytePolling(u16 Data)
{
	// Wait until TxBuffer will be empty
	// UDRE => Flag Register Empty
	while(GET_BIT(UCSRA,UDRE)==0);//=>
#if UART_DataSize==Uart_9BitSize
	if(GET_BIT(Data,8)==1)
	{
		SET_BIT(UCSRB,TXB8);
	}
	else
	{
		CLR_BIT(UCSRB,TXB8);
	}
#endif
	UDR = (u8)Data;
}
void UART_ReceiveByte(u16 *Data)
{
	if(Data!=NULL)
	{
		// Wait until RXC
		while(GET_BIT(UCSRA,RXC)==0);
		*Data=UDR;
	#if UART_DataSize==Uart_9BitSize
		u8 Local_u8NinthBit=GET_BIT(UCSRB,RXB8);
		if(Local_u8NinthBit==1)
		{
			SET_BIT(*Data,8);
		}
		else
		{
			CLR_BIT(*Data,8);
		}
	#endif
	}
}
void UART_SendString(u8 *String)
{
	if(String!=NULL)
	{
		u8 Index = 0 ;
		while(String[Index]!='\0')
		{
			UART_SendBytePolling((u16)String[Index]);
			Index++;
		}
	}
}



u8 UART_u8IsDataAvailable(void)
{
    // Returns 1 if the RXC (Receive Complete) flag is set, otherwise 0
    return GET_BIT(UCSRA, RXC);
}

// the function is can't handle 9bit mode currently
u8 UART_u8ReadByteNonBlocking(void)
{
    return UDR; // Reads the byte and clears the flag
}




