#include "Program_Texture.h"

void Program_texture::init_shader_locations()
{
	Program_Default::init_shader_locations();
	id_pos_texture = glGetAttribLocation(id_program, NAME_POSITION_TEXTURE);
	id_texture_00 = glGetUniformLocation(id_program, NAME_TEXTURE_00);
}


 void Program_texture::use(float * mat_proj, float * mat_viewModel, GLuint texture)
 {
	 Program_Default::use(mat_proj, mat_viewModel);
	 glActiveTexture(GL_TEXTURE0); // Texture unit 0
	 glBindTexture(GL_TEXTURE_2D, texture);
	 glUniform1i(id_texture_00, 0);
 }
