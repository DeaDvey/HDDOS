#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <ctype.h>
#include "text.h"
#include "display.h"
#include "character_set/character.h"

void print_madscii(const uint8_t* string, uint8_t pos_x, uint8_t pos_y, bool wrap)
{
	int i = 0;
	while (string[i] != 0)
	{
		if (string[i] == 0x1c) {
				pos_x = 0;
				pos_y++;
				i++;
				continue;
		};
		draw_character(CHARACTER_SET[string[i]], 0x00f8, 0xffff, pos_x, pos_y);
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

void print_ascii(const char* ascii_string, uint8_t pos_x, uint8_t pos_y, bool wrap)
{
	uint8_t string[strlen(ascii_string)];
	ascii_to_madscii(ascii_string, string);
	print_madscii(string, pos_x, pos_y, wrap);
}

void ascii_to_madscii(const char* string, uint8_t* output)
{
	int i = 0;
	bool done = false;
	while (! done) {
		char current_letter = tolower(string[i]);
		if (current_letter >= 0x61 && current_letter <= 0x7a)
				output[i] = current_letter-'a'+1;
		else {
			switch (current_letter) {
				case 0: // null
					output[i] = 0x00;
					done = true;
					break;
				case 0x0a:
					output[i] = 0x1c;
					break;
				case 0x08: // backspace, so remove previous character
					i-=2;
					output[i] = 0x00;
					break;
				case 0x20: // space
					output[i] = 0x1b;
					break;
				default:
					i--;
					break;
			}
		}
		i++;
	}
}
