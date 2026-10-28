//Return instantly, 0x00 (NULL) if nothing is pressed
//Assumes the pins have been initialised
void interrupt_pressed(uint gpio, uint32_t events);
uint8_t get_pressed();
uint8_t get_pressed_blocking();
uint8_t get_pressed_for(int time);
uint8_t get_multi_tap_input();
void init_keyboard_pins();

extern const int KB_PIN[6];
