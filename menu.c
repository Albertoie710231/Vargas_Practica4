/*
 * menu.c
 *
 *  Created on: 17 may 2020
 *      Author: alber
 */

#include "menu.h"
#include "UART.h"

#define BCKSPACE '\b'
#define ENTER '\r'

static uint8_t menu1[] = "1) Grabar audio\r";
static uint8_t menu2[] = "2) Reproducir audio\r";

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
