/**
 * @file    RGB_PWM.c
 * @brief   Application entry point.
 *
 * @ this is the code for the first DSP exercise.
 * 		Use the ADC to read an analog audio signal.
 * 		Do algorithm to filter the signal.
 * 		Use DAC to output the filtered signal.
 *
 * 		 *  Created on: Jun 14, 2019
 *      Author: - Alvaro Rocha ie703585@iteso.mx
 *      		-
 */
#include "ADC_Module.h"
#include "DAC.h"
#include "bits.h"
#include "MCG.h"
#include "Buttons.h"


#define H1 0x1F
#define H2 0x2F
#define AMP_MAX 10
#define AMP_MIN 0
#define AMP_STEP 0.10f
/********* DEFINITIONS *****************/

uint32_t mcg_clk = 0;



int main(void)
{

	BTN_init();
	PORTC_callback_update(Buttons_decode);
	Buttons_clear();
	GPIO_get_interrupt_status(GPIO_C);
	ADC_init();
	NVIC_priorities();
	DAC_clockGating();
	DAC_enable();
	mcg_clk = init_mcg(PBE, FAST_IRC_FREQ, FAST_IRC);


	/* Array for the ADC input and max R value  */
	int16_t in_ADC[6000] = {};

	/* formula */

	//uint16_t out_DAC[7];

	uint8_t cntr1 = NULL;

	uint8_t x = 0;
	uint8_t a = 0;
	uint8_t b = 0;
	uint8_t c = 0;
	int16_t out_ECHO = 0;
	uint16_t R = 2000;
	uint8_t BTN_selector = FALSE;





    while(1)
    {





			in_ADC[x]= ADC_result();

			/*  calculo de   salida*/
			out_ECHO = in_ADC[x] + a*in_ADC[x-R] +b*in_ADC[x-2R] + c*in_ADC[x-3R];

			DAC_output(out_ECHO - 2110);
