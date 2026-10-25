#include "character.h"

const int CHAR_WIDTH = 40;
const int CHAR_HEIGHT = MAP_WIDTH;

const Character* CHARACTER_SET[64] = {
	&null_bmp,
	&a_bmp,
	&b_bmp,
	&c_bmp,
	&d_bmp,
	&e_bmp,
	&f_bmp,
	&g_bmp,
	&h_bmp,
	&i_bmp,
	&j_bmp,
	&k_bmp,
	&l_bmp,
	&m_bmp,
	&n_bmp,
	&o_bmp,
	&p_bmp,
	&q_bmp,
	&r_bmp,
	&s_bmp,
	&t_bmp,
	&u_bmp,
	&v_bmp,
	&w_bmp,
	&x_bmp,
	&y_bmp,
	&z_bmp,
	&space_bmp,
	&null_bmp, // non printing control characters
	&null_bmp,
	&null_bmp,
};
