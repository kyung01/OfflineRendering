#pragma once
#include "Program_Default.h"
class Program_Shadow : public Program_Default {
	const char
		*NAME_TEXTURE_DEPTH = "depthMap",
		*NAME_MAT_LIGHT = "mat_light",
		*NAME_MAT_VIEW_INVERSED = "mat_view_inversed";
public:
	GLuint 
		id_texture_depth,
		id_mat_light,id_mat_view_inversed;
	bool init(const char* path_vert, const char*path_frag) override;
};