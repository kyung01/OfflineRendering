#pragma once
#include "Program_Default.h"

class Program_View_Inverted :public Program_Default {

	char
		*NAME_MAT_VIEW_INVERSED = "mat_view_inverted";
public:
	GLuint id_mat_view_inversed;
	void init_uniformLocs() override;
	void use(float* mat_proj, float* mat_viewModel, float* mat_view_inversed);
};