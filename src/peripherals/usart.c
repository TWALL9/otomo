#ifdef __cplusplus
extern "C" {
#endif

#include "peripherals/usart.h"
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>

static void usart_pin_setup(uint32_t usart_base)
{
	switch (usart_base)
	{
		case USART1:
		{
			/* Bluetooth TX/RX */
			gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP,
				GPIO9 | GPIO10);
			gpio_set_af(GPIOA, GPIO_AF7, GPIO9 | GPIO10);
			break;
		}
		case USART2:
		{
			/* Debug output USART */
			gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP,
				GPIO2 | GPIO3);
			gpio_set_af(GPIOA, GPIO_AF7, GPIO2 | GPIO3);
			break;
		}
		default:
			break;
	}
}

// someone's gotta typedef these rcc enums
static void usart_clock_setup(uint32_t usart_base)
{
	switch (usart_base)
	{
		case USART1:
		{
			rcc_periph_clock_enable(RCC_USART1);
			break;
		}
		case USART2:
		{
			rcc_periph_clock_enable(RCC_USART2);
			break;
		}
		case USART3:
		{
			rcc_periph_clock_enable(RCC_USART3);
			break;
		}
		case UART4:
		{
			rcc_periph_clock_enable(RCC_UART4);
			break;
		}
		case UART5:
		{
			rcc_periph_clock_enable(RCC_UART5);
			break;
		}
		default:
			break;
	}
}

void usart_setup(
    uint32_t usart_base, 
    uint32_t baud_rate, 
    uint32_t data_bits, 
    uint32_t stop_bits, 
    uint32_t mode, 
    uint32_t parity, 
    uint32_t flowcontrol
)
{
	usart_clock_setup(usart_base);
	usart_pin_setup(usart_base);

	usart_set_baudrate(usart_base, baud_rate);
	usart_set_databits(usart_base, data_bits);
	usart_set_stopbits(usart_base, stop_bits);
	usart_set_mode(usart_base, mode);
	usart_set_parity(usart_base, parity);
	usart_set_flow_control(usart_base, flowcontrol);

	usart_enable(usart_base);
}

void usart_send_buf(uint32_t usart_base, const char * buf, uint16_t len)
{
    uint8_t i;
    for (i = 0; i < len; i++)
    {
        char c = buf[i];
        usart_send_blocking(usart_base, c);
    }
}

bool is_usart_base(uint32_t usart_base)
{
	switch (usart_base)
	{
		case USART1:
		case USART2:
		case USART3:
		case UART4:
		case UART5:
			return true;
		default:
			return false;
	}
}

#ifdef __cplusplus
}
#endif