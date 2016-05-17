#pragma once
#include "GLFW\glfw3.h"
#include "EasyGLFW_Modified.h"
#include <string>
using namespace std;

class EasyGLFW {
	static EasyGLFW *THE_MOST_RECENT_INSTANCE;
	EasyGLFW_Modified modified;
	GLFWwindow* window;
	static void HDR_KEYS(GLFWwindow* window, int key, int scancode, int action, int mods);// modify the function as you please 
public:
	void init(int width, int height, const char* name);
	void startLoop();
};