#pragma once
#include "GLFW_GLEW.h"
#include "Easy_GLSL.h"
class Shader_Element {
	GLuint id;
	bool is_uniform;
	Easy_GLSL::GLSL_VARIABLE_TYPE type;
public:
	void init(GLuint program, char* name,bool is_uniform, Easy_GLSL::GLSL_VARIABLE_TYPE type);
	Shader_Element link(GLuint program_Id);
	void assign(float *);
	void assign(int*);
	GLuint get_id();
};