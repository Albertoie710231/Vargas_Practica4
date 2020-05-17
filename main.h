/*
 * main.h
 *
 *  Created on: 17 may 2020
 *      Author: alber
 */

#ifndef MAIN_H_
#define MAIN_H_

#include "ADC.h"
#include "GPIO.h"
#include "DAC.h"
#include "UART.h"

#define SYSTEM_CLK 60000000

#define CLK_FREQ_HZ 50000000  /* CLKIN0 frequency */
#define SLOW_IRC_FREQ 32768	/*This is the approximate value for the slow irc*/
#define FAST_IRC_FREQ 4000000 /*This is the approximate value for the fast irc*/
#define EXTERNAL_CLOCK 0 /*It defines an external clock*/
#define PLL_ENABLE 1 /**PLL is enabled*/
#define PLL_DISABLE 0 /**PLL is disabled*/
#define CRYSTAL_OSC 1  /*It defines an crystal oscillator*/
#define LOW_POWER 0     /* Set the oscillator for low power mode */
#define SLOW_IRC 0 		/* Set the slow IRC */
#define CLK0_TYPE 0     /* Crystal or canned oscillator clock input */
#define PLL0_PRDIV 25    /* PLL predivider value */
#define PLL0_VDIV 30    /* PLL multiplier value*/

static adc_config_t adc_config =
{
		ADC_0,
		SCn_A,
		SAMP_8,
		DES_DIFF,
		AD_12,//PTB_2
		DIV_2,
		LONG_SAMPLE,
		MODE_0,
		BUS_CLK
};

dac_config_t g_dac_config = {
		DAC_0,
		DACREF_2,
		DESABLE
};

static uart_config_t g_uart_config_0 = {
		UART_0,
		SYSTEM_CLK,
		BD_115200
};

#endif /* MAIN_H_ */
