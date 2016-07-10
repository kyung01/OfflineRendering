#include "Program_ReflectiveShadowMap.h"

void Program_ReflectiveShadowMap::init_shader_locations()
{
	Program_View_Inverted::init_shader_locations();
	/*
		char*NAME_LIGHT_POS = "light_pos",
		*NAME_LIGHT_DIR = "light_dir",
		*NAME_LIGHT_COLOR = "light_color",
		*NAME_MATERIAL_COLOR = "material_color",
		* NAME_WORLD_SIZE = "world_size";
		*/


	world_size.init(id_program, "world_size", true, Easy_GLSL::GLSL_VARIABLE_TYPE::VEC3);
	light_pos.init(id_program, "light_pos", true, Easy_GLSL::GLSL_VARIABLE_TYPE::VEC3);
	light_dir.init(id_program, "light_dir", true, Easy_GLSL::GLSL_VARIABLE_TYPE::VEC3);
	light_color.init(id_program, "light_color", true, Easy_GLSL::GLSL_VARIABLE_TYPE::VEC4);
	material_color.init(id_program, "material_color", true, Easy_GLSL::GLSL_VARIABLE_TYPE::VEC4);
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
	this->world_size.assign(world_size);
	this->light_pos.assign(light_pos);
	this->light_dir.assign(light_dir);
	this->light_color.assign(light_color);
	this->material_color.assign(material_Color);
}
