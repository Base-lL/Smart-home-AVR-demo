/*
 * GIE_program.c
 *
 *  Created on: Aug 13, 2026
 *      Author: emad.yousry
 */

#include "../../LIB/bit_math.h"
#include "../../LIB/std_types.h"


#include "GIE_private.h"
#include "GIE_interface.h"


void GIE_vidEnable(void)
{
	SET_BIT(SREG, SREG_I);
}

void GIE_vidDisable(void)
{
	CLR_BIT(SREG, SREG_I);
}
