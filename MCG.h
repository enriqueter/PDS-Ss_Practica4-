/*
 * MCG.h
 *
 *  Created on: 01/10/2017
 *      Author: jlpe
 */

#ifndef MCG_H_
#define MCG_H_

#include "MK64F12.h"
#include "stdint.h"
#include "stdio.h"
#include "bits.h"

/*!
 * General defines
 */
#define CLK_FREQ_HZ 50000000  /* CLKIN0 frequency */
#define SLOW_IRC_FREQ 32768	/*This is the approximate value for the slow irc*/
#define FAST_IRC_FREQ 4000000 /*This is the approximate value for the fast irc*/
#define EXTERNAL_CLOCK 0 /*It defines an external clock*/
#define PLL_ENABLE 1 /**PLL is enabled*/
#define PLL_DISABLE 0 /**PLL is disabled*/
#define CRYSTAL_OSC 1  /*It defines an crystal oscillator*/
#define LOW_POWER 0     /* Set the oscillator for low power mode */
#define SLOW_IRC 0 		/* Set the slow IRC */
#define FAT_IRC 1 		/* Set the fast IRC */
#define CLK0_TYPE 0     /* Crystal or canned oscillator clock input */
#define PLL0_PRDIV 25    /* PLL predivider value */
#define PLL0_VDIV 30    /* PLL multiplier value*/

// Constants for use in pll_init
#define NO_OSCINIT 0
#define OSCINIT 1

#define OSC_0 0
#define OSC_1 1

#define LOW_POWER 0
#define HIGH_GAIN 1

#define CANNED_OSC  0
#define CRYSTAL 1

#define PLL_0 0
#define PLL_1 1

#define PLL_ONLY 0
#define MCGOUT 1

// MCG Mode defines

#define BLPI 1
#define FBI  2
#define FEI  3
#define FEE  4
#define FBE  5
#define BLPE 6
#define PBE  7
#define PEE  8

// IRC defines
#define SLOW_IRC 0
#define FAST_IRC 1


/** Macros for debugging*/
//#define DEBUG

//#define PLL_DIRECT_INIT

typedef float mcg_float_t;
uint8_t fll_rtc_init(uint8_t, uint8_t);


uint32_t init_mcg(uint8_t mcg_init, uint32_t IRC_freq, uint8_t IRC);
// prototypes
void rtc_as_refclk(void);
uint32_t fee_fei(uint32_t slow_irc_freq);
uint32_t fei_fbe(uint32_t crystal_val, uint8_t hgo_val, uint8_t erefs_val);
uint32_t fbe_fei(uint32_t slow_irc_freq);
uint32_t fei_fbi(uint32_t irc_freq, uint8_t irc_select);
uint32_t fbi_fei(uint32_t slow_irc_freq);
uint32_t fbe_pbe(uint32_t crystal_val, int8_t prdiv_val, int8_t vdiv_val);
uint32_t pbe_pee(uint32_t crystal_val);
uint32_t pee_pbe(uint32_t crystal_val);
uint32_t pbe_fbe(uint32_t crystal_val);
uint32_t fbe_fbi(uint32_t irc_freq, uint8_t irc_select);
uint32_t fbi_fbe(uint32_t crystal_val, uint8_t hgo_val, uint8_t erefs_val);
uint32_t fbi_fee(uint32_t crystal_val, uint8_t hgo_val, uint8_t erefs_val);
uint32_t fbe_fee(uint32_t crystal_val);
uint32_t fee_fbe(uint32_t crystal_val);
uint32_t pbe_blpe(uint32_t crystal_val);
uint32_t blpe_pbe(uint32_t crystal_val, int8_t prdiv_val, int8_t vdiv_val);
uint32_t blpe_fbe(uint32_t crystal_val);
uint32_t fbi_blpi(uint32_t irc_freq, uint8_t irc_select);
uint32_t blpi_fbi(uint32_t irc_freq, uint8_t irc_select);
uint32_t fei_fee(uint32_t crystal_val, uint8_t hgo_val, uint8_t erefs_val);
uint32_t fee_fbi(uint32_t irc_freq, uint8_t irc_select);
uint32_t fbe_blpe(uint32_t crystal_val);
uint32_t fei_fee_rtc(uint32_t rtc_freq);
uint32_t fee_fei_rtc(uint32_t slow_irc_freq);

uint32_t pll_init(uint32_t crystal_val, uint8_t hgo_val, uint8_t erefs_val, int8_t prdiv_val, int8_t vdiv_val, uint8_t mcgout_select);

uint32_t fll_freq(uint32_t fll_ref);
uint8_t what_mcg_mode(void);
uint8_t atc(uint8_t irc_select, uint32_t irc_freq, uint32_t mcg_out_freq);
void clk_monitor_0(uint8_t en_dis);



#endif /* MCG_H_ */
