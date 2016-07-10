#include "Shader_Element.h"





void Shader_Element::init(GLuint program, char * name, bool is_uniform, Easy_GLSL::GLSL_VARIABLE_TYPE type)
{
	this->id = (is_uniform) ? glGetUniformLocation(program, name) : glGetAttribLocation(program,name);
	this->type = type;
	this->is_uniform = is_uniform;
}

Shader_Element Shader_Element::link(GLuint program_Id)
{
	return Shader_Element();
}

void Shader_Element::assign(float * value)
{
	

	switch (type) {
	case Easy_GLSL::GLSL_VARIABLE_TYPE::MAT4:
		if (this->is_uniform) glUniformMatrix4fv(this->id, 1, GL_FALSE, value);
		break;
	case Easy_GLSL::GLSL_VARIABLE_TYPE::VEC3:
		if (this->is_uniform) glUniform3f(this->id, value[0], value[1], value[2]);
		else glVertexAttrib3f(this->id, value[0], value[1], value[2]);
		break;
	case Easy_GLSL::GLSL_VARIABLE_TYPE::VEC4:
		if (this->is_uniform) glUniform4f(this->id, value[0], value[1], value[2], value[3]);
		else glVertexAttrib4f(this->id, value[0], value[1], value[2], value[3]);
		break;
	}
}

GLuint Shader_Element::get_id()
{
	return id;
}
