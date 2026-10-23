/**
 * @file
 * @author
 * @date
 */
#ifndef MCAL_TWI_TWI_INTERFACE_H_
#define MCAL_TWI_TWI_INTERFACE_H_

#include "TWI_Private.h"
#include "TWI_Config.h"

#if TWI_Mode==TWI_Master
/*Master Functions*/

/**
 * @fn     TWI_InitMaster
 * @brief  Initializes the TWI Module as Master device
 * @details
 * @note  Sets BitRate and Prescaller and Enable the TWI Peripheral
 */
void TWI_InitMaster();

/**
 *
 * @return
 */
u8 TWI_SendStartCondition();

u8 TWI_SendRepeatStart();

/**
 * @todo
 */
void TWI_SendStopCondition();
/*Address Packets Functions*/
/**
 *
 * @param SlaveAddess
 * @return
 */
u8 TWI_SendSlaveAddWithWrite(u8 SlaveAddess);
u8 TWI_SendSlaveAddWithRead(u8 SlaveAddess);
/*Data Packet*/
u8 TWI_MasterSendDataByte(u8 TxData);
u8 TWI_MasterReceiveDataByte(u8 *RxData);
#elif TWI_Mode==TWI_Slave
/*Slave Functions*/
void TWI_InitSlave();
u8 TWI_SlaveListen(u8 * TWIStatus);
u8 TWI_SlaveSendDataByte(u8 TxData);
u8 TWI_SlaveReceiveDataByte(u8 *RxData);
#endif
#endif /* MCAL_TWI_TWI_INTERFACE_H_ */
