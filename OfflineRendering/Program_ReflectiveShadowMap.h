#pragma once
#include "Program_View_Inverted.h"
class Program_ReflectiveShadowMap : public Program_View_Inverted {
	char*NAME_LIGHT_POS = "light_pos",
		*NAME_LIGHT_DIR = "light_dir",
		*NAME_LIGHT_COLOR = "light_color",
		*NAME_MATERIAL_COLOR = "material_color";
	/*
		*NAME_TEXTURE_WORLDPOSITION = "texture_worldPosition",
		*NAME_TEXTURE_NORMAL = "texture_normal",
		*NAME_TEXTURE_FLUX = "texture_flux";
	*/
public:
	GLuint 
		id_light_pos, id_light_dir, id_light_color,
		id_tex_worldPosition, id_tex_normal, id_tex_flux,
		id_material_color;
	void init_uniformLocs() override;
	void use(
		float* mat_proj, float* mat_viewModel, float* mat_view_inverted,
		float* light_pos, float* light_dir, float* light_color,
		float * material_color);
};