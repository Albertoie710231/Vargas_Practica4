/**
	\file
	\brief
		This is the source file for the MCG device driver for Kinetis K64.
		It contains all the implementation for the different modes.
	\author	Alberto Vargas Garrido
	\date	17/05/2019
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
#include "NVIC.h"
#include "DMA.h"
#include "DAC.h"
#include "menu.h"
#include "UART.h"
#include "main.h"


/** Macros for debugging*/
//#define DEBUG

//#define PLL_DIRECT_INIT

/*Output compare frequency = (bus clock)/(Prescaler(mod+1))*/

int main(void)
{

	 int mcg_clk_hz;

	 static gpio_pin_control_register_t pin_control_register_uart = GPIO_MUX3;

	 /**
	  * Se cambia el el source clock por uno de 60MHz
	  */
#ifndef PLL_DIRECT_INIT
    mcg_clk_hz = fei_fbi(SLOW_IRC_FREQ,SLOW_IRC);// 64 Hz ---> 32768
    mcg_clk_hz = fbi_fbe(CLK_FREQ_HZ,LOW_POWER,EXTERNAL_CLOCK); // 97.656KHz ---> 50000000
    mcg_clk_hz = fbe_pbe(CLK_FREQ_HZ,PLL0_PRDIV,PLL0_VDIV);	// 97.656KHz ---> 50000000 and PLL is configured to generate 60000000
    mcg_clk_hz =  pbe_pee(CLK_FREQ_HZ);// 117.18 KHz ---> 60000000
#else
    mcg_clk_hz = pll_init(CLK_FREQ_HZ, LOW_POWER, EXTERNAL_CLOCK, PLL0_PRDIV, PLL0_VDIV, PLL_ENABLE);
#endif

    RGB_init();

    DMA_clock_gating();

    DMA_init();

    ADC_init(&adc_config);

    DAC_init(&g_dac_config);

	GPIO_clock_gating(GPIO_B);
	/**Configures the pin control register of pin16 in PortB as UART RX*/
	GPIO_pin_control_register(GPIO_B, 16, &pin_control_register_uart);
	/**Configures the pin control register of pin17 in PortB as UART TX*/
	GPIO_pin_control_register(GPIO_B, 17, &pin_control_register_uart);

    PDB_clk_gating();

	NVIC_set_basepri_threshold(PRIORITY_10);

	NVIC_enable_interrupt_and_priority(UART0_IRQ, PRIORITY_9);
	NVIC_enable_interrupt_and_priority(DMA_CH0_IRQ, PRIORITY_8);
	NVIC_enable_interrupt_and_priority(ADC0_IRQ, PRIORITY_7);

	UART_callback_init(UART_0, menu_select);

	UART_init(&g_uart_config_0);

	menu_principal();

	UART_interrupt_enable(UART_0);

	NVIC_global_enable_interrupts;

	while(1);

}
