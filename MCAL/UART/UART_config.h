/*
 * Uart_config.h
 *
 *  Created on: Sep 1, 2026
 *      Author: hesham
 */

#ifndef MCAL_UART_UART_CONFIG_H_
#define MCAL_UART_UART_CONFIG_H_
/*
 * Uart_Asynchronous
 * Uart_Synchronous*/
#define UART_Mode       Uart_Asynchronous
/*
 * Uart_ParityDisable
 * Uart_ParityEven
 * Uart_ParityOdd
 * */
#define UART_ParityMode  Uart_ParityDisable

/*
 * Uart_1StopBit
 * Uart_2StopBit
 * */
#define UART_StopBit     Uart_1StopBit

/*
 * Uart_5BitSize
 * Uart_6BitSize
 * Uart_7BitSize
 * Uart_8BitSize
 * Uart_9BitSize*/

#define UART_DataSize   Uart_8BitSize



#define UART_BaudRate    9600UL


#endif /* MCAL_UART_UART_CONFIG_H_ */
