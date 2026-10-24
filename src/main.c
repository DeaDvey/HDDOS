#include "pico/stdlib.h"
#include "hardware/spi.h"
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "pico.h"
#include "display.h"
#include "text.h"
#include "character_set/character.h"

int main(void)
{
	led_status(true); // turn on the onboard LED
	init_lcd();
	/*
	draw_character(CHARACTER_SET[0],0x00f8,0,0);
	draw_character(CHARACTER_SET[1],0x00f8,1,0);
	draw_character(CHARACTER_SET[2],0x00f8,2,0);
	*/
	char string[] = "abba\ncab\ndaabaca";
	print_to_coords(string, 0,0,true);

	/*
	while (true) {
		tight_loop_contents();
	}*/
}

