/*
 * ADC.h
 *
 *  Created on: Mar 28, 2019
 *      Author: Andrea Perez Huizar, ie698276@iteso.mx
 */

#ifndef ADC_H_
#define ADC_H_

#include"General.h"

#define ADC_PORT GPIO_E
#define ADC_PIN bit_24

#define ADC_RETURN_UNITS 1
#define ADC_RETURN_DECIMALS 0

#define ADC_CONVERT_CONSTANT 0.00005081f

//Float variables//
typedef float ADC_float_t;

/*ADC initialization*/
void ADC_init(void);

/*ADC clockgating*/
void ADC_clock_gating(void);

/*ADC function that reads pin*/
 uint16_t ADC_result(void);


#endif /* ADC_H_ */

