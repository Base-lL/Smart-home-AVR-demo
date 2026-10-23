/**
 * @file   TWI_Private.h
 * @author Hesham Ahmed
 * @brief  Private Declaration , Registers , Status code for TWI
 * @date   Sep 7,2026
 * @version 1.0
 * @copyright IMT School
 * */

#ifndef MCAL_TWI_TWI_PRIVATE_H_
#define MCAL_TWI_TWI_PRIVATE_H_


#include "../../LIB/std_types.h"
/*========================================================================*/
/*=====================TWI Registers Definitions =========================*/
/*========================================================================*/
#define TWBR  *((volatile u8*)0x20) /**< TWI Bit Rate Register*/
#define TWSR  *((volatile u8*)0x21) /**< TWI Status Register */
#define TWAR  *((volatile u8*)0x22) /**< TWI Address Register (Store the Own Address form bit 1 to bit 7) */
#define TWDR  *((volatile u8*)0x23) /**< TWI Data Register*/
#define TWCR  *((volatile u8*)0x56) /**< TWI Control Register*/


/*========================================================================*/
/*=====================TWI Registers Bits ================================*/
/*========================================================================*/
/*TWAR Bits*/
#define TWGCE 0 /**< General Call Enable Bit */

/*TWSR Bits*/
#define TWPS0 0 /**< TWI Prescaler Bit 0*/
#define TWPS1 1 /**< TWI Prescaler Bit 1*/

/*TWCR Bits */
#define TWIE  0 /**< TWI Interrupt Enable  */
#define TWEN  2 /**< TWI Enable Bit */
#define TWWC  3 /**< TWI Write Collision Flag */
#define TWSTO 4 /**< TWI Stop Condition Bit */
#define TWSTA 5 /**< TWI Start Condition Bit */
#define TWEA  6 /**< TWI Enable Acknowledge Bit*/
#define TWINT 7 /**< TWI  Interrupt Bit*/
/************************************************/

/*========================================================================*/
/*=====================Configuration Definitions==========================*/
/*========================================================================*/
/*MCU Mode*/
#define TWI_Master  1
#define TWI_Slave   2

/*Prescaller Options*/
#define TWI_Prescaller1    0x00
#define TWI_Prescaller4    0x01
#define TWI_Prescaller16   0x02
#define TWI_Prescaller64   0x03

/*========================================================================*/
/*=====================TWI Status Codes ==================================*/
/*========================================================================*/

#define TWI_StatusMask     		             0xF8
#define TWI_StartConditionSuccess 		     0x08
#define TWI_ReStartConditionSuccess          0x10
#define TWI_SLAW_ACK                         0x18
#define TWI_SLAW_NACK                        0x20
#define TWI_Master_TxDataACK                 0x28
#define TWI_Master_TxDataNACK                0x30
#define TWI_SLAR_ACK                         0x40
#define TWI_SLAR_NACK                        0x48
#define TWI_Master_RxDataACK                 0x50
#define TWI_Master_RxDataNACK                0x58
#define TWI_SlaveRecivieAdd_ReqWrite         0x60  //Own SLA+W has been received; ACK has been returned
#define TWI_SlaveRecivieAdd_ReqRead      	 0xA8  //Own SLA+R has been received; ACK has been returned
#define TWI_SlaveDataRecivied_ACK        	 0x80 // Previously addressed with own SLA+W; data has been received; ACK has been returned
#define TWI_SlaveDataTransmite_ACK       	 0xB8 // Data byte in TWDR has been transmitted; ACK has been received


#define TWI_TIMEOUTMAX   50000UL
/*========================================================================*/
/*=====================TWI Errors States =================================*/
/*========================================================================*/
typedef enum
{
	TWI_NoError,
    TWI_StartErr,
	TWI_ReStartErr,
	TWI_SLAWithWriteErr,
	TWI_SLAWithReadErr,
	TWI_MasterSendDataErr,
	TWI_MasterRecivieDataErr,
	TWI_NullPtrErr,
	TWI_SlaveReqNotHandle,
	TWI_SlaveSendDataErr,
	TWI_SlaveRecivieDataErr,
	TWI_TIMEOUTError,
}TWI_ErrState_t;
































#endif /* MCAL_TWI_TWI_PRIVATE_H_ */
