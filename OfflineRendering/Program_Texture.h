#pragma once
#include "Program_Default.h"
class Program_texture: public Program_Default {
	const char
		*NAME_POSITION_TEXTURE = "pos_texture",
		*NAME_TEXTURE_00 = "texture_00";
	
public:
	GLuint
		id_pos_texture,
		id_texture_00;
	Program_texture();

	bool init(const char* path_vert, const char* path_frag) override;// initialize 
};