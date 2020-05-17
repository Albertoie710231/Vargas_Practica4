/*
 * RGB.c
 *
 *  Created on: 10 feb 2020
 *      Author: alber
 */

#include "GPIO.h"
#include "MK64F12.h"
#include "bits.h"
#include "RGB.h"
#include "GPIO.h"

#define LED_RED_MASK			0x00400000
#define LED_BLUE_MASK			0x00200000
#define LED_GREEN_MASK			0x004000000

typedef void (*color_sequence[5])(void);

static uint8_t g_sec_press = 0;
static uint8_t g_time_passed = 0;

static gpio_pin_control_register_t pinControlRegisterGPIOBpin21 = GPIO_MUX1;	//blue
static gpio_pin_control_register_t pinControlRegisterGPIOBpin22 = GPIO_MUX1;	//red
static gpio_pin_control_register_t pinControlRegisterGPIOEpin26 = GPIO_MUX1;	//Green

void RGB_init(void)
{
	GPIO_clock_gating(GPIO_B);				//Inicia el timer de los puertos B y E
	GPIO_clock_gating(GPIO_E);

	GPIO_pin_control_register(GPIO_B,bit_21,&pinControlRegisterGPIOBpin21);
	GPIO_pin_control_register(GPIO_B,bit_22,&pinControlRegisterGPIOBpin22);
	GPIO_pin_control_register(GPIO_E,bit_26,&pinControlRegisterGPIOEpin26);

	GPIO_write_port(GPIO_B, LED_RED_MASK);
	GPIO_write_port(GPIO_B, LED_BLUE_MASK);
	GPIO_write_port(GPIO_E, LED_GREEN_MASK);

	GPIO_data_direction_pin(GPIO_B,GPIO_OUTPUT, bit_21);
	GPIO_data_direction_pin(GPIO_B,GPIO_OUTPUT,bit_22);
	GPIO_data_direction_pin(GPIO_E,GPIO_OUTPUT,bit_26);

}

void RGB_all_turn_off(void)
{
	GPIO_set_pin(GPIO_B, bit_21);	//Apagamos rojo y azul
	GPIO_set_pin(GPIO_B, bit_22);
	GPIO_set_pin(GPIO_E, bit_26);	//Apagamos verde
}

void RGB_red_on(void)
{
	RGB_all_turn_off();
	GPIO_clear_pin(GPIO_B, bit_22);
}

void RGB_blue_on(void)
{
	RGB_all_turn_off();
	GPIO_clear_pin(GPIO_B, bit_21);
}
void RGB_green_on(void)
{
	RGB_all_turn_off();
	GPIO_clear_pin(GPIO_E, bit_26);
}

void RGB_yellow_on(void)
{
	RGB_all_turn_off();
	GPIO_clear_pin(GPIO_B, bit_22);
	GPIO_clear_pin(GPIO_E, bit_26);
}

void RGB_purple_on(void)
{
	RGB_all_turn_off();
	GPIO_clear_pin(GPIO_B, bit_21);
	GPIO_clear_pin(GPIO_B, bit_22);
}

void RGB_cian_on(void)
{
	RGB_all_turn_off();
	GPIO_clear_pin(GPIO_B, bit_21);
	GPIO_clear_pin(GPIO_E, bit_26);
}

void RGB_white_on(void)
{
	RGB_all_turn_off();
	GPIO_clear_pin(GPIO_B, bit_22);
	GPIO_clear_pin(GPIO_B, bit_21);
	GPIO_clear_pin(GPIO_E, bit_26);
}


