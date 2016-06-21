#include "Program_View_Inverted.h"


void Program_View_Inverted::init_uniformLocs()
{
	Program_Default::init_uniformLocs();
	id_mat_view_inversed = glGetUniformLocation(id_program, NAME_MAT_VIEW_INVERSED);
}

void Program_View_Inverted::use(float * mat_proj, float * mat_viewModel, float * mat_view_inversed)
{
	Program_Default::use(mat_proj, mat_viewModel);

	glUniformMatrix4fv(id_mat_view_inversed, 1, GL_FALSE, mat_view_inversed);
}
