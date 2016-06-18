#include "OpenCV_VideoRecorder.h"
#include "OpenGL_ProjectManager.h"
#include "Main.h"
int main(){
	OpenCV_VideoRecorder videoRecorder;
	OpenGL_ProjectManager glProject;
	videoRecorder.init();
	glProject.init();
	int cycle = 0, cycleMax= 20*20;
	while (true) {
		cycle++;
		bool isContinue = true;
		switch (glProject.stateRender)
		{
		case OpenGL_ProjectManager::RENDER_UNDEFINED:
		case OpenGL_ProjectManager::RENDER_END:
			isContinue = false;
			break;
		case OpenGL_ProjectManager::RENDER_OFFLINE:
			videoRecorder.beginRendering();
			glProject.renderOfflineBegin();
			glProject.renderOfflineEnd();
			videoRecorder.endRendering();
			break;
		case OpenGL_ProjectManager::RENDER_REALTIME:
			glProject.renderRealTimeBegin();
			glProject.renderRealTimeEnd();
			break;
		}
		if (!isContinue || cycle >= cycleMax)break;
	}
	glProject.end();
	videoRecorder.end();
	system("pause");
	return 1;
}
/*
#include "Main.h"

#include "EasyGLFW.h"


bool main() {

EasyGLFW myGLFW;
myGLFW.init(500,500,"hi");
myGLFW.startLoop();

std::cout << "SystemEnding...\n";
return true;
//system("pause");
}
*/