#pragma once
#include "Program_View_Inversed.h"
class Program_WorldSpace: public Program_View_Inversed {
public:
	char * NAME_WORLD_SIZE = "world_size";
	GLuint id_world_size;
	bool init(const char * path_vert, const char * path_frag) override;
	void use(float *mat_proj, float* mat_viewModel, float* mat_view_inversed, float* world_size);
};