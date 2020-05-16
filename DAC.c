/*
 * DAC.c
 *
 *  Created on: 4 oct 2019
 *      Author: alber
 */

#include "stdint.h"
#include "MK64F12.h"
#include "bits.h"
#include "DAC.h"

#define BUFFER_SHIFT 4U
#define SHIFT_DATLH 8U
#define MASK_DATLH 0x0F00U

static uint8_t g_buffer_upper_limit = 0;

void DAC_clk_gating(DAC_num dac_num)
{
	switch(dac_num)
	{
	case DAC_0:
		SIM->SCGC2 |= SIM_SCGC2_DAC0_MASK;
		break;
	case DAC_1:
		SIM->SCGC2 |= SIM_SCGC2_DAC1_MASK;
		break;
	}
}

void DAC_enable(DAC_num dac_num)
{
	switch(dac_num)
	{
	case DAC_0:
		DAC0->C0 |= DAC_C0_DACEN_MASK;
		break;
	case DAC_1:
		DAC1->C0 |= DAC_C0_DACEN_MASK;
		break;
	}
}

void DAC_reference_voltage(DAC_num dac_num, dac_reference_voltage_t dac_ref)
{
	switch(dac_num)
	{
	case DAC_0:
		DAC0->C0 |= DAC_C0_DACRFS(dac_ref);
		break;
	case DAC_1:
		DAC1->C0 |= DAC_C0_DACRFS(dac_ref);
		break;
	}
}

void DAC_buffer_enable(DAC_num dac_num, dac_buff_anable_t buff_enable)
{
	if(buff_enable)
	{
		switch(dac_num)
		{
		case DAC_0:
			DAC0->C0 |= DAC_C0_DACTRGSEL_MASK;
			DAC0->C1 |= DAC_C1_DACBFEN_MASK;
			break;
		case DAC_1:
			DAC1->C0 |= DAC_C0_DACTRGSEL_MASK;
			DAC1->C1 |= DAC_C1_DACBFEN_MASK;
			break;
		}
	}
	else
	{
		switch(dac_num)
		{
		case DAC_0:
			DAC0->C0 &= ~DAC_C0_DACTRGSEL_MASK;
			DAC0->C1 &= ~DAC_C1_DACBFEN_MASK;
			break;
		case DAC_1:
			DAC1->C0 &= ~DAC_C0_DACTRGSEL_MASK;
			DAC1->C1 &= ~DAC_C1_DACBFEN_MASK;
			break;
		}
	}
}

void DAC_buffer_mode(DAC_num dac_num, dac_buffer_mode_t mode)
{
	switch(dac_num)
	{
	case DAC_0:
		DAC0->C1 |= DAC_C1_DACBFMD(mode);
		break;
	case DAC_1:
		DAC1->C1 |= DAC_C1_DACBFMD(mode);
		break;
	}
}

void DAC_software_trigger_dac0(void)
{
	DAC0->C0 |= DAC_C0_DACSWTRG_MASK;
}

void DAC_software_trigger_dac1(void)
{
	DAC0->C1 |= DAC_C0_DACSWTRG_MASK;
}

uint8_t DAC_get_status(DAC_num dac_num)
{
	uint8_t status = 0;

	switch(dac_num)
	{
	case DAC_0:
		status = DAC0->SR;
		break;
	case DAC_1:
		status = DAC1->SR;
		break;
	}
	return(status);
}

void DAC_fill_buffer(uint16_t signal_data, uint8_t pointer)
{
	DAC0->DAT[pointer].DATL = (uint8_t)(signal_data);
	DAC0->DAT[pointer].DATH = (uint8_t)((signal_data & MASK_DATLH)>>SHIFT_DATLH);
}

void DAC_buffer_upper_limit(DAC_num dac_num, uint8_t uper_limit)
{
	switch(dac_num)
	{
	case DAC_0:
		DAC0->C2 = DAC_C2_DACBFUP(uper_limit);
		break;
	case DAC_1:
		DAC1->C2 = DAC_C2_DACBFUP(uper_limit);
		break;
	}
	g_buffer_upper_limit = uper_limit;
}

void DAC_init(const dac_config_t* config_struct)
{
	DAC_clk_gating(config_struct->dac_num);
	DAC_enable(config_struct->dac_num);
	DAC_reference_voltage(config_struct->dac_num, config_struct->reference_voltage);
	DAC_buffer_enable(config_struct->dac_num, config_struct->buff_enable);
}
