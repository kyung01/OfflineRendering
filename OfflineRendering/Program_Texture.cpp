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
