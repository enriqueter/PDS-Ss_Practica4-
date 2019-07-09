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

	int16_t *ADC_ptr;
	int16_t *ADC_ptr_hold = 0;

	int16_t in_ADC[2000] = {};
	float hx[7] = {0,0,0,0,0,0,0};

	uint8_t ptr_mod = 0;

	//uint16_t out_DAC[7];
	uint8_t samp_hold = NULL;
	uint8_t samp_n = 7;
	uint8_t samp_n_modifier = 7;
	uint8_t index_k = NULL;
	int16_t convo_out[7];
	float convo;
	uint8_t cntr1 = NULL;


	float Amplitud_value = 0;
	uint8_t BTN_selector = FALSE;
	uint8_t Amp_increase = 10;
	uint8_t Sig_mod = FALSE;
	uint8_t Sig_select = FALSE;

	ADC_ptr = in_ADC;

    while(1)
    {



		BTN_selector = Buttons_get();

		if(GPIO_get_interrupt_status(GPIO_C))
		{
			switch(BTN_selector)
			{
				Buttons_clear();
				case BTN_1:
				{
					if(Amp_increase == AMP_MAX)
					{
						Amp_increase = Amp_increase;
					}
					else
					{
						Amp_increase++;
					}
				}
				break;
				case BTN_0:
				{
					if(Amp_increase == AMP_MIN)
					{
						Amp_increase = Amp_increase;
					}
					else
					{
						Amp_increase--;
					}
				}
					break;
				case BTN_2:
					Sig_mod = ~(Sig_mod); //La señal se modifica
					break;
				case BTN_3:
					Sig_select = ~(Sig_select); // la señal se convoluciona con H1
					break;
				default:
					Amp_increase = NULL;
					break;
			}
		}

		Amplitud_value = AMP_STEP * Amp_increase;


		float ADC_amp_temp = 0;
		for(cntr1=0 ; cntr1<2000 ; cntr1++)
		{
//			ADC_amp_temp = ADC_result() * Amplitud_value;
			in_ADC[cntr1]= ADC_result();

		}//for(cntr1=0 ; cntr1<7 ; cntr1++)
if(Sig_mod)
{
		for(cntr1=0 ; cntr1<7 ; cntr1++)
		{
			convo = ZERO;

			while(samp_hold <= (samp_n-samp_n_modifier))
			{

				if(Sig_select)
				{
					convo = (h1[index_k] * in_ADC[samp_hold - index_k]) + convo;
				}
				else
				{
					convo = (h2[index_k] * in_ADC[samp_hold - index_k]) + convo;
				}

				samp_hold++;
				index_k++;
			}//while(samp_hold <= (samp_n-samp_n_modifier))

			samp_n_modifier--;
			index_k = NULL;
			samp_hold = NULL;

			convo_out[cntr1] = (int16_t)convo + 2110;
		}

		samp_n_modifier = 7;

		for(cntr1=0 ; cntr1<7 ; cntr1++)
		{
			DAC_output(convo_out[cntr1] - 2110);
		}//for(cntr1=0 ; cntr1<7 ; cntr1++)
}
else
{
		for(cntr1=0 ; cntr1<7 ; cntr1++)
		{
			DAC_output(in_ADC[cntr1] - 2110);
		}//for(cntr1=0 ; cntr1<7 ; cntr1++)
}
		in_ADC[7] = NULL;


    }//while(1)
    return (0);
}
