#include "Program_Texture.h"

Program_texture::Program_texture()
{
}

 bool Program_texture::init(const char * path_vert, const char * path_frag) 
{
	bool result = Program_Default::init(path_vert, path_frag);
	id_pos_texture = glGetAttribLocation(id_program, NAME_POSITION_TEXTURE);
	id_texture_00 = glGetUniformLocation(id_program, NAME_TEXTURE_00);
	return result;
}

 void Program_texture::use(float * mat_proj, float * mat_viewModel, GLuint texture)
 {
	 Program_Default::use(mat_proj, mat_viewModel);
	 glActiveTexture(GL_TEXTURE0); // Texture unit 0
	 glBindTexture(GL_TEXTURE_2D, texture);
	 glUniform1i(id_texture_00, 0);
 }
