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

	for (int i=0; i<4; i++) {
		gpio_set_irq_enabled_with_callback(KB_PIN[i], GPIO_IRQ_EDGE_RISE, true, &interrupt_pressed);
	}

	start_tty();

	return 0;
}

