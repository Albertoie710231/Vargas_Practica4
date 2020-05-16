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
/** Macros for debugging*/
//#define DEBUG

//#define PLL_DIRECT_INIT

/*Output compare frequency = (bus clock)/(Prescaler(mod+1))*/

int main(void)
{
	PDB_init();

	 int mcg_clk_hz;
	    unsigned char modeMCG = 0;


	#ifndef PLL_DIRECT_INIT
	    mcg_clk_hz = fei_fbi(SLOW_IRC_FREQ,SLOW_IRC);// 64 Hz ---> 32768
	    mcg_clk_hz = fbi_fbe(CLK_FREQ_HZ,LOW_POWER,EXTERNAL_CLOCK); // 97.656KHz ---> 50000000
//	    mcg_clk_hz = fbe_pbe(CLK_FREQ_HZ,PLL0_PRDIV,PLL0_VDIV);	// 97.656KHz ---> 50000000 and PLL is configured to generate 60000000
//	    mcg_clk_hz =  pbe_pee(CLK_FREQ_HZ);// 117.18 KHz ---> 60000000
	#else
	       mcg_clk_hz = pll_init(CLK_FREQ_HZ, LOW_POWER, EXTERNAL_CLOCK, PLL0_PRDIV, PLL0_VDIV, PLL_ENABLE);
	#endif


	    modeMCG = what_mcg_mode();
	#ifdef DEBUG
	    printf("\nMCG mode =  %d\n",modeMCG);
	  	printf("Clock Rate =  %d MHz\n",mcg_clk_hz);
	#endif


   	/** Configuration for the output compare mode of the FlexTimer 0*/
    SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;
	SIM->SCGC6 |= SIM_SCGC6_FTM0_MASK;
	PORTC->PCR[1]   = PORT_PCR_MUX(0x4);

	FTM0->MODE |= FTM_MODE_WPDIS_MASK;
	FTM0->MODE &= ~FTM_MODE_FTMEN_MASK;
	FTM0->CONF |= FTM_CONF_BDMMODE(3);

	FTM0->CNT = 0x0;
	FTM0->COMBINE = 0;
	FTM0->MOD = 0x1;
	FTM0->CNTIN = 0;
	FTM0->SC = 0;
	FTM0->CONTROLS[0].CnSC = FTM_CnSC_MSA_MASK| FTM_CnSC_ELSA_MASK;
	FTM0->CONTROLS[0].CnV= 0x1;
	FTM0->SC |= FTM_SC_PS(7)|FTM_SC_CLKS(1);

	while(1)
	{
	}


}
