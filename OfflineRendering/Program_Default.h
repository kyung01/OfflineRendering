#pragma once
#include <iostream>
#include <string>
#include <map>
#include "GL\glew.h"
#include "Easy_OpenGL.h"
#include "Shader_Element.h"

class Program_Default {
	enum SHADER_UNIFORM_TYPE {MATRIX, VEC3, VEC4 };
	std::map<char*, SHADER_UNIFORM_TYPE> mapShaderIds_initialize;
	//will be the base program of all
	const char
		*NAME_MATRIX_PROJ = "mat_proj",
		*NAME_MATRIX_VIEWMODEL = "mat_viewModel",
		*NAME_POSITION = "pos";





	//int open_file(char* arr, int arr_size, const char* path); 
	bool is_shader_compiled(GLuint shader_id);
	bool init_shader(char* path_vert, char* path_frag);
	bool init_shader(GLuint * shader_id, GLenum shaderType, char * data, int data_size);
protected :
	virtual void init_shader_locations();
public:
	Shader_Element
		mat_proj,
		mat_viewModel,
		vert_pos, vert_texture_pos;

	GLuint
		id_program, id_shader_vert, id_shader_frag,
		id_mat_proj, id_mat_viewModel,
		id_pos;

	Program_Default();
	bool init(const char* path_vert, const char* path_frag);
	void use(float* mat_proj, float* mat_viewModel);
	void unUse();
	std::string toString();


};