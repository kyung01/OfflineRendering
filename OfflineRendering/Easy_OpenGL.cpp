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

Easy_OpenGL::GlCharArr Easy_OpenGL::TO_GLCHARR_ARR(char * arr, int size)
{
	bool IS_PRINT_READING = false;
	bool IS_PRINT_RESULT = false;
	const int SIZE = 5000;
	GLchar gl_arr[SIZE];
	GLchar *pointer_gl_arr = gl_arr;
	if (IS_PRINT_READING)std::cout << "Easy_OpenGL::TO_GLCHARR_ARR..." << std::endl;
	for (int i = 0; i < size; i++) {
		gl_arr[i] = arr[i];
		if (IS_PRINT_READING)std::cout << arr[i];
	}
	if (IS_PRINT_READING)std::cout <<std::endl<< "...Easy_OpenGL::TO_GLCHARR_ARR" << std::endl;
	gl_arr[size - 1] = '\0';

	if (IS_PRINT_RESULT) {
		std::cout << "Easy_OpenGL::TO_GLCHARR_ARR IS_PRINT_RESULT..." << std::endl;
		for (int i = 0; i < size; i++) {
			std::cout << gl_arr[i];
		}
		std::cout <<"...ENDL"<< std::endl;
	}
	return Easy_OpenGL::GlCharArr { gl_arr , size };
}
