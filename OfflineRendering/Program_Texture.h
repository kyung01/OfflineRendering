#pragma once
#include "Program_Default.h"
class Program_texture: public Program_Default {
	const char
		*NAME_POSITION_TEXTURE = "pos_texture";
	GLuint
		id_pos_texture;
public:
	Program_texture();

	bool init(const char* path_vert, const char* path_frag) override;// initialize 
};