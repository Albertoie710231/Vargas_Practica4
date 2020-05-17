/*
 * UART.c
 *
 *  Created on: 31 oct 2019
 *      Author: alber
 */

#include "UART.h"
#include "MK64F12.h"

static uart_mail_box_t g_mail_box_uart_0 = {0,0};
static uart_mail_box_t g_mail_box_uart_1 = {0,0};
static uart_mail_box_t g_mail_box_uart_2 = {0,0};
static uart_mail_box_t g_mail_box_uart_3 = {0,0};
static uart_mail_box_t g_mail_box_uart_4 = {0,0};
static uart_mail_box_t g_mail_box_uart_5 = {0,0};

static void (*UART_0_callback)(void) = 0;
static void (*UART_1_callback)(void) = 0;
static void (*UART_2_callback)(void) = 0;
static void (*UART_3_callback)(void) = 0;
static void (*UART_4_callback)(void) = 0;
static void (*UART_5_callback)(void) = 0;

void UART0_RX_TX_IRQHandler()
{
	while(!(UART0->S1 & UART_S1_RDRF_MASK));
	g_mail_box_uart_0.mailBox = UART0->D;
	g_mail_box_uart_0.flag = 1;

	if(UART_0_callback)
	{
		UART_0_callback();
	}

	/*Clear flag and mailbox of the UART*/
	g_mail_box_uart_0.mailBox = 0;
	g_mail_box_uart_0.flag = 0;
}

void UART1_RX_TX_IRQHandler()
{
	while(!(UART1->S1 & UART_S1_RDRF_MASK));
	g_mail_box_uart_1.mailBox = UART1->D;
	g_mail_box_uart_1.flag = 1;
	if(UART_1_callback)
	{
		UART_1_callback();
	}
	g_mail_box_uart_1.flag = 0;
}

void UART2_RX_TX_IRQHandler()
{
	while(!(UART2->S1 & UART_S1_RDRF_MASK));
	g_mail_box_uart_2.mailBox = UART2->D;
	if(UART_2_callback)
	{
		UART_2_callback();
	}
	g_mail_box_uart_2.flag = 1;
}

void UART3_RX_TX_IRQHandler()
{
	while(!(UART3->S1 & UART_S1_RDRF_MASK));
	g_mail_box_uart_3.mailBox = UART3->D;
	if(UART_3_callback)
	{
		UART_3_callback();
	}
	g_mail_box_uart_3.flag = 1;
}

void UART4_RX_TX_IRQHandler()
{
	while(!(UART4->S1 & UART_S1_RDRF_MASK));
	g_mail_box_uart_4.mailBox = UART4->D;
	g_mail_box_uart_4.flag = 1;

	if(UART_4_callback)
	{
		UART_4_callback();
	}
	g_mail_box_uart_4.mailBox = 0;
	g_mail_box_uart_4.flag = 0;
}

void UART5_RX_TX_IRQHandler()
{
	while(!(UART5->S1 & UART_S1_RDRF_MASK));
	g_mail_box_uart_5.mailBox = UART5->D;
	if(UART_5_callback)
	{
		UART_5_callback();
	}
	g_mail_box_uart_5.flag = 1;
}

void UART_callback_init(uart_channel_t uart_channel, void(*handler)(void))
{
	switch(uart_channel)
	{
	case UART_0:
		 UART_0_callback = handler;
		break;
	case UART_1:
		UART_1_callback = handler;
		break;
	case UART_2:
		UART_2_callback = handler;
		break;
	case UART_3:
		UART_3_callback = handler;
		break;
	case UART_4:
		UART_4_callback = handler;
		break;
	case UART_5:
		UART_5_callback = handler;
		break;
	}
}

void UART_init(const uart_config_t* config_struct)
{
	UART_clk(config_struct->uart_channel);
	UART_desable_rx_tx(config_struct->uart_channel);
	UART_baud_rate(config_struct->uart_channel, config_struct->system_clk, config_struct->uart_baud_rate);
	UART_enable_rx_tx(config_struct->uart_channel);
}

void UART_clk(uart_channel_t uart_channel)
{
	switch(uart_channel)
	{
	case UART_0:
		SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;
		break;
	case UART_1:
		SIM->SCGC4 |= SIM_SCGC4_UART1_MASK;
		break;
	case UART_2:
		SIM->SCGC4 |= SIM_SCGC4_UART2_MASK;
		break;
	case UART_3:
		SIM->SCGC4 |= SIM_SCGC4_UART3_MASK;
		break;
	case UART_4:
		SIM->SCGC1 |= SIM_SCGC1_UART4_MASK;
		break;
	case UART_5:
		SIM->SCGC1 |= SIM_SCGC1_UART5_MASK;
		break;
	}
}

void UART_enable_rx_tx(uart_channel_t uart_channel)
{
	switch(uart_channel)
	{
	case UART_0:
		UART0->C2 |= UART_C2_RE_MASK;
		UART0->C2 |= UART_C2_TE_MASK;
		break;
	case UART_1:
		UART1->C2 |= UART_C2_RE_MASK;
		UART1->C2 |= UART_C2_TE_MASK;
		break;
	case UART_2:
		UART2->C2 |= UART_C2_RE_MASK;
		UART2->C2 |= UART_C2_TE_MASK;
		break;
	case UART_3:
		UART3->C2 |= UART_C2_RE_MASK;
		UART3->C2 |= UART_C2_TE_MASK;
		break;
	case UART_4:
		UART4->C2 |= UART_C2_RE_MASK;
		UART4->C2 |= UART_C2_TE_MASK;
		break;
	case UART_5:
		UART5->C2 &= ~UART_C2_RE_MASK;
		UART5->C2 &= ~UART_C2_TE_MASK;
		break;
	}
}

void UART_desable_rx_tx(uart_channel_t uart_channel)
{
	switch(uart_channel)
	{
	case UART_0:
		UART0->C2 &= ~UART_C2_RE_MASK;
		UART0->C2 &= ~UART_C2_TE_MASK;
		break;
	case UART_1:
		UART1->C2 &= ~UART_C2_RE_MASK;
		UART1->C2 &= ~UART_C2_TE_MASK;
		break;
	case UART_2:
		UART2->C2 &= ~UART_C2_RE_MASK;
		UART2->C2 &= ~UART_C2_TE_MASK;
		break;
	case UART_3:
		UART3->C2 &= ~UART_C2_RE_MASK;
		UART3->C2 &= ~UART_C2_TE_MASK;
		break;
	case UART_4:
		UART4->C2 &= ~UART_C2_RE_MASK;
		UART4->C2 &= ~UART_C2_TE_MASK;
		break;
	case UART_5:
		UART5->C2 &= ~UART_C2_RE_MASK;
		UART5->C2 &= ~UART_C2_TE_MASK;
		break;
	}
}

void UART_baud_rate(uart_channel_t uart_channel, uint32_t system_clk, uart_baud_rate_t baud_rate)
{
	uint8_t brfa_value = 0;
	float brfd_value = 0;
	uint8_t sbr_value = 0;

	//Estas formulas son vienen de las ecuaciones:
	//1)UART_baud_rate = UART_module_clock / (16 × (SBR[12:0] + BRFD))
	//2)BRFD = brfa/32
	if((UART_0 == uart_channel)||(UART_1 == uart_channel))
	{
		sbr_value	= ((uint8_t)(system_clk/(16*baud_rate)));
		brfd_value	= (-sbr_value+(system_clk/(16*baud_rate)));
		brfa_value	= (uint8_t)(brfd_value*32);

		switch(uart_channel)
		{
		case UART_0:
			UART0->BDH = baud_rate_high(sbr_value);
			UART0->BDL = baud_rate_low(sbr_value);
			UART0->C4 |= brfa_value;
			break;
		case UART_1:
			UART1->BDH = baud_rate_high(sbr_value);
			UART1->BDL = baud_rate_low(sbr_value);
			UART1->C4 |= brfa_value;
			break;
		}
	}
	else
	{
		sbr_value	= ((uint8_t)((system_clk/2)/(16*baud_rate)));
		brfd_value	= (-sbr_value+((system_clk/2)/(16*baud_rate)));
		brfa_value	= (uint8_t)(brfd_value*32);

		switch(uart_channel)
		{
		case UART_2:
			UART2->BDH = baud_rate_high(sbr_value);
			UART2->BDL = baud_rate_low(sbr_value);
			UART2->C4 |= brfa_value;
			break;
		case UART_3:
			UART3->BDH = baud_rate_high(sbr_value);
			UART3->BDL = baud_rate_low(sbr_value);
			UART3->C4 |= brfa_value;
			break;
		case UART_4:
			UART4->BDH = baud_rate_high(sbr_value);
			UART4->BDL = baud_rate_low(sbr_value);
			UART4->C4 |= brfa_value;
			break;
		case UART_5:
			UART5->BDH = baud_rate_high(sbr_value);
			UART5->BDL = baud_rate_low(sbr_value);
			UART5->C4 |= brfa_value;
			break;
		}
	}
}

void UART_interrupt_enable(uart_channel_t uart_channel)
{
	switch(uart_channel)
	{
	case UART_0:
		UART0->C2 |= UART_C2_RIE_MASK;
		break;
	case UART_1:
		UART1->C2 |= UART_C2_RIE_MASK;
		break;
	case UART_2:
		UART2->C2 |= UART_C2_RIE_MASK;
		break;
	case UART_3:
		UART3->C2 |= UART_C2_RIE_MASK;
		break;
	case UART_4:
		UART4->C2 |= UART_C2_RIE_MASK;
		break;
	case UART_5:
		UART5->C2 |= UART_C2_RIE_MASK;
		break;
	}
}

void UART_put_char (uart_channel_t uart_channel, uint8_t character)
{
	switch(uart_channel)
	{
	case UART_0:
		while(!(UART0->S1 & UART_S1_TC_MASK));
		UART0->D = character;
		break;
	case UART_1:
		while(!(UART1->S1 & UART_S1_TC_MASK));
		UART1->D = character;
		break;
	case UART_2:
		while(!(UART2->S1 & UART_S1_TC_MASK));
		UART2->D = character;
		break;
	case UART_3:
		while(!(UART3->S1 & UART_S1_TC_MASK));
		UART3->D = character;
		break;
	case UART_4:
		while(!(UART4->S1 & UART_S1_TC_MASK));
		UART4->D = character;
		break;
	case UART_5:
		while(!(UART5->S1 & UART_S1_TC_MASK));
		UART5->D = character;
		break;
	}
}

void UART_put_string(uart_channel_t uart_channel, int8_t* string)
{
	uint8_t index;
	for(index = 0; *(string+index) != CHAR_NULL ;index++)
		UART_put_char(uart_channel, *(string+index));
}

uint8_t UART_get_char(uart_channel_t uart_channel)
{
	uint8_t uart_char = 0;
	switch(uart_channel)
	{
	case UART_0:
		uart_char = g_mail_box_uart_0.mailBox;
		break;
	case UART_1:
		uart_char = g_mail_box_uart_1.mailBox;
		break;
	case UART_2:
		uart_char = g_mail_box_uart_2.mailBox;
		break;
	case UART_3:
		uart_char = g_mail_box_uart_3.mailBox;
		break;
	case UART_4:
		uart_char = g_mail_box_uart_4.mailBox;
		break;
	case UART_5:
		uart_char = g_mail_box_uart_5.mailBox;
		break;
	}
	return(uart_char);
}

uint8_t UART_status_flag(uart_channel_t uart_channel)
{
	uint8_t uart_status_flag = 0;
	switch(uart_channel)
	{
	case UART_0:
		uart_status_flag = g_mail_box_uart_0.flag;
		break;
	case UART_1:
		uart_status_flag = g_mail_box_uart_1.flag;
		break;
	case UART_2:
		uart_status_flag = g_mail_box_uart_2.flag;
		break;
	case UART_3:
		uart_status_flag = g_mail_box_uart_3.flag;
		break;
	case UART_4:
		uart_status_flag = g_mail_box_uart_4.flag;
		break;
	case UART_5:
		uart_status_flag = g_mail_box_uart_5.flag;
		break;
	}
	return(uart_status_flag);
}

void UART_clear_flag(uart_channel_t uart_channel)
{
	switch(uart_channel)
	{
	case UART_0:
		g_mail_box_uart_0.flag = 0;
		break;
	case UART_1:
		g_mail_box_uart_1.flag = 0;
		break;
	case UART_2:
		g_mail_box_uart_2.flag = 0;
		break;
	case UART_3:
		g_mail_box_uart_3.flag = 0;
		break;
	case UART_4:
		g_mail_box_uart_4.flag = 0;
		break;
	case UART_5:
		g_mail_box_uart_5.flag = 0;
		break;
	}
}
