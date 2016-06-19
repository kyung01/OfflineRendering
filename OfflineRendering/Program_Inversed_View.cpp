#include "Program_Inversed_View.h"

bool Program_Inversed_View::init(const char * path_vert, const char * path_frag)
{
	bool result = Program_Default::init(path_vert, path_frag);
	id_mat_view_inversed = glGetUniformLocation(id_program, NAME_MAT_VIEW_INVERSED);
	return result;
}

void Program_Inversed_View::use(float * mat_proj, float * mat_viewModel, float * mat_view_inversed)
{
	Program_Default::use(mat_proj, mat_viewModel);

	glUniformMatrix4fv(id_mat_view_inversed, 1, GL_FALSE, mat_view_inversed);
}
