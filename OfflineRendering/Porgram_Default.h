#pragma once
#include <string>
#include <GL\glew.h>
class Program_Default {
	//will be the base program of all
	const char 
		* NAME_MATRIX_PROJ = "matrix_proj",
		* NAME_MATRIX_VIEWMODEL = "matrix_proj";

	GLint 
		id_program, id_shader_vert, id_shader_frag,
		id_mat_proj, id_mat_viewModel;

	int open_file(char* arr, int arr_size, const char* path); 
	
public:
	Program_Default();
	bool init(const char* path_vert, const char* path_frag);// initialize 
	std::string toString();
	void set_uniform_proj(float* mat);
	void set_uniform_viewmodel(float* mat);


};