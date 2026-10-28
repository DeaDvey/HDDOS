#include <stdint.h>
#include "pico/stdlib.h"
#include "display.h"
#include "keyboard.h"
#include "text.h"

void start_tty() {
	char string[] = "start";
	print_ascii(string, 0,0,true);
	while (true) {
		uint8_t value = get_multi_tap_input();
		if (value != 0) {
			draw_character(CHARACTER_SET[value], 0x00f8, 0xffff, 0,1);
		}
	}
}
