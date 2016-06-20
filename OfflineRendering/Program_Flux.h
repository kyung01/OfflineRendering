#pragma once
#include "Program_View_Inversed.h"
class Program_Flux :public Program_View_Inversed {
public:
	char*NAME_LIGHT_POS = "light_pos",
		*NAME_LIGHT_DIR = "light_dir",
		*NAME_LIGHT_COLOR = "light_color";
	GLuint id_light_pos, id_light_dir, id_light_color;
	void init_uniformLocs() override;
	void use(
		float* mat_proj, float* mat_viewModel, float* mat_view_inverted, 
		float *light_pos, float * light_dir, float *light_color);
};