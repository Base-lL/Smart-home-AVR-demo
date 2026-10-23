/*
 * SPI_Config.h
 *
 *  Created on: Sep 2, 2026
 *      Author: hesham
 */

#ifndef MCAL_SPI_SPI_CONFIG_H_
#define MCAL_SPI_SPI_CONFIG_H_

/*
 * 1- SPI Interrupt State
 * Options
 * 1- SPI_InterruptDisable
 * 2- SPI_InterruptEnable
 * */
#define SPI_InterruptState    SPI_InterruptDisable


/*
 * 2- SPI Peripheral  State
 * Options
 * 1- SPI_Disable
 * 2- SPI_Enable
 * */
#define SPI_State   SPI_Enable

/*
 * 3- SPI Data Order
 * Options
 * 1- SPI_MSBFirst
 * 2- SPI_LSBFirst
 * */
#define SPI_DataOrder   SPI_MSBFirst

/*
 * 4- SPI Master/Slave Select
 * Options
 * 1- SPI_Slave
 * 2- SPI_Master
 * */
#define SPI_ModeSelect            SPI_Master

/*
 * 5- Clock Polarity
 * Options
 * 1- SPI_RisingLead
 * 2- SPI_FallingLead
 * */
#define SPI_ClockPOL            SPI_RisingLead

/*
 * 6- Clock Phase
 * Options
 * 1- SPI_SampleFirst
 * 2- SPI_SetupFirst
 * */
#define SPI_ClockPHA           SPI_SampleFirst

/*
 * 7- Speed Type
 * Options
 * 1- SPI_NormalSpeed
 * 2- SPI_DoubleSpeed
 * */

#define SPI_SpeedType  SPI_NormalSpeed



/*
 * 8- Clock Rate
 *
 * if Normal Speed , Options :
 * 1-SPI_FOSC_4
 * 2-SPI_FOSC_16
 * 3-SPI_FOSC_64
 * 4-SPI_FOSC_64
 * if Double Speed , Options :
 * 1-SPI_FOSC_2
 * 2-SPI_FOSC_8
 * 3-SPI_FOSC_32
 * 4-SPI_FOSC_64
 *
 * 	*/

#define SPI_ClockRate    SPI_FOSC_16

























#endif /* MCAL_SPI_SPI_CONFIG_H_ */
