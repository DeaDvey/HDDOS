#include "character_set/character.h"

void backlight(bool state);
void hardware_reset(void);
void draw_rect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t colour);
void draw_pixel(uint16_t x, uint16_t y, uint16_t colour);
void draw_character(const Character* c, uint16_t colour, uint8_t pos_x, uint8_t pos_y);
void init_lcd(void);

extern const int SCREEN_HEIGHT;
extern const int SCREEN_WIDTH;
