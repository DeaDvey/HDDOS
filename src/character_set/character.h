#include <stdint.h>

#ifndef CHARACTER_H
#define CHARACTER_H

#define MAP_WIDTH 71

typedef struct {
	uint64_t map[MAP_WIDTH];
	char name;
} Character;

extern const Character null_bmp;
extern const Character a_bmp;
extern const Character b_bmp;
extern const Character c_bmp;
extern const Character d_bmp;
extern const Character e_bmp;
extern const Character f_bmp;
extern const Character g_bmp;
extern const Character h_bmp;
extern const Character i_bmp;
extern const Character j_bmp;
extern const Character k_bmp;
extern const Character l_bmp;
extern const Character m_bmp;
extern const Character n_bmp;
extern const Character o_bmp;
extern const Character p_bmp;
extern const Character q_bmp;
extern const Character r_bmp;
extern const Character s_bmp;
extern const Character t_bmp;
extern const Character u_bmp;
extern const Character v_bmp;
extern const Character w_bmp;
extern const Character x_bmp;
extern const Character y_bmp;
extern const Character z_bmp;
extern const Character space_bmp;

extern const Character* CHARACTER_SET[64];
extern const int CHAR_WIDTH;
extern const int CHAR_HEIGHT;

#endif
