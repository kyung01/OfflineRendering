#pragma once
#include <iostream>
#include <string>
#include "GL\glew.h"
#include "Easy_OpenGL.h"
class Program_Default {
	//will be the base program of all
	const char 
		* NAME_MATRIX_PROJ = "mat_proj",
		* NAME_MATRIX_VIEWMODEL = "mat_viewModel",
		* NAME_POSITION = "pos",
		* NAME_POSITION_TEXTURE = "pos_texture";



	int open_file(char* arr, int arr_size, const char* path); 
	bool is_shader_compiled(GLuint shader_id);
	bool init_shader(GLuint * shader_id, GLenum shaderType, char * data, int data_size);
public:
	GLuint
		id_program, id_shader_vert, id_shader_frag,
		id_mat_proj, id_mat_viewModel,
		id_pos,id_pos_texture;

	Program_Default();
	bool init(const char* path_vert, const char* path_frag);// initialize 
	std::string toString();


};