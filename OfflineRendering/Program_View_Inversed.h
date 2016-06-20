#pragma once
#include "Program_Default.h"

class Program_View_Inversed :public Program_Default {

	char
		*NAME_MAT_VIEW_INVERSED = "mat_view_inversed";
public:
	GLuint id_mat_view_inversed;
	bool init(const char * path_vert, const char * path_frag);
	void use(float* mat_proj, float* mat_viewModel, float* mat_view_inversed);
};