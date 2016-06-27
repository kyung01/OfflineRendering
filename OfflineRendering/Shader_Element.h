#pragma once
#include "GLFW_GLEW.h"
class Shader_Element {
	enum GLSL_VARIABLE_TYPE {MAT4, VEC3, VEC4};
	char* name;
	GLuint id;
public:
	Shader_Element(char* name, GLSL_VARIABLE_TYPE type);
	Shader_Element link(GLuint program_Id);
	void assign(float *);
	void assign(int*);
};