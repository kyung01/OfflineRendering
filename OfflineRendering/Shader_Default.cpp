#include "Shader_Default.h"

Shader_Default::Shader_Default(GLuint id_program):
	id_proj_matrix(glGetUniformLocation(id_program, "projMatrix"))
{
}
