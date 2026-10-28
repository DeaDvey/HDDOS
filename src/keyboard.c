#include <stdint.h>
#include <math.h>
#include "pico/stdlib.h"

#include "text.h"

/*                                a b c   d e f   g h i   j     k     l      m     n     o      p     q     r     s */
const int MULTI_TAP_MAP[6][6] = {{1,2,3},{4,5,6},{7,8,9},{0x0a, 0x0b, 0x0c},{0x0d, 0x0e, 0x0f},{0x10, 0x11, 0x12, 0x13}};
const int KB_PIN[6] = {28,27,26,0,0,0}; // 2^i, lsb to msb
volatile uint8_t kb_buffer = 0;

void interrupt_pressed(uint gpio, uint32_t events)
{
	sleep_ms(2);
	uint8_t value = 0;
	for (int i=0;i<3;i++) {
		value |= gpio_get(KB_PIN[i]) << i;
	}
	kb_buffer = value;
}

uint8_t get_pressed()
{
	uint8_t value = kb_buffer;
	kb_buffer = 0;
	return value;
}

uint8_t get_pressed_blocking()
{
	int current_key = kb_buffer;
	uint8_t value = 0;
	while (value == 0) {
		for (int i=0;i<3;i++) {
			value |= gpio_get(KB_PIN[i]) << i;
		}
	}
	return value;
}

uint8_t get_pressed_for(int time)
{
	for (int j=0;j<time;j++) {
		int current_key = kb_buffer;
		uint8_t value = 0;
		for (int i=0;i<3;i++) {
			value |= gpio_get(KB_PIN[i]) << i;
		}
		if (value != 0) { return value; };
		sleep_ms(1);
	}
	return 0;
}

uint8_t get_multi_tap_input()
{
	int timeout_ms = 1000;
	const int interval = 1;
	uint8_t value = get_pressed(); // reset kb_buffer to 0
	if (value == 0) { return 0; };
	int presses = 0; // initialise to 0

	// get no taps in this time
	multi_tap_start:
	for (int i=0; i<(timeout_ms/interval); i++) {
		if (kb_buffer == value) {
			presses += 1;
			kb_buffer = 0; // reset kb_buffer
			goto multi_tap_start;
		}
		else if (kb_buffer != 0) { // some other key is pressed
			goto multi_tap_end;
		}
		sleep_ms(interval);
	}
	multi_tap_end:
	const int *sub_map = MULTI_TAP_MAP[value-1];

	// Get the number of chars on the key
	int sub_map_len = 1; // must be at least 1
	for (sub_map_len=1; sub_map_len<6; sub_map_len++) {
		if (sub_map[sub_map_len] == 0) {
			break;
		}
	};

	// Get the final key
	int index = presses % sub_map_len;
	return sub_map[index];
}

void init_keyboard_pins()
{
	for (int i=0;i<3;i++) {
		gpio_init(KB_PIN[i]);
		gpio_set_dir(KB_PIN[i], GPIO_IN);
		gpio_pull_down(KB_PIN[i]);
	};
}
