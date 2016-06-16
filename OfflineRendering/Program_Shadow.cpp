#include "Program_Shadow.h"

bool Program_Shadow::init(const char * path_vert, const char * path_frag)
{
	bool result = Program_Default::init(path_vert, path_frag);
	id_texture_depth =	glGetUniformLocation(id_program, NAME_TEXTURE_DEPTH);
	id_mat_light =		glGetUniformLocation(id_program, NAME_MAT_LIGHT);
	return result;
}
