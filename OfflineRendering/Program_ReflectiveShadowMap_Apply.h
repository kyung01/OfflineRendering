#pragma once
#include "Program_View_Inverted.h"
class Program_ReflectiveShadowMap_Apply : public Program_View_Inverted {
	char
		*NAME_MAT_LIGHT = "mat_light",
		*NAME_TEXTURE_POSITION = "texture_position",
		*NAME_TEXTURE_DEPTH = "texture_depth",
		*NAME_TEXTURE_NORMAL = "texture_normal",
		*NAME_TEXTURE_FLUX = "texture_flux",
		*NAME_WORLD_SIZE = "world_size",
		*NAME_RAND_SEED = "RAND_SEED",
		*NAME_MATERIAL_COLOR = "material_color";
protected:
	void init_shader_locations() override;
public:
	GLuint
		id_mat_light, id_world_size,
		id_texture_position, id_texture_depth, id_texture_normal, id_texture_flux, id_rand_seed,
		id_material_color;
	void use(
		float* mat_proj, float* mat_viewModel, float* mat_view_inverted, float* mat_light,
		float* world_size,
		GLuint texture_position,GLuint texture_depth, GLuint texture_normal, GLuint texture_flux);
	void set_rand_seed(float n);


	
};