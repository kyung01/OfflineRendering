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

	worldRender.init();
	if (!program_default.init(PATH_SHADER_VERTEX_DEFAULT, PATH_SHADER_FRAG_DEFAULT))
		error("program_default failed to init.");
	if (!program_texture.init(PATH_SHADER_TEXTURE_VERT, PATH_SHADER_TEXTURE_FRAG))
		error("Program_texture failed to init.");
	if (!program_shadow.init(PATH_SHADER_SHADOW_VERT, PATH_SHADER_SHADOW_FRAG))
		error("program_shadow failed to init.");
	if (!fbo_light.init()) error("fbo_light failed to init.");
	fbo_light.init();
	fbo_light.set_colorbuffer(1024, 1024);
	fbo_light.set_depthbuffer(1024, 1024);
	glEnable(GL_DEPTH_TEST);
	//init_fbo();
	//init_shader();
	//init_program(program_00, shader_vertex, shader_frag);
	//glDrawBuffer(GL_NONE);
	//glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, texture_depth, 0);
	//glReadBuffer(GL_NONE);
	// check FBO status
}
void OpenGL_ProjectManager::render_texture(GLuint id_modelview, GLuint id_vert, GLuint id_vert_texture, GLuint id_texture_loc, GLuint id_texture, int index)
{
	int
		width = 150, height = 150,
		x = width *index, y = 0;
	glm::mat4 modelView;
	glUniformMatrix4fv(id_modelview, 1, false, glm::value_ptr(modelView));
	glActiveTexture(GL_TEXTURE0 ); // Texture unit 0
	glBindTexture(GL_TEXTURE_2D, id_texture);
	glUniform1i(id_texture_loc, 0);

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
	glBindTexture(GL_TEXTURE_2D, 0);
	/*
	bool is_enabled_texture = glIsEnabled(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_2D);


	glBindTexture(GL_TEXTURE_2D, texture);
	//glClearColor(0.0f, 1.0f, 0.0f, 1.0f); // Set background color to black and opaque
	//glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glFrustum(-1, 1, -1, 1, 1.0f, 100);
	//gluOrtho2D(0, 640, 0, 480);
	gluOrtho2D(0, GlobalVariables::CONTEXT_WIDTH,GlobalVariables::CONTEXT_HEIGHT, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();



	glBegin(GL_QUADS); //begin drawing our quads
	glColor3f(1, 1, 1);
	glTexCoord2d(0.0, 1.0);
	glVertex2f(x+0.0,y+ 0.0); //with our vertices we have to assign a texcoord

	glTexCoord2d(1.0, 1.0);
	glVertex2f(x + width, y + 0.0f); //so that our texture has some points to draw to

	glTexCoord2d(1.0, 0.0);
	glVertex2f(x + width, y + height);

	glTexCoord2d(0.0, 0.0);
	glVertex2f(x + 0.0, y + height);
	glEnd();	
	

	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);

	if (is_enabled_texture) glEnable(GL_TEXTURE_2D);
	else glDisable(GL_TEXTURE_2D);
	*/
}
void OpenGL_ProjectManager::hpr_basisc_glTexParameteri()
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}


void OpenGL_ProjectManager::error(const char * error_message)
{
	cout << "OpenGL_ProjectManager::error::" << error_message << endl;
	system("pause");
	exit(-1);
}

void OpenGL_ProjectManager::glm_mat_array(float * arr, glm::mat4 * mat)
{
	const float *pSource = (const float*)glm::value_ptr(*mat);
	for (int i = 0; i < 16; i++) {
		arr[i] = pSource[i];
	}
}
void OpenGL_ProjectManager::renderRealTimeBegin()
{
	movement += .02f;
	float arr_mat[16];
	glm::mat4 mat_ortho = glm::ortho<float>(0, GlobalVariables::CONTEXT_WIDTH, GlobalVariables::CONTEXT_HEIGHT, 0);
	//glm::mat4 mat_ortho_light = glm::ortho<float>(0, 1024, 1024, 0);
	glm::mat4 mat_me_proj			= glm::perspective<float>(2.0f, (float)GlobalVariables::CONTEXT_WIDTH / GlobalVariables::CONTEXT_HEIGHT, 0.1f, 2000.f);
	glm::mat4 mat_me_viewModel		= glm::lookAt(glm::vec3(2.f, 1.8f, 2.f), glm::vec3(1.5f,.5f, 0), glm::vec3(0, 1, 0));
	glm::mat4 mat_me_view_inversed = glm::inverse(mat_me_viewModel);
	glm::vec3	
		lightPos = glm::vec3(1.5f , .5f, 1.5),
		lightCenter = glm::vec3(lightPos.x, 0,0) + glm::vec3(cos(movement), 0, 0)* 1.25f;

	glm::mat4 mat_light_proj = glm::ortho<float>(-3, 3, -3, 3, -3, 5);
	glm::mat4 mat_light_modelView	= glm::lookAt (
		lightPos,
		lightCenter,
		glm::vec3(0, 1, 0));
	glm::mat4 mat_light = mat_light_proj * mat_light_modelView;
	glm::mat4 biasMatrix(
		0.5, 0.0, 0.0, 0.0,
		0.0, 0.5, 0.0, 0.0,
		0.0, 0.0, 0.5, 0.0,
		0.5, 0.5, 0.5, 1.0
		);
	mat_light = biasMatrix * mat_light_proj * mat_light_modelView;



	//mat_proj = glm::ortho<float>(0, GlobalVariables::CONTEXT_WIDTH, GlobalVariables::CONTEXT_HEIGHT, 0);
	//mat_proj = glm::perspective<float>(2.0f, (float)GlobalVariables::CONTEXT_WIDTH / GlobalVariables::CONTEXT_HEIGHT, 0.1f, 2000.f);
	//mat_proj = glm::ortho(0, 1,1, 0);
	//mat_view = glm::lookAt(glm::vec3(0.f, 0.f, 1.0f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.0f, 1.0f, 0.0f));
	/*

	glUseProgram(program_default.id_program);
	glClearColor(0.01f, .02f, .03f, 1.0f);
	glViewport(0, 0, GlobalVariables::CONTEXT_WIDTH, GlobalVariables::CONTEXT_HEIGHT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUniformMatrix4fv(program_default.id_mat_proj, 1, GL_FALSE, (float*)glm::value_ptr(mat_proj));
	glUniformMatrix4fv(program_default.id_mat_viewModel, 1, GL_FALSE, (float*)glm::value_ptr(mat_view));
	glBegin(GL_TRIANGLES);

	glVertexAttrib3f(program_default.id_pos, 0, 0, 0);
	glVertexAttrib3f(program_default.id_pos, 100, 0, 0);
	glVertexAttrib3f(program_default.id_pos, 100, 100, 0);

	glEnd();
	glUseProgram(0);
	glfwSwapBuffers(this->easyGLFW.window);
	return;
	*/
	/*
	*/
	glUseProgram(program_shadow.id_program);
	glClearColor(0.01f, .01f, .01f, 1.0f);
	glViewport(0, 0, GlobalVariables::CONTEXT_WIDTH, GlobalVariables::CONTEXT_HEIGHT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUniformMatrix4fv(program_shadow.id_mat_proj, 1, GL_FALSE, (float*)glm::value_ptr(mat_me_proj));
	glUniformMatrix4fv(program_shadow.id_mat_viewModel, 1, GL_FALSE, (float*)glm::value_ptr(mat_me_viewModel));
	glUniformMatrix4fv(program_shadow.id_mat_view_inversed, 1, GL_FALSE, (float*)glm::value_ptr(mat_me_view_inversed));
	glUniformMatrix4fv(program_shadow.id_mat_light, 1, GL_FALSE, (float*)glm::value_ptr(mat_light));
	glUniform1i(program_shadow.id_texture_depth, 0);
	glActiveTexture(GL_TEXTURE0); // Texture unit 0
	glBindTexture(GL_TEXTURE_2D, fbo_light.id_texture_depth);
	worldRender.draw(&mat_me_viewModel, program_shadow.id_mat_viewModel, program_shadow.id_pos, -1	);
	glUseProgram(0);
	glBindTexture(GL_TEXTURE_2D, 0);	


	//return statement to test out if I can draw 2d with this shader
	//render light scene
	glUseProgram(program_default.id_program);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo_light.id_fbo);
	 
	glClearColor(0.1f, .1f, 0.1f, 1.0f)	;
	glViewport(0, 0, 1024,1024);
	//glViewport(0, 0, GlobalVariables::CONTEXT_WIDTH, GlobalVariables::CONTEXT_HEIGHT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUniformMatrix4fv(program_default.id_mat_proj, 1, GL_FALSE, (float*)glm::value_ptr(mat_light_proj));
	glUniformMatrix4fv(program_default.id_mat_viewModel, 1, GL_FALSE, (float*)glm::value_ptr(mat_light_modelView));
	worldRender.draw(&mat_light_modelView, program_default.id_mat_viewModel, program_default.id_pos, -1);
	glUseProgram(0);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glUseProgram(this->program_texture.id_program);
	glViewport(0, 0, GlobalVariables::CONTEXT_WIDTH, GlobalVariables::CONTEXT_HEIGHT);
	glUniformMatrix4fv(program_default.id_mat_proj, 1, GL_FALSE, (float*)glm::value_ptr(mat_ortho));
	render_texture(program_texture.id_mat_viewModel, program_texture.id_pos, program_texture.id_pos_texture, program_texture.id_texture_00, fbo_light.id_texture_color, 0);
	render_texture(program_texture.id_mat_viewModel, program_texture.id_pos, program_texture.id_pos_texture, program_texture.id_texture_00, fbo_light.id_texture_depth, 1);
	glUseProgram(0);





	glfwSwapBuffers(this->easyGLFW.window);




	//glm_mat_array(arr_mat, &mat_proj);
	//glm_mat_array(arr_mat, &mat_view);
	//cout << program00.id_mat_proj << " " << program00.id_mat_viewModel << endl;
	//0, .4f, .7f + movement, 0, 0, 0, 0, 1, 0
	//set the projection matrix
	//pass the projection matrix
	//get the view matrix
	//pass the view matrix
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
