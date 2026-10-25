#include <stdint.h>
#include <math.h>
#include "pico/stdlib.h"

const int KB_PIN[6] = {28,27,26,0,0,0}; // 2^i, lsb to msb

uint8_t get_pressed()
{
	uint8_t value = 0;
	for (int i=0;i<3;i++) {
		value += gpio_get(KB_PIN[i]) * pow(2,i);
	}
	return value;
}

void init_keyboard_pins()
{
	for (int i=0;i<3;i++) {
		gpio_init(KB_PIN[i]);
		gpio_set_dir(KB_PIN[i], GPIO_IN);
		gpio_pull_down(KB_PIN[i]);
	};
}
