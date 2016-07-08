#pragma once
#include "Program_Default.h"

class Program_View_Inverted :public Program_Default {

	char
		*NAME_MAT_VIEW_INVERSED = "mat_view_inverted";
public:
	Shader_Element mat_view_inverted;

	GLuint id_mat_view_inversed;
	void init_shader_locations() override;
	void use(float* mat_proj, float* mat_viewModel, float* mat_view_inversed);
};