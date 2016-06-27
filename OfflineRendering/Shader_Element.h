#pragma once
#include "GLFW_GLEW.h"
class Shader_Element {
	char* name;
	GLuint id;
public:
	enum GLSL_VARIABLE_TYPE { MAT4, VEC3, VEC4 };
	void init(char* name, GLSL_VARIABLE_TYPE type);
	Shader_Element link(GLuint program_Id);
	void assign(float *);
	void assign(int*);
};