#include "Program_Flux.h"



void Program_Flux::init_uniformLocs()
{
	Program_View_Inversed::init_uniformLocs();
	id_light_pos = glGetUniformLocation(id_program, NAME_LIGHT_POS);
	id_light_dir = glGetUniformLocation(id_program, NAME_LIGHT_DIR);
	id_light_color = glGetUniformLocation(id_program, NAME_LIGHT_COLOR);
}

void Program_Flux::use(
	float * mat_proj, float * mat_viewModel, float * mat_view_inverted, 
	float * light_pos, float * light_dir, float* light_color)
{
	Program_View_Inversed::use(mat_proj, mat_viewModel, mat_view_inverted);
	glUniform3f(id_light_pos, light_pos[0], light_pos[1], light_pos[2]);
	glUniform3f(id_light_dir, light_dir[0], light_dir[1], light_dir[2]);
	glUniform4f(id_light_color, light_color[0], light_color[1], light_color[2], light_color[3]);
}
