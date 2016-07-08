#include "Program_View_Inverted.h"


void Program_View_Inverted::init_shader_locations()
{
	Program_Default::init_shader_locations();
	mat_view_inverted.init(id_program, "mat_view_inverted",true, Easy_GLSL::GLSL_VARIABLE_TYPE::MAT4);
	//id_mat_view_inversed = glGetUniformLocation(id_program, NAME_MAT_VIEW_INVERSED);
}

void Program_View_Inverted::use(float * mat_proj, float * mat_viewModel, float * dat_mat_view_inverted)
{
	Program_Default::use(mat_proj, mat_viewModel);

	//glUniformMatrix4fv(id_mat_view_inversed, 1, GL_FALSE, dat_mat_view_inverted);
	this->mat_view_inverted.assign(dat_mat_view_inverted);
}
