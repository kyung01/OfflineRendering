#include "Program_ReflectiveShadowMap.h"

void Program_ReflectiveShadowMap::init_uniformLocs()
{
	Program_View_Inverted::init_uniformLocs();
	id_light_pos = glGetUniformLocation(id_program, NAME_LIGHT_POS);
	id_light_dir = glGetUniformLocation(id_program, NAME_LIGHT_DIR);
	id_light_color = glGetUniformLocation(id_program, NAME_LIGHT_COLOR);
	id_material_color = glGetUniformLocation(id_program, NAME_MATERIAL_COLOR);
	id_world_size = glGetUniformLocation(id_program, NAME_WORLD_SIZE);
	//id_tex_worldPosition = glGetUniformLocation(id_program, NAME_TEXTURE_WORLDPOSITION);
	//id_tex_normal = glGetUniformLocation(id_program, NAME_TEXTURE_NORMAL);
	//id_tex_flux = glGetUniformLocation(id_program, NAME_TEXTURE_FLUX);
}

void Program_ReflectiveShadowMap::use(
	float * mat_proj, float * mat_viewModel, float * mat_view_inverted, 
	float * world_size,
	float * light_pos, float * light_dir, float * light_color, float*material_Color)
{
	Program_View_Inverted::use(mat_proj, mat_viewModel, mat_view_inverted);
	glUniform3f(id_world_size, world_size[0], world_size[1], world_size[2]);


	glUniform3f(id_light_pos, light_pos[0], light_pos[1], light_pos[2]);
	glUniform3f(id_light_dir, light_dir[0], light_dir[1], light_dir[2]);
	glUniform4f(id_light_color, light_color[0], light_color[1], light_color[2], light_color[3]);
	glUniform4f(id_material_color, material_Color[0], material_Color[1], material_Color[2], material_Color[3]);
}
