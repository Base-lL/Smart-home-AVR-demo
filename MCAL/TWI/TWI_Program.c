/*
 * TWI_Program.c
 *
 *  Created on: Sep 7, 2026
 *      Author: hesham
 */


#include "std_types.h"
#include "bit_math.h"
#include <stddef.h>

#include "TWI_Private.h"
#include "TWI_Config.h"
#include "TWI_Interface.h"
#if TWI_Mode==TWI_Master
void TWI_InitMaster()
{
	/**< @brief 1- Set the Bit Rate (SCL Frequency )*/
	TWBR = TWI_BitRate;
	/**< @brief 2- Clear the previous Prescaler and set the new prescalar value */
	TWSR = (TWSR &~0x03)|(TWI_Prescaller&0x03);
	/**< @brief 3- Assign the Master's Own Address */
	TWAR = TWI_MyOwnAddress << 1 ; /**< @todo */
	/**< @brief 4- Enable the TWI peripheral*/
	SET_BIT(TWCR,TWEN);
}

u8 TWI_SendStartCondition()
{
	u8 ErrorState = TWI_NoError ;
	u32 LocalTimeOut =   0 ;
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while(GET_BIT(TWCR,TWINT)==0 && LocalTimeOut< TWI_TIMEOUTMAX)
	{
		LocalTimeOut++;
	}
	if(LocalTimeOut>=TWI_TIMEOUTMAX)
	{
		ErrorState = TWI_TIMEOUTError;
		return ErrorState;
	}
	if((TWSR & TWI_StatusMask)!= TWI_StartConditionSuccess)
	{
		// Error
		ErrorState = TWI_StartErr;
	}
	else
	{
		// Clear for Start Condition
	}
	return ErrorState;
}
u8 TWI_SendRepeatStart()
{
	u8 ErrorState = TWI_NoError;
	u32 LocalTimeOut =   0 ;
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while(GET_BIT(TWCR,TWINT)==0&& LocalTimeOut< TWI_TIMEOUTMAX)
	{
		LocalTimeOut++;
	}
	if(LocalTimeOut>=TWI_TIMEOUTMAX)
	{
		ErrorState = TWI_TIMEOUTError;
		return ErrorState;
	}
	if((TWSR&TWI_StatusMask)!=TWI_ReStartConditionSuccess)
	{
		ErrorState = TWI_ReStartErr;
	}
	else
	{

	}
	return ErrorState;
}

void TWI_SendStopCondition()
{

	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
	while(GET_BIT(TWCR, TWSTO) == 1);
}



u8 TWI_SendSlaveAddWithWrite(u8 SlaveAddess)
{
	u8 ErrorState = TWI_NoError;
	u32 LocalTimeOut =   0 ;
	TWDR= (SlaveAddess<<1);
	CLR_BIT(TWDR,0);
	TWCR = (1<<TWINT)|(1<<TWEN);

	while(GET_BIT(TWCR,TWINT)==0&& LocalTimeOut< TWI_TIMEOUTMAX)
	{
		LocalTimeOut++;
	}
	if(LocalTimeOut>=TWI_TIMEOUTMAX)
	{
		ErrorState = TWI_TIMEOUTError;
		return ErrorState;
	}
	if((TWSR&TWI_StatusMask)!=TWI_SLAW_ACK)
	{
		ErrorState=TWI_SLAWithWriteErr;
	}

	return ErrorState;
}

u8 TWI_SendSlaveAddWithRead(u8 SlaveAddess)
{
	u8 ErrorState = TWI_NoError;
	u32 LocalTimeOut =   0 ;
	TWDR= (SlaveAddess<<1);
	SET_BIT(TWDR,0);
	TWCR = (1<<TWINT)|(1<<TWEN);
	while(GET_BIT(TWCR,TWINT)==0&& LocalTimeOut< TWI_TIMEOUTMAX)
	{
		LocalTimeOut++;
	}
	if(LocalTimeOut>=TWI_TIMEOUTMAX)
	{
		ErrorState = TWI_TIMEOUTError;
		return ErrorState;
	}
	// Check status
	if((TWSR&TWI_StatusMask)!=TWI_SLAR_ACK)
	{
		ErrorState=TWI_SLAWithReadErr;
	}


	return ErrorState;
}

u8 TWI_MasterSendDataByte(u8 TxData)
{
	u8 ErrorState = TWI_NoError;

	TWDR = TxData;
	TWCR = (1<<TWINT)|(1<<TWEN);
	u32 LocalTimeOut =   0 ;
	while(GET_BIT(TWCR,TWINT)==0&& LocalTimeOut< TWI_TIMEOUTMAX)
	{
		LocalTimeOut++;
	}
	if(LocalTimeOut>=TWI_TIMEOUTMAX)
	{
		ErrorState = TWI_TIMEOUTError;
		return ErrorState;
	}

	if((TWSR&TWI_StatusMask)!=TWI_Master_TxDataACK)
	{
		ErrorState=TWI_MasterSendDataErr;
	}
	return ErrorState;


}
u8 TWI_MasterReceiveDataByte(u8 *RxData)
{
	u8 ErrorState = TWI_NoError;
	u32 LocalTimeOut =   0 ;
	if(RxData!=NULL)
	{
		TWDR = 0 ;
		TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);

		while(GET_BIT(TWCR,TWINT)==0&& LocalTimeOut< TWI_TIMEOUTMAX)
		{
			LocalTimeOut++;
		}
		if(LocalTimeOut>=TWI_TIMEOUTMAX)
		{
			ErrorState = TWI_TIMEOUTError;
			return ErrorState;
		}
		// Check Status
		if((TWSR&TWI_StatusMask)!=TWI_Master_RxDataACK)
		{
			ErrorState=TWI_MasterRecivieDataErr;
		}
		else
		{
			// read Data
			*RxData = TWDR;
		}

	}
	else
	{
		ErrorState = TWI_NullPtrErr;
	}
	return ErrorState;


}

//---------------------------------------------------------
#elif TWI_Mode==TWI_Slave
void TWI_InitSlave()
{
	// Update the My Own Address
	TWAR = (TWI_MyOwnAddress<<1);
	TWCR = (1<<TWEN) |(1<<TWEA);
}
u8 TWI_SlaveListen(u8 * TWIStatus)
{
	u8 ErrorState = TWI_NoError;
	u32 LocalTimeOut =   0 ;
	while(GET_BIT(TWCR,TWINT)==0 && LocalTimeOut< TWI_TIMEOUTMAX)
	{
		LocalTimeOut++;
	}
	if(LocalTimeOut>=TWI_TIMEOUTMAX)
	{
		ErrorState = TWI_TIMEOUTError;
		return ErrorState;
	}
	// Read for Bus status
	if(TWIStatus!=NULL)
	{
		*TWIStatus =  TWSR & TWI_StatusMask;
		if(*TWIStatus==TWI_SlaveRecivieAdd_ReqWrite)
		{
			*TWIStatus = TWI_SlaveRecivieAdd_ReqWrite;
		}
		else if (*TWIStatus==TWI_SlaveRecivieAdd_ReqRead)
		{
			*TWIStatus = TWI_SlaveRecivieAdd_ReqRead;
		}
		else
		{
			ErrorState = 	TWI_SlaveReqNotHandle;
		}
	}
	else
	{
		ErrorState=TWI_NullPtrErr;
	}
	return ErrorState;
}
u8 TWI_SlaveSendDataByte(u8 TxData)
{
	u8 ErrorState = TWI_NoError;
	u32 LocalTimeOut =   0 ;
	TWDR = TxData;
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
	// Wait Flag
	while(GET_BIT(TWCR,TWINT)==0 && LocalTimeOut< TWI_TIMEOUTMAX)
	{
		LocalTimeOut++;
	}
	if(LocalTimeOut>=TWI_TIMEOUTMAX)
	{
		ErrorState = TWI_TIMEOUTError;
		return ErrorState;
	}
	// Check Status
	if((TWSR&TWI_StatusMask)!= TWI_SlaveDataTransmite_ACK)
	{
		ErrorState = TWI_SlaveSendDataErr;
	}

	return ErrorState;
}
u8 TWI_SlaveReceiveDataByte(u8 *RxData)
{
	u8 ErrorState = TWI_NoError;
	u32 LocalTimeOut =   0 ;
	if(RxData!=NULL)
	{
		TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
		while(GET_BIT(TWCR,TWINT)==0&& LocalTimeOut< TWI_TIMEOUTMAX)
		{
			LocalTimeOut++;
		}
		if(LocalTimeOut>=TWI_TIMEOUTMAX)
		{
			ErrorState = TWI_TIMEOUTError;
			return ErrorState;
		}
		if((TWSR&TWI_StatusMask)!= TWI_SlaveDataRecivied_ACK)
		{
			ErrorState = TWI_SlaveRecivieDataErr;
		}
		else
		{
			*RxData=TWDR;
		}
	}
	else
	{
		ErrorState =  TWI_NullPtrErr;
	}
	return ErrorState;
}

#endif



