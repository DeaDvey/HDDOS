#include "pico/stdlib.h"

void init_pin(const uint pin);

// turn the onboard LED on as a status indicator
void led_status(bool status)
{
	init_pin(PICO_DEFAULT_LED_PIN);
	gpio_put(PICO_DEFAULT_LED_PIN, status);
}

void init_pin(const uint pin)
{
	gpio_init(pin);
	gpio_set_dir(pin, GPIO_OUT);
}
