#include "Program_Default.h"
#include <fstream>
int Program_Default::open_file(char * arr, int arr_size, const char * path)
{
	int n = 0;
	std::ifstream fin(path, std::ios::in);
	if (!fin.good()) {
		std::cout << "NOT GOOD" << std::endl;
		system("pause");
	}
	while (!fin.eof() && n < arr_size ) {
		fin.get(arr[n++]);
	}

	return n;
}

bool Program_Default::is_shader_compiled(GLuint shader_id)
{
	GLint isCompiled;
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled) return true;
	return false;
}

Program_Default::Program_Default()
{
}
bool Program_Default::init_shader(GLuint * shader_id, GLenum shaderType, char * data, int data_size)
{
	GLchar gl_arr[1000];
	GLchar *pointer_gl_arr = gl_arr;
	GLint gl_data_size = data_size;
	for (int i = 0; i < data_size; i++) {
		gl_arr[i] = data[i];
	}
	gl_arr[data_size-1] = '\0';

	bool setting_prinnt_data = false;
	if (setting_prinnt_data) {
		std::cout << "____________________________________________________________init_Shader " << data_size << std::endl;
		for (int i = 0; i < data_size; i++) {
			std::cout << gl_arr[i];
		}
		std::cout << std::endl;
	} 
		
	*shader_id = glCreateShader(shaderType);
	glShaderSource(*shader_id, 1, &pointer_gl_arr, &gl_data_size);
	glCompileShader(*shader_id);
	return Easy_OpenGL::check_shader_compilation(*shader_id);
}
bool Program_Default::init(const char * path_vert, const char * path_frag)
{
	const int ARR_SIZE = 1000;
	int source_length;
	char arr[ARR_SIZE];
	char *arr_pointer = &arr[0];
	bool is_shader_compiled00, is_shader_compiled01;
	source_length= open_file(arr, ARR_SIZE, path_vert);
	if (!init_shader(&id_shader_vert, GL_VERTEX_SHADER, arr_pointer, source_length)) return false;
	source_length = open_file(arr, ARR_SIZE, path_frag);
	if (!init_shader(&id_shader_frag, GL_FRAGMENT_SHADER, arr_pointer, source_length)) return false;


	
	//creating shader is now completed, let's now create program
	id_program = glCreateProgram();
	glAttachShader(id_program, id_shader_vert);
	glAttachShader(id_program, id_shader_frag);
	glLinkProgram(id_program);
	GLint linked;
	glGetProgramiv(id_program, GL_LINK_STATUS, &linked);
	std::cout << "CHECKING id_program" << std::endl;
	if (!linked) return false;

	id_mat_proj =		glGetUniformLocation(id_program, NAME_MATRIX_PROJ);
	id_mat_viewModel =	glGetUniformLocation(id_program, NAME_MATRIX_VIEWMODEL);
	id_pos =			glGetAttribLocation(id_program, NAME_POSITION);
	

	return true;
}
