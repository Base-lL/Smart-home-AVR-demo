
#include "FreeRTOS.h"
#include "task.h"

#ifndef MCAL_UART_UART_INTERFACE_H_
#define MCAL_UART_UART_INTERFACE_H_

void UART_Init();
void UART_SendBytePolling(u16 Data);
void UART_ReceiveByte(u16 *Data);
void UART_SendString(u8 *String);


void UART_TxEnable();
void UART_TxDisable();
void UART_RxEnable();
void UART_RxDisable();

u8 UART_u8IsDataAvailable(void);
u8 UART_u8ReadByteNonBlocking(void);


#endif /* MCAL_UART_UART_INTERFACE_H_ */
