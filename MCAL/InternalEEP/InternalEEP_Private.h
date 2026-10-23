/*
 * InternalEEP_Private.h
 *
 *  Created on: Sep 8, 2026
 *      Author: hesham
 */

#ifndef MCAL_INTERNALEEP_INTERNALEEP_PRIVATE_H_
#define MCAL_INTERNALEEP_INTERNALEEP_PRIVATE_H_

#include "../../LIB/std_types.h"

#define EEARL    *((volatile u8*)0x3E)
#define EEARH    *((volatile u8*)0x3F)
#define EEAR     *((volatile u16*)0x3E)
#define EEDR     *((volatile u8*)0x3D)
#define EECR     *((volatile u8*)0x3C)



#define EERE   0
#define EEWE   1
#define EEMWE  2
#define EEIE   3



#endif /* MCAL_INTERNALEEP_INTERNALEEP_PRIVATE_H_ */
