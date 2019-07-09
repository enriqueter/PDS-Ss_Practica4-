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



#define SAMPLES 25000
#define OFFSET 	2110


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
	float in_ADC[25000] = {};

	/* formula */

	uint8_t cntr1 = NULL;

	uint8_t n = 0;

	float out_ECHO = 0;


	uint8_t BTN_selector = FALSE;
	uint8_t BTN_Delayctr = FALSE;
	uint8_t BTN_Factorctr = FALSE;

	uint16_t R = 2000;
	float SCALE_1  = 0.7;
	float SCALE_2  = 0.49;	// SCALE_1^2
	float SCALE_3  = 0.343;	// SCALE_1^3

    while(1)
    {
    	BTN_selector = Buttons_get();
    	if(GPIO_get_interrupt_status(GPIO_C))
    	{
    		if(BTN_selector = BTN_0){    /* Button 0 to modify delay*/

    			BTN_Delayctr++;
    		    if(BTN_Delayctr < 8 )
    		    {
    		    		R = R +1000;
    		    }else if(BTN_Delayctr > 8 )
    		    {
    		    	BTN_Delayctr = NULL;
    		    }
    		}
    		else if(BTN_selector = BTN_1)  /* Button 1 to modify factor */
    		{
    			BTN_Factorctr++;      /* Factor > 1 para que se disminuya */
    			if(BTN_Factorctr < 5)
    			{
    				SCALE_1 = SCALE_1 * (BTN_Factorctr * 0.2);
    				SCALE_2 = SCALE_2 * (BTN_Factorctr * 0.2);
    				SCALE_3 = SCALE_3 * (BTN_Factorctr * 0.2);
    			}else if(BTN_Factorctr > 5)
    			{
    				BTN_Factorctr = NULL;
    			}
    		}
    		else
    		{
    			/* Do nothing*/
    		}


    	}
    	in_ADC[n] = ADC_result(); // SI SE NECESITA UTILIZAR FTM COMO TRIGGER PARA EL ADC Y TENER MEJOR CONTROL

		/*  calculo de   salida*/
		out_ECHO = (in_ADC[n]) + (SCALE_1 * in_ADC[n - R]) + (SCALE_2 * in_ADC[n - 2*R]) + (SCALE_3 * in_ADC[n - 3*R]);

		DAC_output(out_ECHO + OFFSET);

		if(n == SAMPLES)
		{
			n = ZERO;
		}
		else
		{
			n++;
		}



    }

    return (0);
}
