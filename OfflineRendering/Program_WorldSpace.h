#pragma once
#include "Program_View_Inverted.h"
class Program_WorldSpace: public Program_View_Inverted {
public:
	char * NAME_WORLD_SIZE = "world_size";
	GLuint id_world_size;
	void init_uniformLocs() override;
	void use(float *mat_proj, float* mat_viewModel, float* mat_view_inversed, float* world_size);
};