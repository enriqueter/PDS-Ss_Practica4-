/*
 * ADC.c
 *
 *  Created on: Mar 28, 2019
 *      Author: Alvaro Rocha ie703585@iteso.mx
 *      		Enrique Teran		 @iteso.mx
 */

#include "ADC.h"

void ADC_init()
{
	ADC_clock_gating();


	ADC0->CFG1 |= ADC_CFG1_MODE(1) | ADC_CFG1_ADICLK(0) | ADC_CFG1_ADIV(0x02);
	ADC0->CFG2 = ADC_CFG2_ADHSC(1);
	ADC0->SC3 = ADC_SC3_ADCO(1);
}

void ADC_clock_gating()
{
	GPIO_clock_gating(ADC_PORT);
	SIM->SCGC6 |= SIM_SCGC6_ADC0_MASK;

}

 uint16_t ADC_result(void)
 {
	 uint16_t adc_result;
	 ADC0->SC1[0] = ADC_SC1_ADCH(17);

	 while( (ADC0->SC1[0] & ADC_SC1_COCO_MASK) == 0)
	 {
	 	 adc_result = ADC0->R[0] - 2110;
	 }

	 return(adc_result);
 }

 uint8_t ADC_in_to_volt(uint16_t adc_in, uint8_t return_volt_digit)
 {
 	ADC_float_t volt_value;
 	uint8_t volt_units;
 	uint8_t volt_decimals;

 	/*!
 	 * Converts ADC read to a float number with the format:
 	 * [Vu][Vd].xx
 	 * Where Vu is the voltage input units
 	 * 		 Vd is the voltage input decimals
 	 */
 	volt_value = adc_in * ADC_CONVERT_CONSTANT;

 	if(ADC_RETURN_UNITS == return_volt_digit)
 	{
 		return (volt_units = (uint8_t)volt_value % 10);
 	}
 	else if(ADC_RETURN_DECIMALS == return_volt_digit)
 	{
 		return (volt_decimals = (uint8_t)(volt_value*10) % 10);
 	}

 	return(FALSE);
 }
