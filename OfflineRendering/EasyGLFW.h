#pragma once
#include "GLEW_GLFW.h"
#include "EasyGLFW_Modified.h"
#include <string>
using namespace std;

class EasyGLFW {
	static EasyGLFW *THE_MOST_RECENT_INSTANCE;
	static void HDR_KEYS(GLFWwindow* window, int key, int scancode, int action, int mods);// modify the function as you please 
	static void HDR_CURSOR_POS(GLFWwindow* window, double posX, double posY);// modify the function as you please 
	
	EasyGLFW_Modified modified;
	GLFWwindow* window;
public:
	void init(int width, int height, const char* name);
	void startLoop();
};