#pragma once
#include "Program_Default.h"
class Program_texture: public Program_Default {
	const char
		*NAME_POSITION_TEXTURE = "pos_texture",
		*NAME_TEXTURE_00 = "texture_00";
	
protected:
	void init_shader_locations() override;
public:
	GLuint
		id_pos_texture,
		id_texture_00;

	void use(float* mat_proj, float* mat_viewModel, GLuint texture);
};