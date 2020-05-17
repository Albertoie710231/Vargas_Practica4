/*
 * ADC.c
 *
 *  Created on: 9 nov 2019
 *      Author: alber
 */

#include "ADC.h"
#include "PDB.h"
#include "MK64F12.h"

#define SIZE_ARRAY 40000

static uint8_t g_adc_result[SIZE_ARRAY] = {0};
static uint16_t g_pos = 0;

void ADC0_IRQHandler(void)
{
	if(SIZE_ARRAY > g_pos)
	{
		g_adc_result[g_pos] = (ADC0->R[SCn_A]);
		g_pos++;
	}
	else
	{
		g_pos = 0;
		PDB_desable();
	}
}

uint32_t ADC_biffer_address(void)
{
	return((uint32_t)(&g_adc_result[0]));
}

void ADC_clk_gating(adc_t adc_n)
{
	switch(adc_n)
	{
	case ADC_0:
		SIM->SCGC6 |= SIM_SCGC6_ADC0_MASK;
		break;
	case ADC_1:
		SIM->SCGC3 |= SIM_SCGC3_ADC1_MASK;
		break;
	}
}

void ADC_input_chn_select(adc_t adc_n, adc_scn_x_t sc1n_x, adc_channel_t channel)
{
	switch(adc_n)
	{
	case ADC_0:
		ADC0->SC1[sc1n_x] = ADC_SC1_ADCH(channel);
		break;
	case ADC_1:
		ADC1->SC1[sc1n_x] = ADC_SC1_ADCH(channel);
		break;
	}
}

void ADC_differential_mode(adc_t adc_n, adc_scn_x_t sc1n_x,adc_diff_mode_t diff_mode)
{
	switch(adc_n)
	{
	case ADC_0:
		if(ENB_DIFF == diff_mode)
			ADC0->SC1[sc1n_x] |= ADC_SC1_DIFF_MASK;
		else if(DES_DIFF == diff_mode)
			ADC0->SC1[sc1n_x] &= ~ADC_SC1_DIFF_MASK;
		break;
	case ADC_1:
		if(ENB_DIFF == diff_mode)
			ADC1->SC1[sc1n_x] |= ADC_SC1_DIFF_MASK;
		else if(DES_DIFF == diff_mode)
			ADC1->SC1[sc1n_x] &= ~ADC_SC1_DIFF_MASK;
		break;
	}
}

uint16_t ADC_data_result(adc_t adc_n, adc_scn_x_t sc1_n)
{
	uint16_t data_result = 0;
	switch(adc_n)
	{
	case ADC_0:
		ADC_input_chn_select(ADC_0, SCn_A, AD_12);
		while(0 == (ADC0->SC1[sc1_n] & ADC_SC1_COCO_MASK));
		data_result = (ADC0->R[sc1_n]);
		break;
	case ADC_1:
		while(0 == (ADC1->SC1[sc1_n] & ADC_SC1_COCO_MASK));
		data_result = 0xFF & (ADC1->R[sc1_n]);
		break;
	}
	return (data_result);
}

void ADC_conversion_mode(adc_t adc_n, adc_clk_devide_t clk_devide, adc_mode_t resolution_mode, adc_input_clk_t imput_clk)
{
	switch(adc_n)
	{
	case ADC_0:
		ADC0->CFG1 |= ADC_CFG1_ADIV(clk_devide);
		ADC0->CFG1 |= ADC_CFG1_MODE(resolution_mode);
		ADC0->CFG1 |= ADC_CFG1_ADICLK(imput_clk);
		break;
	case ADC_1:
		ADC1->CFG1 |= ADC_CFG1_ADIV(clk_devide);
		ADC1->CFG1 |= ADC_CFG1_MODE(resolution_mode);
		ADC1->CFG1 |= ADC_CFG1_ADICLK(imput_clk);
		break;
	}
}

void ADC_calibration(adc_t adc_n, hwd_average_t average)
{
	switch(adc_n)
	{
	case ADC_0:
		ADC0->SC3 |= ADC_SC3_AVGE_MASK;
		ADC0->SC3 |= ADC_SC3_AVGS(average);
		break;
	case ADC_1:
		ADC1->SC3 |= ADC_SC3_AVGE_MASK;
		ADC1->SC3 |= ADC_SC3_AVGS(average);
		break;
	}
}

void ADC_sample_time(adc_t adc_n, adc_sample_time_t sample_time)
{
	switch(adc_n)
	{
	case ADC_0:
		if(SHORT_SAMPLE == sample_time)
			ADC0->CFG1 &= ~ADC_CFG1_ADLSMP_MASK;
		else if(LONG_SAMPLE == sample_time)
			ADC0->CFG1 |= ADC_CFG1_ADLSMP_MASK;
		break;
	case ADC_1:
		if(SHORT_SAMPLE == sample_time)
			ADC1->CFG1 &= ~ADC_CFG1_ADLSMP_MASK;
		else if(LONG_SAMPLE == sample_time)
			ADC1->CFG1 |= ADC_CFG1_ADLSMP_MASK;
		break;
	}
}

void ADC_interrupt_enable(adc_t adc_n, adc_scn_x_t sc1_n)
{
	switch(adc_n)
	{
	case ADC_0:
		ADC0->SC1[sc1_n] |= ADC_SC1_AIEN(1);
		break;
	case ADC_1:
		ADC1->SC1[sc1_n] |= ADC_SC1_AIEN(1);
		break;
	}
}

void ADC_init(const adc_config_t* config_struct)
{
	ADC_clk_gating(config_struct->adc);

	ADC_input_chn_select(config_struct->adc, config_struct->scn_x,config_struct->channel);

	ADC_differential_mode(config_struct->adc, config_struct->scn_x, config_struct->diff_mode);

	ADC_conversion_mode(config_struct->adc, config_struct->clk_div, config_struct->adc_res, config_struct->imput_clk);

	ADC_calibration(config_struct->adc,config_struct->avrg);

	ADC_sample_time(config_struct->adc, config_struct->smpl_time);

	ADC0->CFG2 &= ~ADC_CFG2_MUXSEL(1);

	ADC0->CFG2 &= ~ADC_CFG2_ADHSC(1);

	ADC0->SC2 |= ADC_SC2_ADTRG(1);

	ADC_interrupt_enable(config_struct->adc,config_struct->scn_x);
}
