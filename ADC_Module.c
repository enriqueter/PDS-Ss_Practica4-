/*
 * ADC_Module.c
 *
 *  Created on: Jun 14, 2019
 *      Author: Alvaro Rocha ie703585@iteso.mx
 */
#include "ADC_Module.h"

//ADC
static uint8_t adc_module_status = FALSE;
////Variables for PWM//
uint16_t red_ADC;
uint16_t green_ADC;
uint16_t blue_ADC;
uint8_t result_index = SEVEN;
uint8_t index_handler = ZERO;
uint16_t result_array[SEVEN];

//Module start
void ADC_Module_start(void)
{
	adc_module_status = TRUE;
}

void ADC_Module_stop(void)
{
	adc_module_status = FALSE;
}

void ADC_update_result(uint16_t value)
{
	if(index_handler == result_index)
	{
		 ADC0->SC1[0] = ADC_SC1_ADCH(63);

		for(index_handler = 0 ; index_handler < result_index; index_handler++)
		{
			printf("result[");
			printf("%d", index_handler);
			printf("] = ");
			printf("%d\n", result_array[index_handler]);
		}
		index_handler = ZERO;
	}
	else
	{
		result_array[index_handler] = value;
		index_handler = index_handler + ONE;
	}
}
