#include "character_set/character.h"

void initialise_pins(void);
void backlight(bool state);
void hardware_reset(void);
void send_command(uint8_t cmd, const uint8_t data[], size_t length);
void set_coords(uint16_t x1, uint16_t x2, uint16_t y1, uint16_t y2);
void draw_rect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t colour);
void draw_pixel(uint16_t x, uint16_t y, uint16_t colour);
void draw_character(const Character* c, uint16_t colour);
void init_lcd(void);
