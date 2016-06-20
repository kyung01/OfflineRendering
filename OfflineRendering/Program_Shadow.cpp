#include "Program_Shadow.h"

bool Program_Shadow::init(const char * path_vert, const char * path_frag)
{
	bool result = Program_View_Inversed::init(path_vert, path_frag);
	id_texture_depth =	glGetUniformLocation(id_program, NAME_TEXTURE_DEPTH);
	id_mat_light =		glGetUniformLocation(id_program, NAME_MAT_LIGHT);
	return result;
}

void Program_Shadow::use(float * proj, float * modelView,float * view_inverted , float * mat_light,GLuint texture_shadow)
{
	Program_View_Inversed::use(proj, modelView, view_inverted);
	glUniformMatrix4fv(id_mat_light, 1, GL_FALSE, mat_light);
	glUniform1i(id_texture_depth, 0);

	glActiveTexture(GL_TEXTURE0); // Texture unit 0
	glBindTexture(GL_TEXTURE_2D, texture_shadow);
}

void Program_Shadow::unUse()
{
	Program_Default::unUse();
	glBindTexture(GL_TEXTURE_2D, 0);
}
