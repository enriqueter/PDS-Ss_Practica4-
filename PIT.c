/**
 * @file    PIT.c
 * @brief   Application entry point.
 *
 * Author: Andrea Perez Huizar ie698276@iteso.mx & Alvaro A. Rocha Robles, ie703585@iteso.mx
 * 28/02/2019. Zapopan, Jal.
 */

#include "PIT.h"
#include "bits.h"
#include "MK64F12.h"

#define CALLBACKS_ACTIVE ONE

static void (*pit_ch0_callback)(void) = ZERO;
static void (*pit_ch1_callback)(void) = ZERO;
static void (*pit_ch2_callback)(void) = ZERO;
static void (*pit_ch3_callback)(void) = ZERO;

static uint8_t pit0_intr_flag = FALSE;
static uint8_t pit1_intr_flag = FALSE;
static uint8_t pit2_intr_flag = FALSE;
static uint8_t pit3_intr_flag = FALSE;


//	P I T   I N T E R R U P T   S E C T I O N //

//PIT CALLBACK UPDATERS
void PIT0_callback_update(void (*handler)(void))
{
	pit_ch0_callback = handler;
}

void PIT1_callback_update(void (*handler)(void))
{
	pit_ch1_callback = handler;
}

void PIT2_callback_update(void (*handler)(void))
{
	pit_ch2_callback = handler;
}

void PIT3_callback_update(void (*handler)(void))
{
	pit_ch3_callback = handler;
}

//PIT ISR HANDLERS
void PIT0_IRQHandler()
{
	volatile uint32_t dummyRead;
	PIT->CHANNEL[0].TFLG |= PIT_TFLG_TIF_MASK;
	dummyRead = PIT->CHANNEL[0].TCTRL;	//read control register for clear PIT flag, this is silicon bug
	pit1_intr_flag = TRUE;

#if CALLBACKS_ACTIVE
	pit_ch0_callback();
#endif
}

void PIT1_IRQHandler()
{
	volatile uint32_t dummyRead;
	PIT->CHANNEL[1].TFLG |= PIT_TFLG_TIF_MASK;
	dummyRead = PIT->CHANNEL[1].TCTRL;	//read control register for clear PIT flag, this is silicon bug
	pit1_intr_flag = TRUE;

#if CALLBACKS_ACTIVE
	pit_ch1_callback();
#endif
}

void PIT2_IRQHandler()
{
	volatile uint32_t dummyRead;
	PIT->CHANNEL[2].TFLG |= PIT_TFLG_TIF_MASK;
	dummyRead = PIT->CHANNEL[2].TCTRL;	//read control register for clear PIT flag, this is silicon bug
	pit2_intr_flag = TRUE;

#if CALLBACKS_ACTIVE
	pit_ch2_callback(); //LED control
#endif
}

void PIT3_IRQHandler()
{
	volatile uint32_t dummyRead;
	PIT->CHANNEL[3].TFLG |= PIT_TFLG_TIF_MASK;
	dummyRead = PIT->CHANNEL[3].TCTRL;	//read control register for clear PIT flag, this is silicon bug
	pit3_intr_flag = TRUE;

#if CALLBACKS_ACTIVE
	pit_ch3_callback(); //LED control
#endif
}

//PIT INTERRUPT FLAG HANDLERS
uint8_t PIT_get_interrupt_flag_status(PIT_timer_t pit)
{
	uint8_t pit_intr_flag;
	switch(pit)
	{
		case PIT_0:
			pit_intr_flag = pit0_intr_flag;
		break;
		case PIT_1:
			pit_intr_flag = pit1_intr_flag;
		break;
		case PIT_2:
			pit_intr_flag = pit2_intr_flag;
		break;
		case PIT_3:
			pit_intr_flag = pit3_intr_flag;
		break;
		default:
			break;
	}
	return pit_intr_flag;
}

void PIT_clear_interrupt_flag(PIT_timer_t pit)
{
	switch(pit)
	{
		case PIT_0:
			pit0_intr_flag = FALSE;
			break;
		case PIT_1:
			pit1_intr_flag = FALSE;
		break;
		case PIT_2:
			pit2_intr_flag = FALSE;
		break;
		case PIT_3:
			pit3_intr_flag = FALSE;
		break;
		default:
		break;
	}
}

////////////////////////////////////////////////////////////////////////////////////////

// P I T  C O N T R O L  S E C T I O N //

void PIT_init(void)
{
	PIT_clock_gating();
	PIT_enable();
}

void PIT_clock_gating(void)
{
	SIM->SCGC6 |= SIM_SCGC6_PIT_MASK;
	PIT->MCR = 0;
}

void PIT_enable(void)
{
	PIT->MCR  |= PIT_MCR_FRZ_MASK;
	PIT->MCR &= ~PIT_MCR_MDIS_MASK; /* Enable PIT*/
}

void PIT_delay(PIT_timer_t pit_timer, PIT_float_t system_clock , PIT_float_t delay)
{
	uint32_t LDVAL = 0;
	PIT_float_t clock_period = 0.0F;
	system_clock = system_clock /2;
	clock_period = (1/system_clock);
	LDVAL = (uint32_t)(delay / clock_period);
	LDVAL = LDVAL - 1;

	switch(pit_timer)
	{
		case PIT_0:
			PIT->CHANNEL[0].LDVAL = LDVAL;
			PIT_enable_interrupt(PIT_0);
		break;
		case PIT_1:
			PIT->CHANNEL[1].LDVAL = LDVAL;
			PIT_enable_interrupt(PIT_1);
		break;
		case PIT_2:
			PIT->CHANNEL[2].LDVAL = LDVAL;
			PIT_enable_interrupt(PIT_2);
		break;
		case PIT_3:
			PIT->CHANNEL[3].LDVAL = LDVAL;
			PIT_enable_interrupt(PIT_3);
		break;
		default:
		break;
		}
}

void PIT_enable_interrupt(PIT_timer_t pit)
{
	switch(pit)
	{
		case PIT_0:
		{
			PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TIE_MASK;//enables PIT timer interrupt
			PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TEN_MASK;//enables timer0
		}
		break;
		case PIT_1:
		{
			PIT->CHANNEL[1].TCTRL |= PIT_TCTRL_TIE_MASK;//enables PIT timer interrupt
			PIT->CHANNEL[1].TCTRL |= PIT_TCTRL_TEN_MASK;//enables timer1
		}
		break;
		case PIT_2:
		{
			PIT->CHANNEL[2].TCTRL |= PIT_TCTRL_TIE_MASK;//enables PIT timer interrupt
			PIT->CHANNEL[2].TCTRL |= PIT_TCTRL_TEN_MASK;//enables timer1
		}
		break;
		case PIT_3:
		{
			PIT->CHANNEL[3].TCTRL |= PIT_TCTRL_TIE_MASK;//enables PIT timer interrupt
			PIT->CHANNEL[3].TCTRL |= PIT_TCTRL_TEN_MASK;//enables timer1
		}
		break;
		default:
			break;
	}
}

void PIT_stop(PIT_timer_t pit)
{
	switch(pit)
	{
		case PIT_0:
		{
			PIT->CHANNEL[0].TCTRL &= !PIT_TCTRL_TEN_MASK;//disables timer0
		}
		break;

		case PIT_1:
		{
			PIT->CHANNEL[1].TCTRL &= !PIT_TCTRL_TEN_MASK;//disables timer1
		}
		break;

		case PIT_2:
		{
			PIT->CHANNEL[2].TCTRL &= !PIT_TCTRL_TEN_MASK;//disables timer2
		}
		break;

		case PIT_3:
		{
			PIT->CHANNEL[3].TCTRL &= !PIT_TCTRL_TEN_MASK;//disables timer2
		}
		break;

		default:
			break;
	}
}

void PIT_disable_interrupt(PIT_timer_t pit)
{
	switch(pit)
	{
		case PIT_0:
		{
			PIT->CHANNEL[0].TCTRL |= !PIT_TCTRL_TIE_MASK;//disables PIT timer interrupt
		}
		break;

		case PIT_1:
		{
			PIT->CHANNEL[1].TCTRL |= !PIT_TCTRL_TIE_MASK;//disables PIT timer interrupt
		}
		break;

		case PIT_2:
		{
			PIT->CHANNEL[2].TCTRL |= !PIT_TCTRL_TIE_MASK;//disables PIT timer interrupt
		}
		break;
		case PIT_3:
		{
			PIT->CHANNEL[3].TCTRL |= !PIT_TCTRL_TIE_MASK;//disables PIT timer interrupt
		}
		break;
		default:
		break;
	}
}

