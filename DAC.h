/*
 * DAC.h
 *
 *  Created on: 4 oct 2019
 *      Author: alber
 */

#ifndef DAC_H_
#define DAC_H_

#include "stdint.h"
#include "MK64F12.h"

/*Configuration for DACx_C0*/
#define DACEN		0x80
#define DACRFS		0x40
#define DACTRGSEL	0x20
#define LPEN		0x08
#define DACBWIEN 	0x04
#define DACBTIEN 	0x02
#define DACBBIEN 	0x01

/*Configuration for DACx_C1*/
#define DMAEN			0x80
#define DACBFMD_NORMAL	0x00
#define DACBFMD_SWING	0x04
#define DACBFMD_OTS		0x08
#define DACBFEN			0x01

typedef enum
{
	NORMAL, SWING, ONE_TIME_SCAN, RESERVED
}dac_buffer_mode_t;

typedef enum
{
	DACREF_1, DACREF_2
}dac_reference_voltage_t;

typedef enum
{
	DAC_0,
	DAC_1
}DAC_num;

typedef enum
{
	DESABLE,
	ENABLE
}dac_buff_anable_t;

typedef struct
{
	DAC_num dac_num;
	dac_reference_voltage_t reference_voltage;
	dac_buff_anable_t buff_enable;
} dac_config_t;

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function enables the GPIO clock by configuring the corresponding bit
 	 	 and register in the System Clock Gating Control Register.

 	 \param[in]  port_name Port to be configured.
 	 \return 1 if the port_name is valid else return 0
 */
void DAC_clk_gating(DAC_num dac_num);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function enables the GPIO clock by configuring the corresponding bit
 	 	 and register in the System Clock Gating Control Register.

 	 \param[in]  port_name Port to be configured.
 	 \return 1 if the port_name is valid else return 0
 */
void DAC_enable(DAC_num dac_num);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function enables the GPIO clock by configuring the corresponding bit
 	 	 and register in the System Clock Gating Control Register.

 	 \param[in]  port_name Port to be configured.
 	 \return 1 if the port_name is valid else return 0
 */
void DAC_buffer_enable(DAC_num dac_num, dac_buff_anable_t buff_enable);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function enables the GPIO clock by configuring the corresponding bit
 	 	 and register in the System Clock Gating Control Register.

 	 \param[in]  port_name Port to be configured.
 	 \return 1 if the port_name is valid else return 0
 */
void DAC_buffer_mode(DAC_num dac_num, dac_buffer_mode_t mode);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function enables the GPIO clock by configuring the corresponding bit
 	 	 and register in the System Clock Gating Control Register.

 	 \param[in]  port_name Port to be configured.
 	 \return 1 if the port_name is valid else return 0
 */
void DAC_software_trigger_dac0(void);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function enables the GPIO clock by configuring the corresponding bit
 	 	 and register in the System Clock Gating Control Register.

 	 \param[in]  port_name Port to be configured.
 	 \return 1 if the port_name is valid else return 0
 */
void DAC_software_trigger_dac1(void);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function enables the GPIO clock by configuring the corresponding bit
 	 	 and register in the System Clock Gating Control Register.

 	 \param[in]  port_name Port to be configured.
 	 \return 1 if the port_name is valid else return 0
 */
uint8_t DAC_get_status(DAC_num dac_num);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function enables the GPIO clock by configuring the corresponding bit
 	 	 and register in the System Clock Gating Control Register.

 	 \param[in]  port_name Port to be configured.
 	 \return 1 if the port_name is valid else return 0
 */
void DAC_fill_buffer(uint16_t signal_data, uint8_t pointer);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function enables the GPIO clock by configuring the corresponding bit
 	 	 and register in the System Clock Gating Control Register.

 	 \param[in]  port_name Port to be configured.
 	 \return 1 if the port_name is valid else return 0
 */
void DAC_buffer_upper_limit(DAC_num dac_num, uint8_t uper_limit);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function enables the GPIO clock by configuring the corresponding bit
 	 	 and register in the System Clock Gating Control Register.

 	 \param[in]  port_name Port to be configured.
 	 \return 1 if the port_name is valid else return 0
 */
void DAC_init(const dac_config_t* config_struct);

void DAC_reference_voltage(DAC_num dac_num, dac_reference_voltage_t dac_ref);

#endif /* DAC_H_ */
