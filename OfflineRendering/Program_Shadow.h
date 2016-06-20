#pragma once
#include "Program_View_Inversed.h"
class Program_Shadow : public Program_View_Inversed {
	const char
		*NAME_TEXTURE_DEPTH = "depthMap",
		*NAME_MAT_LIGHT = "mat_light";
public:
	GLuint 
		id_texture_depth,
		id_mat_light;
	bool init(const char* path_vert, const char*path_frag) override;
	void use(float* proj, float* modelView, float* view_inverted , float* mat_light_MVP, GLuint texture_depth);
	void unUse();
};