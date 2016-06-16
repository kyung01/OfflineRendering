#pragma once
#include "Program_Default.h"
class Program_Shadow : public Program_Default {
	const char
		*NAME_TEXTURE_DEPTH = "depthMap",
		*NAME_MAT_LIGHT = "mat_light";
public:
	GLuint 
		id_texture_depth,
		id_mat_light;
	bool init(const char* path_vert, const char*path_frag) override;
};