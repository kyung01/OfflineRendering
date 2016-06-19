#include <string>
#include <iostream>
#include <fstream>
#include "OpenGL_ProjectManager.h"
#include "GlobalVariables.h"
#include "ShaderPath.h"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"


float movement = 0;

void OpenGL_ProjectManager::init()
{
	this->easyGLFW.createContext(GlobalVariables::CONTEXT_NAME, GlobalVariables::CONTEXT_WIDTH, GlobalVariables::CONTEXT_HEIGHT);
	this->stateRender = RENDER_OFFLINE;// first we will initiate to render in real time

	glEnable(GL_DEPTH_TEST);
	glClearColor(0, 0, 0, 1);

	worldRender.init();
	if (!program_default.init(PATH_SHADER_VERTEX_DEFAULT, PATH_SHADER_FRAG_DEFAULT))
		error("program_default failed to init.");
	if (!program_texture.init(PATH_SHADER_TEXTURE_VERT, PATH_SHADER_TEXTURE_FRAG))
		error("Program_texture failed to init.");
	if (!program_shadow.init(PATH_SHADER_SHADOW_VERT, PATH_SHADER_SHADOW_FRAG))
		error("program_shadow failed to init.");
	if (!program_normal.init(PATH_SHADER_NORMAL_VERT, PATH_SHADER_NORMAL_FRAG))
		error("program_normal failed to init.");
	if (!program_worldsapce.init(PATH_SHADER_WORLDSPACE_VERT, PATH_SHADER_WORLDSPACE_FRAG))
		error("program_worldsapce failed to init.");
	if (!fbo_light.init()) error("fbo_light failed to init.");
	fbo_light.init();
	fbo_normal.init();
	fbo_worldSpace.init();
	//fbo_light.set_colorbuffer(1024, 1024);
	fbo_light.set_depthbuffer(1024, 1024);
	fbo_normal.set_colorbuffer(1024, 1024);
	fbo_normal.set_depthbuffer(1024, 1024);
	fbo_worldSpace.set_colorbuffer(1024, 1024);
	fbo_worldSpace.set_depthbuffer(1024, 1024);

	biasMatrix = glm::mat4(
		0.5, 0.0, 0.0, 0.0,
		0.0, 0.5, 0.0, 0.0,
		0.0, 0.0, 0.5, 0.0,
		0.5, 0.5, 0.5, 1.0
		);
	mat_proj_firstPerson = glm::perspective<float>(2.0f, (float)GlobalVariables::CONTEXT_WIDTH / GlobalVariables::CONTEXT_HEIGHT, 0.1f, 2000.f);
	mat_proj_ortho = glm::ortho<float>(-3, 3, -3, 3, -3, 5);
	mat_proj_ortho_screen = glm::ortho<float>(0, GlobalVariables::CONTEXT_WIDTH, GlobalVariables::CONTEXT_HEIGHT, 0);
	//mat_ = glm::ortho<float>(0, 1024, 1024, 0);
	mat_me_modelView = glm::lookAt(glm::vec3(2.f, 1.8f, 2.f), glm::vec3(1.5f, .5f, 0), glm::vec3(0, 1, 0));
	mat_me_view_inversed = glm::inverse(mat_me_modelView);
	glm::vec3
		lightPos = glm::vec3(1.5f, .5f, 1.5),
		lightCenter = glm::vec3(lightPos.x, 0, 0) + glm::vec3(cos(movement), 0, 0)* 1.25f;

	//mat_light_proj = glm::ortho<float>(-3, 3, -3, 3, -3, 5);
	mat_light_modelView = glm::lookAt(
		lightPos,
		lightCenter,
		glm::vec3(0, 1, 0));
	
	mat_light_MVP = biasMatrix * mat_proj_ortho * mat_light_modelView;

}
void OpenGL_ProjectManager::render_texture(GLuint id_vert, GLuint id_vert_texture, GLuint id_texture, int index)
{
	int
		width = 350, height = 350,
		x = width *index, y = 0;
	glBindTexture(GL_TEXTURE_2D, id_texture);

	glBegin(GL_QUADS);

	glVertexAttrib2f(id_vert_texture, 0.0, 1.0);
	glVertexAttrib3f(id_vert, x + 0.0, y + 0.0, 0);

	glVertexAttrib2f(id_vert_texture, 1.0, 1.0);
	glVertexAttrib3f(id_vert, x + width, y + 0.0f, 0);

	glVertexAttrib2f(id_vert_texture, 1.0, 0.0);
	glVertexAttrib3f(id_vert, x + width, y + height, 0);

	glVertexAttrib2f(id_vert_texture, 0.0, 0.0);
	glVertexAttrib3f(id_vert, x + 0.0, y + height, 0);

	glEnd();
}


void OpenGL_ProjectManager::error(const char * error_message)
{
	cout << "OpenGL_ProjectManager::error::" << error_message << endl;
	system("pause");
	exit(-1);
}

void OpenGL_ProjectManager::set_FBO(KFrameBufferObject * buffer)
{
	if (buffer == NULL) {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, GlobalVariables::CONTEXT_WIDTH, GlobalVariables::CONTEXT_HEIGHT);
		return;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, buffer->id_fbo);
	glViewport(0, 0, buffer->viewport_width() , buffer->viewport_height() );
}

void OpenGL_ProjectManager::renderRealTimeBegin()
{
	movement += .02f;
	glm::vec3
		lightPos = glm::vec3(1.5f, .5f, 1.5),
		lightCenter = glm::vec3(lightPos.x, 0, 0) + glm::vec3(cos(movement), 0, 0)* 1.25f;

	//mat_light_proj = glm::ortho<float>(-3, 3, -3, 3, -3, 5);
	mat_light_modelView = glm::lookAt(
		lightPos,
		lightCenter,
		glm::vec3(0, 1, 0));
	mat_light_view_inverted = glm::inverse(mat_light_modelView);
	mat_light_MVP = biasMatrix * mat_proj_ortho * mat_light_modelView;


	set_FBO(&fbo_light);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	program_default.use(glm::value_ptr(mat_proj_ortho), glm::value_ptr(mat_light_modelView));
	worldRender.draw(&mat_light_modelView, program_default.id_mat_viewModel, program_default.id_pos, 0);
	program_default.unUse();

	set_FBO(&fbo_worldSpace);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	program_worldsapce.use(glm::value_ptr(mat_proj_ortho), glm::value_ptr(mat_light_modelView), glm::value_ptr(mat_light_view_inverted));
	worldRender.draw(&mat_light_modelView, program_worldsapce.id_mat_viewModel, program_worldsapce.id_pos, 0);
	program_worldsapce.unUse();

	set_FBO(&fbo_normal);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	program_normal.use(glm::value_ptr(mat_proj_ortho), glm::value_ptr(mat_light_modelView), glm::value_ptr(mat_light_view_inverted));
	worldRender.draw(&mat_light_modelView, program_normal.id_mat_viewModel, program_normal.id_pos, 0);
	program_normal.unUse();

	
	set_FBO(NULL);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	program_shadow.use(
		glm::value_ptr(mat_proj_firstPerson),
		glm::value_ptr(mat_me_modelView),
		glm::value_ptr(mat_me_view_inversed),
		glm::value_ptr(mat_light_MVP),
		fbo_light.id_texture_depth);
	worldRender.draw(&mat_me_modelView, program_shadow.id_mat_viewModel, program_shadow.id_pos, -1);
	program_shadow.unUse();
	

	set_FBO(NULL);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	program_normal.use(glm::value_ptr(mat_proj_ortho), glm::value_ptr(mat_light_modelView), glm::value_ptr(mat_light_view_inverted));
	worldRender.draw(&mat_light_modelView, program_normal.id_mat_viewModel, program_normal.id_pos, 0);
	program_normal.unUse();
	

	glm::mat4 m;
	set_FBO(NULL);
	program_texture.use(glm::value_ptr(mat_proj_ortho_screen), glm::value_ptr(m), fbo_light.id_texture_color);
	render_texture(program_texture.id_pos, program_texture.id_pos_texture, fbo_worldSpace.id_texture_color, 0);
	render_texture(program_texture.id_pos, program_texture.id_pos_texture, fbo_light.id_texture_depth, 1);
	render_texture(program_texture.id_pos, program_texture.id_pos_texture, fbo_normal.id_texture_color, 2);
	program_texture.unUse();

	glfwSwapBuffers(this->easyGLFW.window);
}




void OpenGL_ProjectManager::renderOfflineBegin()
{
	renderRealTimeBegin();
}
void OpenGL_ProjectManager::renderRealTimeEnd()
{
	glfwPollEvents();
}
void OpenGL_ProjectManager::renderOfflineEnd()
{
	renderRealTimeEnd();
}

void OpenGL_ProjectManager::end()
{
	if (easyGLFW.window) {
		glfwDestroyWindow(easyGLFW.window);
	}
}
/*
bool OpenGL_ProjectManager::hpr_is_shader_compiled(GLint shaderID)
{
GLint isCompiled;
glGetShaderiv(shaderID, GL_COMPILE_STATUS, &isCompiled);
if (!isCompiled)
return false;
return true;
}

int OpenGL_ProjectManager::hpr_txt_to_char(char* buffer, int buffer_size, const char * path)
{
int n = 0;
ifstream fin(path, ios::in);
while (!fin.eof() &&n < buffer_size && fin.good() ) {
//fin.get(data_gl[n++]);
fin.get(buffer[n++]);
//cout << data[n - 1];
}
//data[n] = NULL;
//cout << "[ENDL]"<<endl;
return n;
/*
std::string content((std::istreambuf_iterator<char>(fin)), std::istreambuf_iterator<char>());
string content2 = content;
//std::string content((std::istreambuf_iterator<char>(fin)), std::istreambuf_iterator<char>());
const char *c(content2.c_str());

int n = strlen(c);
//char c_copy[n];
for (int i = 0; i < n; i++) {
cout << "[" << c[i] << "]";
//c_copy[i] = c[i];
}
cout << endl;
//fin.close();
//std::cout << "THUS " << c << endl;

}

bool OpenGL_ProjectManager::init_shader(GLuint * shader_id, GLenum shaderType,  char * data, int data_size)
{

cout << "READING..." << endl;
for (int i = 0; i < data_size; i++) {
cout << data[i];
}
cout << endl;
cout << "OpenGL_ProjectManager::init_shader::data_size" << data_size << endl;

*shader_id = glCreateShader(shaderType);
glShaderSource(*shader_id, 1, &data, &data_size);
glCompileShader(*shader_id);
GLint isCompiled;
glGetShaderiv(*shader_id, GL_COMPILE_STATUS, &isCompiled);
if (isCompiled) return true;
return false;
}

void OpenGL_ProjectManager::init_fbo()
{
glGenTextures(1, &texture_depth);
glBindTexture(GL_TEXTURE_2D, texture_depth);
glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, 1024, 1024, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, 0);
hpr_basisc_glTexParameteri();
glGenTextures(1, &texture_color);
glBindTexture(GL_TEXTURE_2D, texture_color);
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1024, 1024, 0, GL_RGBA, GL_FLOAT, 0);
hpr_basisc_glTexParameteri();

glBindTexture(GL_TEXTURE_2D, 0);

glGenFramebuffers(1, &fbo_depth);
glBindFramebuffer(GL_FRAMEBUFFER, fbo_depth);
glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, texture_depth, 0);
glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture_color, 0);
GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
if (status != GL_FRAMEBUFFER_COMPLETE)
cout << "FBO NO OK!!" << endl << endl;
else cout << "FBO IS OK!!" << endl;

glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
void OpenGL_ProjectManager::init_shader()
{
cout << "OpenGL_ProjectManager::init_shader" << endl;
char error[1000];
//char * buffer = new char[1000];
char buffer[1000];
int errorSize, buffer_size;
buffer_size = hpr_txt_to_char(buffer, 1000, SHADER::VERTEX_DEFAULT);
if (init_shader(&shader_vertex, GL_VERTEX_SHADER,buffer,buffer_size))
cout << "OpenGL_ProjectManager::init_shader::VERTEX_SHADER::YES" << endl;
else {
cout << "OpenGL_ProjectManager::init_shader::VERTEX_SHADER::NO" << endl;
glGetShaderInfoLog(shader_vertex, 1000, &errorSize, error);
cout << error<<endl;
}
buffer_size = hpr_txt_to_char(buffer, 1000, SHADER::FRAG_DEFAULT);
if (init_shader(&shader_frag, GL_FRAGMENT_SHADER, buffer,buffer_size) )
cout << "OpenGL_ProjectManager::init_shader::FRAG_SHADER::YES" << endl;
else {
cout << "OpenGL_ProjectManager::init_shader::FRAG_SHADER::NO" << endl;
glGetShaderInfoLog(shader_frag, 1000, &errorSize, error);
cout << error << endl;
}



}
void OpenGL_ProjectManager::init_program(GLuint & program_id, GLuint shader_vertex, GLuint shader_frag)
{
program_id = glCreateProgram();
glAttachShader(program_id, shader_vertex);
glAttachShader(program_id, shader_frag);
glLinkProgram(program_id);

GLint linked;
glGetProgramiv(program_id, GL_LINK_STATUS, &linked);
cout << "OpenGL_ProjectManager::init_program::";
if (linked) cout << "YES" << endl;
else cout << "NO" << endl;
}
void OpenGL_ProjectManager::renderRealTimeBegin_old()
{
movement += .01f;
glClearColor(0.0f, 0.0f, .1f, 1.0f);
glViewport(0, 0, GlobalVariables::CONTEXT_WIDTH, GlobalVariables::CONTEXT_HEIGHT);
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluPerspective(60, (float)GlobalVariables::CONTEXT_WIDTH / GlobalVariables::CONTEXT_HEIGHT, 0.1f, 2000.f);
//glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0f, 102.0);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
gluLookAt(0,.4f, .7f + movement,	0,0,0,	0,1,0);
worldRender.draw_scene_bunnies();

glBindFramebuffer(GL_FRAMEBUFFER, fbo_depth);
glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
glViewport(0, 0,1024, 1024);
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluPerspective(60, (float)GlobalVariables::CONTEXT_WIDTH / GlobalVariables::CONTEXT_HEIGHT, 0.1f, 2000.f);
//glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0f, 102.0);
//gluOrtho2D(0, GlobalVariables::CONTEXT_WIDTH, GlobalVariables::CONTEXT_HEIGHT, 0);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
gluLookAt(0, .4f, .7f + movement, 0, 0, 0, 0, 1, 0);
worldRender.draw_scene_bunnies();
glBindFramebuffer(GL_FRAMEBUFFER, 0);
glViewport(0, 0, GlobalVariables::CONTEXT_WIDTH, GlobalVariables::CONTEXT_HEIGHT);


render_texture(texture_color, 0);
render_texture(texture_depth, 1);
glUseProgram(program_00);
render_texture(texture_depth, 2);
glUseProgram(0);

glfwSwapBuffers(this->easyGLFW.window);

}
*/
