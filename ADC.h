/*
 * ADC.h
 *
 *  Created on: 9 nov 2019
 *      Author: alber
 */

#ifndef ADC_H_
#define ADC_H_

#include "MK64F12.h"

typedef enum{
	 ADC_0,
	 ADC_1
}adc_t;

typedef enum{
	 SCn_A,
	 SCn_B
}adc_scn_x_t;

typedef enum
{
	DIV_1,
	DIV_2,
	DIV_4,
	DIV_8
}adc_clk_devide_t;

typedef enum
{
	DES_DIFF,
	ENB_DIFF
}adc_diff_mode_t;

typedef enum
{
	SHORT_SAMPLE,
	LONG_SAMPLE
}adc_sample_time_t;

typedef enum
{
	MODE_0,
	MODE_1,
	MODE_2,
	MODE_3
}adc_mode_t;

typedef enum
{
	BUS_CLK,
	ALTCLK2,
	ALTCLK,
	ADACK
}adc_input_clk_t;

typedef enum
{
	DAD_0,
	DAD_1,
	DAD_2,
	DAD_3,
	AD_4,
	AD_5,
	AD_6,
	AD_7,
	AD_8,
	AD_9,
	AD_10,
	AD_11,
	AD_12,
	AD_13,
	AD_14,
	AD_15,
	AD_16,
	AD_17,
	AD_18,
	AD_19,
	AD_20,
	AD_21,
	AD_22,
	AD_23
}adc_channel_t;

typedef enum
{
	SAMP_4,
	SAMP_8,
	SAMP_16,
	SAMP_32
}hwd_average_t;

typedef struct
{
	adc_t adc;
	adc_scn_x_t scn_x;
	hwd_average_t avrg;
	adc_diff_mode_t diff_mode;
	adc_channel_t channel;
	adc_clk_devide_t clk_div;
	adc_sample_time_t smpl_time;
	adc_mode_t adc_res;
	adc_input_clk_t imput_clk;
} adc_config_t;

uint32_t ADC_biffer_address(void);

void ADC_clk_gating(adc_t adc_n);

void ADC_input_chn_select(adc_t adc_n, adc_scn_x_t sc1n_x, adc_channel_t channel);

void ADC_differential_mode(adc_t adc_n, adc_scn_x_t sc1n_x,adc_diff_mode_t diff_mode);

uint16_t ADC_data_result(adc_t adc_n, adc_scn_x_t sc1_n);

void ADC_conversion_mode(adc_t adc_n, adc_clk_devide_t clk_devide, adc_mode_t resolution_mode, adc_input_clk_t imput_clk);

void ADC_sample_time(adc_t adc_n, adc_sample_time_t sample_time);

void ADC_calibration(adc_t adc_n, hwd_average_t average);

void ADC_init(const adc_config_t* config_struct);

void ADC_interrupt_enable(adc_t adc_n, adc_scn_x_t sc1_n);

#endif /* ADC_H_ */
