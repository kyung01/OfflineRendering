#pragma once
#include "Program_View_Inverted.h"
class Program_ReflectiveShadowMap : public Program_View_Inverted {


protected:
	void init_shader_locations() override;
public:
	Shader_Element 
		world_size,
		light_pos, light_dir, light_power, light_color, material_color;

	void use(
		float* mat_proj, float* mat_viewModel, float* mat_view_inverted,
		float* world_size,
		float* light_pos, float* light_dir, float* light_color,
		float * material_color);
};