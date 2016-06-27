#include "Program_Default.h"
#include "EASY_STD.h"
#include "Easy_OpenGL.h"

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
bool Program_Default::init_shader(char* path_vert, char* path_frag)
{
	Easy_STD::File file_vert = Easy_STD::READ_FILE((char*)path_vert);
	Easy_STD::File  file_frag = Easy_STD::READ_FILE((char*)path_frag);
	
	if (!init_shader(&id_shader_vert, GL_VERTEX_SHADER, file_vert.array.get(), file_vert.array_used_size)) {
		std::cout << "Program_Default::FAILED TO INITIALIZE VERTEX SHADER" << std::endl;
		return false;
	}
	if (!init_shader(&id_shader_frag, GL_FRAGMENT_SHADER, file_frag.array.get(), file_frag.array_used_size)) {
		std::cout << "Program_Default::FAILED TO INITIALIZE FRAGEMNT SHADER" << std::endl;
		return false;
	}
}

bool Program_Default::init_shader(GLuint * shader_id, GLenum shaderType, char * data, int data_size)
{
	auto glChar = Easy_OpenGL::TO_GLCHARR_ARR(data, data_size);
	*shader_id = glCreateShader(shaderType);
	glShaderSource(*shader_id, 1, &glChar.arr, &glChar.size);
	glCompileShader(*shader_id);
	return Easy_OpenGL::check_shader_compilation(*shader_id);
}
void Program_Default::init_uniformLocs()
{
	id_mat_proj = glGetUniformLocation(id_program, NAME_MATRIX_PROJ);
	id_mat_viewModel = glGetUniformLocation(id_program, NAME_MATRIX_VIEWMODEL);
	id_pos = glGetAttribLocation(id_program, NAME_POSITION);
	mat_proj.init("mat_proj", Shader_Element::GLSL_VARIABLE_TYPE::MAT4);
	mat_viewModel.init("mat_viewModel", Shader_Element::GLSL_VARIABLE_TYPE::MAT4);
	vert_pos.init("vert_pos", Shader_Element::GLSL_VARIABLE_TYPE::VEC3);
}
bool Program_Default::init_old(const char * path_vert, const char * path_frag)
{
	if (!init_shader((char*)path_vert, (char*)path_frag))return false;

	
	//creating shader is now completed, let's now create program
	id_program = glCreateProgram();
	glAttachShader(id_program, id_shader_vert);
	glAttachShader(id_program, id_shader_frag);
	glLinkProgram(id_program);
	GLint linked;
	glGetProgramiv(id_program, GL_LINK_STATUS, &linked);
	std::cout << "CHECKING linked status... " << linked << std::endl;
	if (!linked) return false;


	
	init_uniformLocs();
	return true;
}

bool Program_Default::init(const char * path_vert, const char * path_frag)
{
	return false;
}

void Program_Default::use(float * mat_proj, float * mat_viewModel)
{
	glUseProgram(id_program);
	glUniformMatrix4fv(id_mat_proj, 1, GL_FALSE, mat_proj);
	glUniformMatrix4fv(id_mat_viewModel, 1, GL_FALSE, mat_viewModel);
}

void Program_Default::unUse()
{
	glUseProgram(0);
}
