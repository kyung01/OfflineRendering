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
	shader_vertex = glCreateShader(GL_VERTEX_SHADER);
	shader_frag = glCreateShader(GL_FRAGMENT_SHADER);
	hpr_txt_to_char(SHADER::FRAG_DEFAULT);
}
void OpenGL_ProjectManager::init()
{
	this->easyGLFW.createContext(GlobalVariables::CONTEXT_NAME, GlobalVariables::CONTEXT_WIDTH, GlobalVariables::CONTEXT_HEIGHT);
	this->stateRender = RENDER_OFFLINE;// first we will initiate to render in real time

	worldRender.init();
	init_fbo();
	init_shader();

	
	//glDrawBuffer(GL_NONE);
	//glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, texture_depth, 0);
	//glReadBuffer(GL_NONE);
	// check FBO status
}
void OpenGL_ProjectManager::render_texture(GLuint texture, int index)
{
	int 
		width = 200, height = 200, 
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
	glVertex2f(x + 200.0, y + 0.0f); //so that our texture has some points to draw to

	glTexCoord2d(1.0, 0.0);
	glVertex2f(x + 200.0, y + 200.0f);

	glTexCoord2d(0.0, 0.0);
	glVertex2f(x + 0.0, y + 200.0f);
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
const char* OpenGL_ProjectManager::hpr_txt_to_char(const char * path)
{
	ifstream fin(path);
	std::string content((std::istreambuf_iterator<char>(fin)), std::istreambuf_iterator<char>());
	const char *c(content.c_str());
	std::cout << "THUS " << c << endl;
	return c;
}
float movement = 0;
void OpenGL_ProjectManager::renderRealTimeBegin()
{
	movement += .01f;
	glClearColor(0.0f, 0.0f, .0f, 1.0f);
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
