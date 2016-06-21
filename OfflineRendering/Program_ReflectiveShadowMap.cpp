#include "Program_ReflectiveShadowMap.h"

void Program_ReflectiveShadowMap::init_uniformLocs()
{
	Program_View_Inverted::init_uniformLocs();
	id_light_pos = glGetUniformLocation(id_program, NAME_LIGHT_POS);
	id_light_dir = glGetUniformLocation(id_program, NAME_LIGHT_DIR);
	id_light_color = glGetUniformLocation(id_program, NAME_LIGHT_COLOR);
	id_material_color = glGetUniformLocation(id_program, NAME_MATERIAL_COLOR);
	//id_tex_worldPosition = glGetUniformLocation(id_program, NAME_TEXTURE_WORLDPOSITION);
	//id_tex_normal = glGetUniformLocation(id_program, NAME_TEXTURE_NORMAL);
	//id_tex_flux = glGetUniformLocation(id_program, NAME_TEXTURE_FLUX);
}

void Program_ReflectiveShadowMap::use(
	float * mat_proj, float * mat_viewModel, float * mat_view_inverted, 
	float * light_pos, float * light_dir, float * light_color, float*material_Color)
{
	Program_View_Inverted::use(mat_proj, mat_viewModel, mat_view_inverted);
}
