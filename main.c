/**
	\file
	\brief
		This is the source file for the MCG device driver for Kinetis K64.
		It contains all the implementation for the different modes.
	\author Dr. J. Luis Pizano Escalante, luispizano@iteso.mx
	\date	25/04/2015
	\todo
	    the device driver doesn't work with frequencies greater than 65 MHz.
 */

#include "MK64F12.h"
#include "stdio.h"
#include "MCG.h"
#include "PDB.h"
#include "ADC.h"
#include "GPIO.h"
#include "bits.h"

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

static gpio_pin_control_register_t pin_control_register = GPIO_MUX4;
/** Macros for debugging*/
//#define DEBUG

//#define PLL_DIRECT_INIT

/*Output compare frequency = (bus clock)/(Prescaler(mod+1))*/

int main(void)
{

	 int mcg_clk_hz;
	 unsigned char modeMCG = 0;
	 static uint16_t data = 0;

#ifndef PLL_DIRECT_INIT
    mcg_clk_hz = fei_fbi(SLOW_IRC_FREQ,SLOW_IRC);// 64 Hz ---> 32768
    mcg_clk_hz = fbi_fbe(CLK_FREQ_HZ,LOW_POWER,EXTERNAL_CLOCK); // 97.656KHz ---> 50000000
    mcg_clk_hz = fbe_pbe(CLK_FREQ_HZ,PLL0_PRDIV,PLL0_VDIV);	// 97.656KHz ---> 50000000 and PLL is configured to generate 60000000
    mcg_clk_hz =  pbe_pee(CLK_FREQ_HZ);// 117.18 KHz ---> 60000000
#else
    mcg_clk_hz = pll_init(CLK_FREQ_HZ, LOW_POWER, EXTERNAL_CLOCK, PLL0_PRDIV, PLL0_VDIV, PLL_ENABLE);
#endif
	PDB_init_adc();

	ADC_init(&adc_config);

	while(1)
	{
		ADC_input_chn_select(ADC_0, SCn_A, AD_12);
		data = ADC_data_result(ADC_0, SCn_A);
	}


}
