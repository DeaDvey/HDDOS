#include <stdint.h>

#ifndef CHARACTER_H
#define CHARACTER_H

#define MAP_WIDTH 71

typedef struct {
	uint64_t map[MAP_WIDTH];
	char name;
} Character;

extern const Character a_bmp;
extern const Character* CHARACTER_SET[64];
extern const int CHAR_WIDTH;
extern const int CHAR_HEIGHT;

#endif
