/**
  \file
  	  Menu_Buttons.c
 	\brief
		This is the implementation file for the control of push buttons using GPIO.
		implementation of functions can be found here
   	  \date Mar 16, 2018
      \author: Santiago Soule & Enrique Teran
      * IE702333 & IE701909
 */


#include "Buttons.h"
#include "GPIO.h"
#include "bits.h"


static 	uint8_t buttons_decode_output;

void BTN_init(){
	gpio_pin_control_register_t pinControlRegisterGPIO_C_BTN = GPIO_MUX1|GPIO_PE|GPIO_PS|INTR_RISING_EDGE;	//BTN CONTROL
	GPIO_clock_gating(GPIO_C); //BTN CONTROL


	GPIO_pin_control_register(GPIO_C, BTN0, &pinControlRegisterGPIO_C_BTN);
	GPIO_pin_control_register(GPIO_C, BTN1, &pinControlRegisterGPIO_C_BTN);
	GPIO_pin_control_register(GPIO_C, BTN2, &pinControlRegisterGPIO_C_BTN);
	GPIO_pin_control_register(GPIO_C, BTN3, &pinControlRegisterGPIO_C_BTN);
	GPIO_pin_control_register(GPIO_C, BTN4, &pinControlRegisterGPIO_C_BTN);

	GPIO_clear_pin(GPIO_C, BTN0);
	GPIO_clear_pin(GPIO_C, BTN1);
	GPIO_clear_pin(GPIO_C, BTN2);
	GPIO_clear_pin(GPIO_C, BTN3);
	GPIO_clear_pin(GPIO_C, BTN4);


	GPIO_data_direction_pin(GPIO_C,GPIO_INPUT, BTN0);
	GPIO_data_direction_pin(GPIO_C,GPIO_INPUT, BTN1);
	GPIO_data_direction_pin(GPIO_C,GPIO_INPUT, BTN2);
	GPIO_data_direction_pin(GPIO_C,GPIO_INPUT, BTN3);
	GPIO_data_direction_pin(GPIO_C,GPIO_INPUT, BTN4);
	GPIO_data_direction_pin(GPIO_C,GPIO_INPUT, BTN5);

}

uint8_t Buttons_clear(void)
{
	buttons_decode_output = ZERO;
	return buttons_decode_output;
}

uint8_t Buttons_get(void)
{

	return buttons_decode_output;
}

void Buttons_decode(uint8_t value)
{

	switch(value)
	{
		case BTN0_MASK:
			buttons_decode_output = BTN_0;
			break;
		case BTN1_MASK:
			buttons_decode_output = BTN_1;
			break;
		case BTN2_MASK:
			buttons_decode_output = BTN_2;
			break;
		case BTN3_MASK:
			buttons_decode_output = BTN_3;
			break;
		case BTN4_MASK:
			buttons_decode_output = BTN_4;
			break;
		case BTN5:
			buttons_decode_output = BTN_5;
			break;
		default:
			break;
	}
}

