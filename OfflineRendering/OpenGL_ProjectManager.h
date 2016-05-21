#pragma once
#include "EasyGLFW.h"
#include "WorldRenderer.h"
class OpenGL_ProjectManager {
	EasyGLFW easyGLFW;
	WorldRenderer worldRender; 
	void initWorld();
public:
	enum RenderState {RENDER_UNDEFINED, RENDER_REALTIME,RENDER_OFFLINE,RENDER_END};
	RenderState stateRender;
	void init();
	void renderRealTimeBegin();
	void renderRealTimeEnd();
	void renderOfflineBegin();
	void renderOfflineEnd();

};
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