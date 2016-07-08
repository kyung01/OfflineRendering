#pragma once
#include "GLFW_GLEW.h"
class Easy_GLSL {
public:
	static GLuint INIT_SHADER(char * data, int data_size, GLenum shaderType);
	enum GLSL_VARIABLE_TYPE { MAT4, VEC3, VEC4 };

};