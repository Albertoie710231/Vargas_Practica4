/*
 * speaker.c
 *
 *  Created on: 16 may 2020
 *      Author: alber
 */

#include "DAC.h"
#include "DMA.h"

dac_config_t g_dac_config = {
		DAC_0,
		DACREF_2,
		DESABLE
};

void speaker_init(void)
{
	DMA_clock_gating();
	DAC_init(&g_dac_config);
	DMA_init();
}
