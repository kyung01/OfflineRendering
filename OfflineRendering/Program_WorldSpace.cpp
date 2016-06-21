#include "Program_WorldSpace.h"



void Program_WorldSpace::init_uniformLocs()
{
	Program_View_Inverted::init_uniformLocs();
	this->id_world_size = glGetUniformLocation(this->id_program, NAME_WORLD_SIZE);

}

void Program_WorldSpace::use(float * mat_proj, float * mat_viewModel, float * mat_view_inversed, float * world_size)
{
	Program_View_Inverted::use(mat_proj, mat_viewModel, mat_view_inversed);
	glUniform3fv(id_world_size, 1, world_size);

}
