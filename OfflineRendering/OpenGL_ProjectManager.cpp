#include "OpenGL_ProjectManager.h"
#include "GlobalVariables.h"
void OpenGL_ProjectManager::initWorld()
{
	worldRender.init();
	//crate world
	//give the world to the world renderer
}
void OpenGL_ProjectManager::init()
{
	this->easyGLFW.createContext(GlobalVariables::CONTEXT_NAME, GlobalVariables::CONTEXT_WIDTH, GlobalVariables::CONTEXT_HEIGHT);
	this->stateRender = RENDER_OFFLINE;// first we will initiate to render in real time
	initWorld();
	return;
	/*
	glGenTextures(1, &texture_depth);
	glBindTexture(GL_TEXTURE_2D, texture_depth);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, 1024, 1024, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);
	*/
}

void OpenGL_ProjectManager::render_texture(GLuint texture, int index)
{
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
	glTexCoord2d(0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0); //with our vertices we have to assign a texcoord

	glTexCoord2d(1.0, 0.0);
	glVertex3f(100.0, 0.0, 0.0); //so that our texture has some points to draw to

	glTexCoord2d(1.0, 1.0);
	glVertex3f(100.0, 100.0, 0.0);

	glTexCoord2d(0.0, 1.0);
	glVertex3f(0.0, 100.0, 0.0);
	glEnd();
	

	glPopMatrix();
}
void OpenGL_ProjectManager::renderRealTimeBegin()
{
	glViewport(0, 0, GlobalVariables::CONTEXT_WIDTH, GlobalVariables::CONTEXT_HEIGHT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (float)GlobalVariables::CONTEXT_WIDTH / GlobalVariables::CONTEXT_HEIGHT, 0.01f, 100.0f);
	//glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0f, 102.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(
		0,.4f, .7f,
		0,0,0,
		0,1,0);
	worldRender.draw();
	//render_texture(texture_depth, 0);

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
