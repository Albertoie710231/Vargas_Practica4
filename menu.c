/*
 * menu.c
 *
 *  Created on: 17 may 2020
 *      Author: alber
 */

#include "menu.h"
#include "UART.h"
#include "PDB.h"
#include "ADC.h"

#define BCKSPACE '\b'
#define ENTER '\r'

static uint8_t g_key_value = 0;
static uint8_t menu1[] = "1) Grabar audio\r";
static uint8_t menu2[] = "2) Reproducir audio\r";
static uint8_t menu3[] = "Grabando...\r";
static uint8_t menu4[] = "Reproduciendo...\r";

void menu_clear(void)
{
	UART_put_string(UART_0, "\033[0;30;46m");
	/*VT100 command for clearing the screen*/
	UART_put_string(UART_0, "\033[2J");
	/** VT100 command for text in red and background in green*/
	UART_put_string(UART_0, "\033[0;30;46m");
}

void menu_principal(void)
{
	/*VT100 command for clearing the screen*/

	menu_clear();

	UART_put_string(UART_0, "\033[10;10H");
	UART_put_string(UART_0, &menu1);
	UART_put_string(UART_0, "\033[11;10H");
	UART_put_string(UART_0, &menu2);
	UART_put_string(UART_0, "\033[12;10H");
}

void menu_select(void)
{
	g_key_value = menu_capture_keyboard();

	switch(g_key_value)
	{
	case '1':
		menu_clear();
		UART_put_string(UART_0, "\033[10;10H");
		UART_put_string(UART_0, &menu3);
		UART_put_string(UART_0, "\033[11;10H");

		PDB_init_adc();
		break;
	case '2':
		menu_clear();
		UART_put_string(UART_0, "\033[10;10H");
		UART_put_string(UART_0, &menu4);
		UART_put_string(UART_0, "\033[11;10H");

		PDB_init_dac();
		break;
	case BCKSPACE:
		menu_principal();
		break;
	}
}

uint8_t menu_capture_keyboard(void)
{
	static uint8_t keyboard_capture = 0;

	keyboard_capture = UART_get_char(UART_0);
	UART_put_char(UART_0, keyboard_capture);

	return keyboard_capture;
}
