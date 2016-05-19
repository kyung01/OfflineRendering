#include "OpenGL_ProjectManager.h"
#include "SharedConstValues.h"
void OpenGL_ProjectManager::init()
{
	this->easyGLFW.createContext(SCV::CONTEXT_NAME,SCV::CONTEXT_WIDTH, SCV::CONTEXT_HEIGHT);
	this->stateRender = RENDER_REALTIME;// first we will initiate to render in real time
}

void OpenGL_ProjectManager::renderRealTimeBegin()
{
}

void OpenGL_ProjectManager::renderRealTimeEnd()
{
	glfwPollEvents();
}

void OpenGL_ProjectManager::renderOfflineBegin()
{
}

void OpenGL_ProjectManager::renderOfflineEnd()
{
}
