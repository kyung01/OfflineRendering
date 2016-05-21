#include "OpenGL_ProjectManager.h"
#include "GlobalVariables.h"
void OpenGL_ProjectManager::initWorld()
{
	//crate world
	//give the world to the world renderer
}
void OpenGL_ProjectManager::init()
{
	this->easyGLFW.createContext(GlobalVariables::CONTEXT_NAME, GlobalVariables::CONTEXT_WIDTH, GlobalVariables::CONTEXT_HEIGHT);
	this->stateRender = RENDER_OFFLINE;// first we will initiate to render in real time
	initWorld();
	
}

void OpenGL_ProjectManager::renderRealTimeBegin()
{
	glViewport(0, 0, GlobalVariables::CONTEXT_WIDTH, GlobalVariables::CONTEXT_HEIGHT);
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0f, 102.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	worldRender.drawAndRecord();
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
