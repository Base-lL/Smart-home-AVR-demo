/*
 * ADC_config.h
 *
 *  Created on: Aug 18, 2026
 *      Author: emad.yousry
 */

#ifndef MCAL_ADC_ADC_CONFIG_H_
#define MCAL_ADC_ADC_CONFIG_H_


#define ADC_AVCC_REF        0b010000000
#define ADC_256_REF         0b110000000

/*
 * ADC_AVCC_REF
 * ADC_256_REF
 * */
#define ADC_ADMUX_REF_VOLT_MASK 0b00111111
#define ADC_ADMUX_REF_VOLT  ADC_AVCC_REF


#define DIV_FACTOR_2         0
#define DIV_FACTOR_4         2
#define DIV_FACTOR_8         3
#define DIV_FACTOR_128       7 // 0b00000111

#define ADC_PRESCALER_MASK  0b11111000
#define ADC_PRESCALER  DIV_FACTOR_128



#define ADC_ADMUX_MUX_MASK   0b11100000

#define ADC0_SINGLE_ENDED    0

#define ADC_ADMUX_MUX_VALUE  ADC0_SINGLE_ENDED


#endif /* MCAL_ADC_ADC_CONFIG_H_ */
