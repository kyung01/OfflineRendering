#include "Program_Deferred.h"

void Program_Deferred::init_shader_locations()
{
	Program_View_Inverted::init_shader_locations();
	world_size.init(id_program, "world_size", true, Easy_GLSL::GLSL_VARIABLE_TYPE::VEC3);
	material_color.init(id_program, "material_color", true, Easy_GLSL::GLSL_VARIABLE_TYPE::VEC4);
}
