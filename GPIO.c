/**
	\file
	\brief
		This is the source file for the GPIO device driver for Kinetis K64.
		It contains all the implementation for configuration functions and runtime functions.
		i.e., this is the application programming interface (API) for the GPIO peripheral.
	\author J. Luis Pizano Escalante, luispizano@iteso.mx
	\date	18/02/2019
	\todo
	    Interrupts are not implemented in this API implementation.
 */
#include "MK64F12.h"
#include "GPIO.h"
#include "bits.h"


static void (*gpio_callback_A)(void) = 0;
static void (*gpio_callback_B)(void) = 0;
static void (*gpio_callback_C)(void) = 0;
static void (*gpio_callback_D)(void) = 0;
static void (*gpio_callback_E)(void) = 0;

static gpio_interrupt_flags_t g_intr_status_flag;

void PORTA_IRQHandler(void)
{
	if(gpio_callback_A)
	{
		gpio_callback_A();
	}
	GPIO_clear_interrupt(GPIO_A);
}

void PORTB_IRQHandler(void)
{
	if(gpio_callback_B)
	{
		gpio_callback_B();
	}
	GPIO_clear_interrupt(GPIO_B);
}

void PORTC_IRQHandler(void)
{
	if(gpio_callback_C)
	{
		gpio_callback_C();
	}
	GPIO_clear_interrupt(GPIO_C);
}

void PORTD_IRQHandler(void)
{
	if(gpio_callback_D)
	{
		gpio_callback_D();
	}
	GPIO_clear_interrupt(GPIO_D);
}

void PORTE_IRQHandler(void)
{
	if(gpio_callback_E)
	{
		gpio_callback_E();
	}
	GPIO_clear_interrupt(GPIO_E);
}

void GPIO_callback_init(gpio_port_name_t port_name, void(*handler)(void))
{
	switch(port_name)
	{
	case GPIO_A:
		gpio_callback_A = handler;
		break;
	case GPIO_B:
		gpio_callback_B = handler;
		break;
	case GPIO_C:
		gpio_callback_C = handler;
		break;
	case GPIO_D:
		gpio_callback_D = handler;
		break;
	case GPIO_E:
		gpio_callback_E = handler;
		break;
	}
}

uint32_t GPIO_get_irq_status(gpio_port_name_t gpio)
{
	uint32_t status = 0;

	switch(gpio){
	case GPIO_A:
		status = g_intr_status_flag.flagPortA;
		break;
	case GPIO_B:
		status = g_intr_status_flag.flagPortB;
		break;
	case GPIO_C:
		status = g_intr_status_flag.flagPortC;
		break;
	case GPIO_D:
		status = g_intr_status_flag.flagPortD;
		break;
	case GPIO_E:
		status = g_intr_status_flag.flagPortE;
		break;
	}
	return(status);
}

void GPIO_clear_interrupt(gpio_port_name_t gpio)
{
	switch(gpio)
	{
	case GPIO_A:
		PORTA->ISFR = FLAG_INT_MASK;
		g_intr_status_flag.flagPortA = ~FLAG_INT_MASK;
		break;
	case GPIO_B:
		PORTB->ISFR = FLAG_INT_MASK;
		g_intr_status_flag.flagPortB = ~FLAG_INT_MASK;
		break;
	case GPIO_C:
		PORTC->ISFR = FLAG_INT_MASK;
		g_intr_status_flag.flagPortC = ~FLAG_INT_MASK;
		break;
	case GPIO_D:
		PORTD->ISFR = FLAG_INT_MASK;
		g_intr_status_flag.flagPortD = ~FLAG_INT_MASK;
		break;
	case GPIO_E:
		PORTE->ISFR = FLAG_INT_MASK;
		g_intr_status_flag.flagPortE = ~FLAG_INT_MASK;
		break;
	}
}

uint8_t GPIO_clock_gating(gpio_port_name_t port_name)
{
	switch(port_name)/** Selecting the GPIO for clock enabling*/
	{
		case GPIO_A: /** GPIO A is selected*/
			SIM->SCGC5 |= GPIO_CLOCK_GATING_PORTA; /** Bit 9 of SIM_SCGC5 is  set*/
			break;
		case GPIO_B: /** GPIO B is selected*/
			SIM->SCGC5 |= GPIO_CLOCK_GATING_PORTB; /** Bit 10 of SIM_SCGC5 is set*/
			break;
		case GPIO_C: /** GPIO C is selected*/
			SIM->SCGC5 |= GPIO_CLOCK_GATING_PORTC; /** Bit 11 of SIM_SCGC5 is set*/
			break;
		case GPIO_D: /** GPIO D is selected*/
			SIM->SCGC5 |= GPIO_CLOCK_GATING_PORTD; /** Bit 12 of SIM_SCGC5 is set*/
			break;
		case GPIO_E: /** GPIO E is selected*/
			SIM->SCGC5 |= GPIO_CLOCK_GATING_PORTE; /** Bit 13 of SIM_SCGC5 is set*/
			break;
		default: /**If doesn't exist the option*/
			return(FALSE);
	}// end switch
	/**Successful configuration*/
	return(TRUE);
}// end function

uint8_t GPIO_pin_control_register(gpio_port_name_t port_name, uint8_t pin,const gpio_pin_control_register_t*  pin_control_register)
{

	switch(port_name)
		{
		case GPIO_A:/** GPIO A is selected*/
			PORTA->PCR[pin] = *pin_control_register;
			break;
		case GPIO_B:/** GPIO B is selected*/
			PORTB->PCR[pin] = *pin_control_register;
			break;
		case GPIO_C:/** GPIO C is selected*/
			PORTC->PCR[pin] = *pin_control_register;
			break;
		case GPIO_D:/** GPIO D is selected*/
			PORTD->PCR[pin] = *pin_control_register;
			break;
		case GPIO_E: /** GPIO E is selected*/
			PORTE->PCR[pin] = *pin_control_register;
		default:/**If doesn't exist the option*/
			return(FALSE);
		break;
		}
	/**Successful configuration*/
	return(TRUE);
}

void GPIO_write_port(gpio_port_name_t port_name, uint32_t data)
{
	switch(port_name)
	{
	case GPIO_A:
		GPIOA->PDOR |= data;
		break;
	case GPIO_B:
		GPIOB->PDOR |= data;
		break;
	case GPIO_C:
		GPIOC->PDOR |= data;
		break;
	case GPIO_D:
		GPIOD->PDOR |= data;
		break;
	case GPIO_E:
		GPIOE->PDOR |= data;
		break;
	}

}




uint32_t GPIO_read_port(gpio_port_name_t port_name)
{
	uint32_t read_value = 0;
	switch(port_name)
		{
		case GPIO_A:
			read_value = GPIOA->PDIR;
			break;
		case GPIO_B:
			read_value = GPIOB->PDIR;
			break;
		case GPIO_C:
			read_value = GPIOC->PDIR;
			break;
		case GPIO_D:
			read_value = GPIOD->PDIR;
			break;
		case GPIO_E:
			read_value = GPIOE->PDIR;
			break;
		default:
			read_value = FALSE;
			break;
		}
	return(read_value);
}




uint8_t GPIO_read_pin(gpio_port_name_t port_name, uint8_t pin)
{
	uint32_t read_value;
	switch(port_name)
		{
		case GPIO_A:
			read_value = GPIOA->PDIR;
			read_value &= (uint32_t)((0x01)<<(pin));
			read_value = (uint8_t)(read_value >> pin);
			break;
		case GPIO_B:
			read_value = GPIOB->PDIR;
			read_value &= (uint32_t)((0x01)<<(pin));
			read_value = (uint8_t)(read_value >> pin);
			break;
		case GPIO_C:
			read_value = GPIOC->PDIR;
			read_value &= (uint32_t)((0x01)<<(pin));
			read_value = (uint8_t)(read_value >> pin);
			break;
		case GPIO_D:
			read_value = GPIOD->PDIR;
			read_value &= (uint32_t)((0x01)<<(pin));
			read_value = (uint8_t)(read_value);
			break;
		case GPIO_E:
			read_value = GPIOE->PDIR;
			read_value &= (uint32_t)((0x01)<<(pin));
			read_value = (uint8_t)(read_value >> pin);
			break;
		default:
			return(FALSE);
		}
	return(read_value);
}




void GPIO_set_pin(gpio_port_name_t port_name, uint8_t pin)
{
	switch(port_name)
		{
		case GPIO_A:
			GPIOA->PSOR = (uint32_t)((0x01)<<(pin));
			break;
		case GPIO_B:
			GPIOB->PSOR = (uint32_t)((0x01)<<(pin));
			break;
		case GPIO_C:
			GPIOC->PSOR = (uint32_t)((0x01)<<(pin));
			break;
		case GPIO_D:
			GPIOD->PSOR = (uint32_t)((0x01)<<(pin));
			break;
		case GPIO_E:
			GPIOE->PSOR = (uint32_t)((0x01)<<(pin));
			break;
		}
}




void GPIO_clear_pin(gpio_port_name_t port_name, uint8_t pin)
{
	switch(port_name)
		{
		case GPIO_A:
			GPIOA->PCOR = (uint32_t)((0x01)<<(pin));
			break;
		case GPIO_B:
			GPIOB->PCOR = (uint32_t)((0x01)<<(pin));
			break;
		case GPIO_C:
			GPIOC->PCOR = (uint32_t)((0x01)<<(pin));
			break;
		case GPIO_D:
			GPIOD->PCOR = (uint32_t)((0x01)<<(pin));
			break;
		case GPIO_E:
			GPIOE->PCOR = (uint32_t)((0x01)<<(pin));
			break;
		}
}





void GPIO_toogle_pin(gpio_port_name_t port_name, uint8_t pin)
{
	switch(port_name)
		{
		case GPIO_A:
			GPIOA->PTOR = (uint32_t)((0x01)<<(pin));
			break;
		case GPIO_B:
			GPIOB->PTOR = (uint32_t)((0x01)<<(pin));
			break;
		case GPIO_C:
			GPIOC->PTOR = (uint32_t)((0x01)<<(pin));
			break;
		case GPIO_D:
			GPIOD->PTOR = (uint32_t)((0x01)<<(pin));
			break;
		case GPIO_E:
			GPIOE->PTOR = (uint32_t)((0x01)<<(pin));
			break;
		}
}




void GPIO_data_direction_port(gpio_port_name_t port_name ,uint32_t direction)
{
	switch(port_name)
		{
		case GPIO_A:
			GPIOA->PDDR |= GPIO_OUTPUT;
			break;
		case GPIO_B:
			GPIOB->PDDR |= GPIO_OUTPUT;
			break;
		case GPIO_C:
			GPIOC->PDDR |= GPIO_OUTPUT;
			break;
		case GPIO_D:
			GPIOD->PDDR |= GPIO_OUTPUT;
			break;
		case GPIO_E:
			GPIOE->PDDR |= GPIO_OUTPUT;
			break;
		}
}




void GPIO_data_direction_pin(gpio_port_name_t port_name, uint8_t state, uint8_t pin)
{
	switch(port_name)
		{
		case GPIO_A:/** GPIO A is selected*/
			if(state == GPIO_OUTPUT)
			{
				GPIOA->PDDR |=  (uint32_t)((0x01)<<(pin));
			}
			else
			{
				GPIOA->PDDR &=  ~(uint32_t)((0x01)<<(pin));

			}
			break;
		case GPIO_B:/** GPIO B is selected*/
			if(state == GPIO_OUTPUT)
			{
				GPIOB->PDDR |=  (uint32_t)((0x01)<<(pin));
			}
			else
			{
				GPIOB->PDDR &=  ~(uint32_t)((0x01)<<(pin));

			}
			break;
		case GPIO_C:/** GPIO C is selected*/
			if(state == GPIO_OUTPUT)
			{
				GPIOC->PDDR |=  (uint32_t)((0x01)<<(pin));
			}
			else
			{
				GPIOC->PDDR &=  ~(uint32_t)((0x01)<<(pin));
			}
			break;
		case GPIO_D:/** GPIO D is selected*/
			if(state == GPIO_OUTPUT)
			{
				GPIOD->PDDR |=  (uint32_t)((0x01)<<(pin));
			}
			else
			{
				GPIOD->PDDR &=  ~(uint32_t)((0x01)<<(pin));

			}
			break;
		case GPIO_E: /** GPIO E is selected*/
			if(state == GPIO_OUTPUT)
			{
				GPIOE->PDDR |=  (uint32_t)((0x01)<<(pin));
			}
			else
			{
				GPIOE->PDDR &=  ~(uint32_t)((0x01)<<(pin));

			}
			break;
		default:/**If doesn't exist the option*/
		break;
		}
}
