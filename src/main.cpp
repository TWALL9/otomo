#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/cm3/systick.h>
#include "timer.h"
#include "delay.h"
#include "usart.h"
#include "gpio.h"
#include "log.h"
#include "ultrasonic.h"
#include "h_bridge.h"

static void clock_setup(void) 
{
    rcc_clock_setup_pll(&rcc_hse_8mhz_3v3[RCC_CLOCK_3V3_168MHZ]);
    rcc_periph_clock_enable(RCC_TIM2);
	rcc_periph_clock_enable(RCC_TIM3);
	rcc_periph_clock_enable(RCC_TIM4);
    rcc_periph_clock_enable(RCC_TIM14);

	rcc_periph_clock_enable(RCC_USART2);
}

/* Set up a timer to create 1mS ticks. */
static void systick_setup(void)
{
	/* clock rate / 1000 to get 1mS interrupt rate */
	systick_set_reload(168000);
	systick_set_clocksource(STK_CSR_CLKSOURCE_AHB);
	systick_counter_enable();
	/* this done last */
	systick_interrupt_enable();
}

void gpio_setup(void) 
{
	/* clocks */
	rcc_periph_clock_enable(RCC_GPIOA);
	rcc_periph_clock_enable(RCC_GPIOB);
	rcc_periph_clock_enable(RCC_GPIOC);
	rcc_periph_clock_enable(RCC_GPIOD);

    /* LEDS on discovery board */
    gpio_mode_setup(GPIOD, GPIO_MODE_OUTPUT,
            GPIO_PUPD_NONE, LED_GREEN | LED_ORANGE | LED_RED | LED_BLUE);
    gpio_clear(GPIOD, LED_GREEN | LED_ORANGE | LED_RED | LED_BLUE);

    /* Motor PWM outputs */
    gpio_mode_setup(GPIOB, GPIO_MODE_AF, GPIO_PUPD_PULLDOWN, 
			GPIO7 | GPIO8 |GPIO10 | GPIO11);
    gpio_clear(GPIOB, GPIO7 | GPIO8 | GPIO10 | GPIO11);

    /* AF1 is timer 2 channel 2/3 output for pin 10 and 11 */
    gpio_set_af(GPIOB, GPIO_AF1, GPIO10 | GPIO11);
	/* AF2 is timer 4 channel 2/3 output on pin 7 and 8 */
    gpio_set_af(GPIOB, GPIO_AF2, GPIO7 | GPIO8);

	gpio_mode_setup(GPIOC, GPIO_MODE_AF, GPIO_PUPD_PULLDOWN, 
			GPIO6 | GPIO7 | GPIO8 | GPIO9);
    gpio_clear(GPIOC, GPIO6 | GPIO7 | GPIO8 | GPIO9);
    gpio_set_af(GPIOC, GPIO_AF2, GPIO6 | GPIO7 | GPIO8 | GPIO9);
}

int main(void) 
{
    clock_setup();
    systick_setup();
    timer_setup();
    gpio_setup();
	usart_setup();

	int16_t pulse = 1000/3;
	
	HBridge hb = HBridge(TIM2, TIM_OC3, TIM2, TIM_OC4);
    uint8_t mode = NEUTRAL;
    
    log_init();

    for (;;) 
    {
        if (mode == DRIVE)
        {
            pulse = pulse * -1;
        }
        hb.set_mode((drive_mode_t)mode);
        hb.set_duty(pulse);
        hb.drive();
        DEBUG("%d", mode);
        delay_ms(1000);
        mode = (mode == BRAKE) ? NEUTRAL : mode + 1;
    }

    return 0;
}
