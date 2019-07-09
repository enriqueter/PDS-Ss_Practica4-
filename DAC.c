/*
 * DAC.c
 *
 *  Created on: Feb 22, 2018
 *      Author: SANTIAGO
 */

#include "DAC.h"
#include "bits.h"
#include "PIT.h"
#include "NVIC.h"
#include "GPIO.h"


void DAC_clockGating(){
	SIM->SCGC2 |= DAC0_clockGating_mask;
}

void DAC_enable(){
	DAC0->C0|=0xC0;
}
void DAC_output(uint16 value){
	uint8 low = value & 0x00FF;
	uint8 high = value>>8;
	DAC0->DAT[0].DATL= low;
	DAC0->DAT[0].DATH= high;
}
