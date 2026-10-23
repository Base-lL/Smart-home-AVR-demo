/*
 * ADC_program.c
 *
 *  Created on: Aug 18, 2026
 *      Author: emad.yousry
 */

#include "../../LIB/std_types.h"
#include "../../LIB/bit_math.h"


#include "ADC_private.h"
#include "ADC_config.h"
#include "ADC_interface.h"

void ADC_vidInit(void)
{
	/*Configure Ref volt to use AVCC*/
//	CLR_BIT(ADMUX, ADMUX_REFS1);
//	SET_BIT(ADMUX, ADMUX_REFS0);
	ADMUX &= ADC_ADMUX_REF_VOLT_MASK;
	ADMUX |= ADC_AVCC_REF;

	/*Configure Data left adjustment*/
	SET_BIT(ADMUX, ADMUX_ADLAR);

	/*Configure clock*/
	ADCSRA &= ADC_PRESCALER_MASK;
	ADCSRA |= ADC_PRESCALER;


	/*Enbable ADC*/
	SET_BIT(ADCSRA, ADCSRA_ADEN);

}

u8 ADC_u8GetValue(u8 copy_u8Channel)
{
	/*Configure Channel*/
	ADMUX &= ADC_ADMUX_MUX_MASK;
	ADMUX |= copy_u8Channel;

	/*Trigger start conversion*/
	SET_BIT(ADCSRA, ADCSRA_ADSC);

	/*Wait until conversion complete (flat is set)*/
	while(GET_BIT(ADCSRA, ADCSRA_ADIF) == 0);

	/*Clear flag by writing 1*/
	SET_BIT(ADCSRA, ADCSRA_ADIF);

	return ADCH; // 8-bit
}




