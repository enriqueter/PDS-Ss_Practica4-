/**
  \file
  	  Menu_Buttons.h
 	\brief
		This is the header file for the control of push buttons using GPIO.
		description of functions can be found here
   	  \date Mar 16, 2018
      \author: Santiago Soule & Enrique Teran
      * IE702333 & IE701909
 */

#ifndef BUTTONS_H_
#define BUTTONS_H_

#include "bits.h"

#define BTN0_MASK 0x01
#define BTN1_MASK 0x04
#define BTN2_MASK 0x80
#define BTN3_MASK 0x20
#define BTN4_MASK 0xFF
#define BTN5_MASK 0xFF


#define BTN0 5
#define BTN1 7
#define BTN2 0
#define BTN3 2
#define BTN4 9
#define BTN5 5


typedef enum { BTN_0, BTN_1, BTN_2, BTN_3, BTN_4, BTN_5} BTN_option;

/* brief
 * This function initializes the Button Control.
 */
void BTN_init();

/* brief
 * this function reads the PORT_C, filters the data and decodes which button was pressed
 * return value is the button that was pressed as an integer from 0 to 5
 */
uint8 Read_BTN ();

uint8_t Buttons_clear(void);

uint8_t Buttons_get(void);

void Buttons_decode(uint8_t value);



#endif /* BUTTONS_H_ */
