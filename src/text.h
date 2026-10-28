#include <stdint.h>
// Start printing at the coords (pos_x,pos_y) and continue printing until the string is all printed, none MADSCII characters are ignored
// If wrap is enabled, a string that reaches the edge of the screen will wrap to the next line
void print_madscii(const uint8_t* string, uint8_t pos_x, uint8_t pos_y, bool wrap);
void print_ascii(const char* ascii_string, uint8_t pos_x, uint8_t pos_y, bool wrap);

// Return a MADSCII encoded array from an ASCII string
void ascii_to_madscii(const char* string, uint8_t* output);
