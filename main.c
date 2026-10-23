/*
https://files.waveshare.com/wiki/common/ST7796S_Datasheet.pdf
*/
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include <stdint.h>
#include <stdbool.h>

#include "display.h"
#include "character_set/character.h"

void led_status();

int main(void)
{
	led_status(); // turn on the onboard LED
	init_lcd();
	draw_character(CHARACTER_SET[0],0x00f8);

	/*
	while (true) {
		tight_loop_contents();
	}*/
}

// turn the onboard LED on as a status indicator
void led_status()
{
	const uint LED_PIN = PICO_DEFAULT_LED_PIN;
	gpio_init(LED_PIN);
	gpio_set_dir(LED_PIN, GPIO_OUT);
	gpio_put(LED_PIN, 1);
}
