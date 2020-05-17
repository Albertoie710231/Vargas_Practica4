/**
	\file
	\brief
		This is the header file for the UART device driver.
		It contains the macros and function definition.
	\author J. Luis Pizano Escalante, luispizano@iteso.mx
	\date	05/03/2019
	\todo
		To implement all needed functions
 */
#ifndef UART_H_
#define UART_H_

#include <stdint.h>
#include "MK64F12.h"

#define baud_rate_h_shift	0x08
#define baud_rate_l_mask	0x00FF
#define baud_rate_high(x)	(((uint8_t)(((uint8_t)(x)) >> baud_rate_h_shift)) & UART_BDH_SBR_MASK)
#define	baud_rate_low(x)	(((uint8_t)(((uint8_t)(x)) & baud_rate_l_mask)) & UART_BDL_SBR_MASK)

#define CHAR_NULL 0x00
/**
 * \brief A mail box type definition for serial port
 */
typedef struct{
	uint8_t flag; /** Flag to indicate that there is new data*/
	uint8_t mailBox; /** it contains the received data*/
} uart_mail_box_t;

/**
 * \brief This enum define the UART port to be used.
 */
typedef enum {UART_0,UART_1,UART_2,UART_3,UART_4,UART_5} uart_channel_t;

/**
 * \brief It defines some common transmission baud rates
 */
typedef enum {BD_4800 = 4800,BD_9600 = 9600,BD_5600 = 5600, BD_115200 = 115200} uart_baud_rate_t;

typedef struct
{
	uart_channel_t uart_channel;
	uint32_t system_clk;
	uart_baud_rate_t uart_baud_rate;
}uart_config_t;
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 It configures the UART to be used
 	 \param[in]  uartChannel indicates which UART will be used.
 	 \param[in]  systemClk indicates the MCU frequency.
 	 \param[in]  baudRate sets the baud rate to transmit.
 	 \return void
 */
void UART_callback_init(uart_channel_t uart_channel, void(*handler)(void));

void UART_init(const uart_config_t* config_struct);

void UART_clk(uart_channel_t uart_channel);

void UART_baud_rate(uart_channel_t uart_channel, uint32_t system_clk, uart_baud_rate_t baud_rate);

void UART_enable_rx_tx(uart_channel_t uart_channel);

void UART_desable_rx_tx(uart_channel_t uart_channel);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 enables the RX UART interrupt). This function should include the next sentence:
 	 while (!(UART0_S1 & UART_S1_RDRF_MASK)). It is to guaranty that the incoming data is complete
 	 when reception register is read. For more details see chapter 52 in the kinetis reference manual.
 	 \param[in]  uartChannel indicates the UART channel.
 	 \return void
 */
void UART_interrupt_enable(uart_channel_t uart_channel);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 It sends one character through the serial port. This function should include the next sentence:
 	 while(!(UART0_S1 & UART_S1_TC_MASK)). It is to guaranty that before to try to transmit a byte, the previous
 	 one was transmitted. In other word, to avoid to transmit data while the UART is busy transmitting information.
 	 \param[in]  uartChannel indicates the UART channel.
 	 \param[in]  character to be transmitted.
 	 \return void
 */

void UART_put_char (uart_channel_t uart_channel, uint8_t character);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 It sends a string character through the serial port.
 	 \param[in]  uartChannel indicates the UART channel.
 	 \param[in]  string pointer to the string to be transmitted.
 	 \return void
 */
void UART_put_string(uart_channel_t uart_channel, int8_t* string);

uint8_t UART_get_char(uart_channel_t uart_channel);

uint8_t UART_status_flag(uart_channel_t uart_channel);

void UART_clear_flag(uart_channel_t uart_channel);

void UART_reset_counter(void);

void UART_clear_buffer(void);

#endif /* UART_H_ */
