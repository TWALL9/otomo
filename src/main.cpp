#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/cm3/systick.h>
#include "peripherals/timer.h"
#include "utils/delay.h"
#include "peripherals/usart.h"
#include "peripherals/gpio.h"
#include "utils/debug.h"
#include "drivers/ultrasonic.h"
#include "drivers/h_bridge.h"
#include "drivers/continuous_servo.h"
#include "drivers/bluetooth.h"

static void clock_setup(void) 
{
    rcc_clock_setup_pll(&rcc_hse_8mhz_3v3[RCC_CLOCK_3V3_168MHZ]);
    rcc_periph_clock_enable(RCC_TIM2);
	rcc_periph_clock_enable(RCC_TIM3);
	rcc_periph_clock_enable(RCC_TIM4);
    rcc_periph_clock_enable(RCC_TIM14);
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

    SerialDebug debug = SerialDebug(USART1, 115200);
    debug.set_handle("main");

	int16_t pulse[] = {-1000, -500, 0, 500, 1000};
    uint8_t i = 0;

    //motors::ContinuousServo cs = motors::ContinuousServo(TIM2, TIM_OC3);
    //cs.set_drive_mode(motors::DRIVE);
    motors::HBridge hb = motors::HBridge(TIM2, TIM_OC3, TIM2, TIM_OC4);
    hb.set_drive_mode(motors::drive_mode_t::DRIVE);

    debug.debug(LOG_LEVEL_DEBUG, "hey");

    HC06 b = HC06(USART2);

    for (;;) 
    {
        // delay_ms(1000);
        b.start();
        uint8_t res[10];
        // uint16_t len = b.read_blocking(res);

    }

    return 0;
}
