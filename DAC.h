/**
	\file DAC.h
	\brief
		This is the header file for the DAC device driver.
	\author Santiago Soule and Enrique Teran
	\date	8/02/2018
 */

#ifndef DAC_H_
#define DAC_H_

#include "bits.h"
#define DAC0_clockGating_mask 0x1000;
#define DAC1_clockGating_mask 0x1001;

/*! This enumerated constant are used to select the PIT to be used*/

void DAC_clockGating();
void DAC_enable();
void DAC_output(uint16 value);

#endif /* DAC_H_ */
