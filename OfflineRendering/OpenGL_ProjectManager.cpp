#include <string>
#include <iostream>
#include <fstream>
#include "OpenGL_ProjectManager.h"
#include "GlobalVariables.h"
#include "ShaderPath.h"

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
	char * buffer = new char[1000];
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
void OpenGL_ProjectManager::init()
{
	this->easyGLFW.createContext(GlobalVariables::CONTEXT_NAME, GlobalVariables::CONTEXT_WIDTH, GlobalVariables::CONTEXT_HEIGHT);
	this->stateRender = RENDER_OFFLINE;// first we will initiate to render in real time

	worldRender.init();
	init_fbo();
	init_shader();
	init_program(program_00, shader_vertex, shader_frag);

	
	//glDrawBuffer(GL_NONE);
	//glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, texture_depth, 0);
	//glReadBuffer(GL_NONE);
	// check FBO status
}
void OpenGL_ProjectManager::render_texture(GLuint texture, int index)
{
	int 
		width = 100, height = 100, 
		x = width *index, y = 0;
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
}
void OpenGL_ProjectManager::hpr_basisc_glTexParameteri()
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
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
	*/
}
bool OpenGL_ProjectManager::hpr_is_shader_compiled(GLint shaderID)
{
	GLint isCompiled;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &isCompiled);
	if (!isCompiled)
		return false;
	return true;
}
float movement = 0;
void OpenGL_ProjectManager::renderRealTimeBegin()
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
	glUseProgram(program_00);
	render_texture(texture_depth, 1);
	glUseProgram(0);

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
