/*
 * ADC_Module.h
 *
 *  Created on: Mar 29, 2019
 *      Author: Andrea Perez Huizar, ie698276@iteso.mx
 */
#ifndef ADC_MODULE_H_
#define ADC_MODEULE_H_

#include "ADC.h"




//Module control//
#define ADC_MODULE_OFF 0x00
#define ADC_MODULE_ON 0x01


void ADC_Module_start(void);


void ADC_Module_stop(void);

void ADC_update_result(uint16_t new_result);

#endif //* ADC_MODULE_H_ *//
