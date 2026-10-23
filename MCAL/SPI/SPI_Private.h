/*
 * SPI_Private.h
 *
 *  Created on: Sep 2, 2026
 *      Author: hesham
 */

#ifndef MCAL_SPI_SPI_PRIVATE_H_
#define MCAL_SPI_SPI_PRIVATE_H_


#define ReadFlag(Reg,Bit)  ((Reg>>Bit)&1)

#define SPCR   *((volatile u8*)0x2D)
#define SPR0        0
#define SPR1        1
#define CPHA        2
#define CPOL        3
#define MSTR        4
#define DODR        5
#define SPE         6
#define SPIE        7
#define SPSR   *((volatile u8*)0x2E)
#define SPI2X       0
#define WCOL        6
#define SPIF        7
#define SPDR   *((volatile u8*)0x2F)

/*Options*/
// SPCR
// 76543210
// 00010000
/*
 * 1- Interrupt State (SPIE-Bit7) */
#define SPI_InterruptDisable 0x00
#define SPI_InterruptEnable  0x80


/*
 * 2- SPI Peripheral  State(SPE-Bit6) */
#define SPI_Disable 0x00
#define SPI_Enable  0x40


/*
 * 3- SPI Data Order  (DODR-Bit5) */
#define SPI_MSBFirst  0x00
#define SPI_LSBFirst  0x20


/*
 * 4- Master/Slave Select (MSTR-Bit4) */
#define SPI_Slave   0x00
#define SPI_Master  0x10

// SPCR
// 76543210
// 00000100
/*
 * 5- Clock Polarity (CPOL-Bit3) */
#define SPI_RisingLead    0x00
#define SPI_FallingLead   0x08




/*
 * 6- Clock Phase (CPHA-Bit2) */
#define SPI_SampleFirst     0x00
#define SPI_SetupFirst      0x04

/*7- Clock Rate (0,1)*/
// 76543210
// Normal Speed
#define SPI_FOSC_4      0x00
#define SPI_FOSC_16     0x01
#define SPI_FOSC_64     0x02
#define SPI_FOSC_128    0x03



// Double Speed
#define SPI_FOSC_2      0x00
#define SPI_FOSC_8      0x01
#define SPI_FOSC_32     0x02




/*8- Speed Type  -(SPI2X - 0 )*/

#define SPI_NormalSpeed 0x00
#define SPI_DoubleSpeed 0x01




































#endif /* MCAL_SPI_SPI_PRIVATE_H_ */
