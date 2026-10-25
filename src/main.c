#include "pico/stdlib.h"
#include "hardware/spi.h"
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "pico.h"
#include "display.h"
#include "text.h"
#include "keyboard.h"
#include "tty.h"
#include "character_set/character.h"

int main(void)
{
	// setup
	led_status(true); // turn on the onboard LED
	init_lcd();
	init_keyboard_pins();

	char string[] = "hello world";
	print_to_coords(string, 0,0,true);

	while (true)
	{
		int value = get_pressed();
		draw_character(CHARACTER_SET[value], 0x00f8, 0xffff, 0, 1);
		sleep_ms(100);
	}

}

