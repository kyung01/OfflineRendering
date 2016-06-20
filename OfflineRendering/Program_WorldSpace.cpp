#include "Program_WorldSpace.h"

bool Program_WorldSpace::init(const char * path_vert, const char * path_frag)
{
	bool result = Program_View_Inversed::init(path_vert, path_frag);
	this->id_world_size = glGetUniformLocation(this->id_program, NAME_WORLD_SIZE);
	return result;
}

void Program_WorldSpace::use(float * mat_proj, float * mat_viewModel, float * mat_view_inversed, float * world_size)
{
	Program_View_Inversed::use(mat_proj, mat_viewModel, mat_view_inversed);
	glUniform3fv(id_world_size, 1, world_size);

}
