#include "Easy_OpenGL.h"

bool Easy_OpenGL::check_shader_compilation(GLuint shader_id)
{
	GLint isCompiled;
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled) {
		return true;	
	}
	std::cout << "GLSL_Easy::Shader is not compiled" << std::endl;
	
	char error[1000];
	//char * buffer = new char[1000];
	char buffer[1000];
	int errorSize, buffer_size;
	glGetShaderInfoLog(shader_id, 1000, &errorSize, error);
	std::cout << "GLSL_Easy::Shader is not compiled because... "<<error << std::endl;
	system("pause");
	return false;
}
