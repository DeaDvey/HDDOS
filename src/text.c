#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "text.h"
#include "display.h"
#include "character_set/character.h"

void print_to_coords(const char* ascii_string, uint8_t pos_x, uint8_t pos_y, bool wrap)
{
	uint8_t string[strlen(ascii_string)];
	ascii_to_madscii(ascii_string, string);
	int i = 0;
	while (string[i] != 0)
	{
		if (string[i] == 0x1c) {
				pos_x = 0;
				pos_y++;
				i++;
				continue;
		};
		draw_character(CHARACTER_SET[string[i]], 0x00f8, pos_x, pos_y);
		pos_x++;
		if (pos_x >= (SCREEN_WIDTH/CHAR_WIDTH)) {
			if (wrap) { // If wrap is set, then just wrap to the next line
				pos_x = 0;
				pos_y++;
			}
			else return;
		}
		i++;
	};
}

void ascii_to_madscii(const char* string, uint8_t* output)
{
	int i = 0;
	bool done = false;
	while (! done) {
		switch (string[i]) {
			case 0:
				output[i] = 0x00;
				done = true;
				break;
			case 'a':
				output[i] = 0x01;
				break;
			case 'b':
				output[i] = 0x02;
				break;
			case 'c':
				output[i] = 0x03;
				break;
			case 'd':
				output[i] = 0x04;
				break;
			case 0x0a:
				output[i] = 0x1c;
				break;
			default:
				i--;
				break;
		}
		i++;
	}
}
