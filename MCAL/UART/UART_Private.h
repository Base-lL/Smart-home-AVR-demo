
#ifndef MCAL_UART_UART_PRIVATE_H_
#define MCAL_UART_UART_PRIVATE_H_


#include "std_types.h"

#define UDR     *((volatile u8*)0x2C)
#define UCSRA   *((volatile u8*)0x2B)
#define MPCM     0
#define U2X      1
#define PE       2
#define DOR      3
#define FE       4
#define UDRE     5
#define TXC      6
#define RXC      7
#define UCSRB   *((volatile u8*)0x2A)
#define TXB8     0
#define RXB8     1
#define UCSZ2    2
#define TXEN     3
#define RXEN     4
#define UDRIE    5
#define TXCIE    6
#define RXCIE    7
#define UCSRC   *((volatile u8*)0x40)
#define UCPOL    0
#define UCSZ0    1
#define UCSZ1    2
#define USBS     3
#define UPM0     4
#define UPM1     5
#define UMSEL    6
#define URSEL    7
#define UBRRL   *((volatile u8*)0x29)
#define UBRRH   *((volatile u8*)0x40)
/*------------------------------------------------------*/
//76543210
//01000000
//Mode Select
#define Uart_Asynchronous  0
#define Uart_Synchronous   0x40
//76543210
//00100000
//00110000
//Parity Mode
#define Uart_ParityDisable   0
#define Uart_ParityEven      0x20
#define Uart_ParityOdd       0x30
//76543210
//00001000
#define Uart_1StopBit        0x00
#define Uart_2StopBit        0x08


//76543210
//00000000
//00000010
//00000100
//00000110
#define Uart_5BitSize        0x00
#define Uart_6BitSize 		 0x02
#define Uart_7BitSize        0x04
#define Uart_8BitSize        0x06
#define Uart_9BitSize 		 7
#endif /* MCAL_UART_UART_PRIVATE_H_ */
