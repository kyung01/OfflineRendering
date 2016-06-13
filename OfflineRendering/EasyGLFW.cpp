#include "EasyGLFW.h"
#include <iostream>
EasyGLFW *EasyGLFW::THE_MOST_RECENT_INSTANCE = NULL;


void EasyGLFW::createContext(const char* name, int width, int height)
{
	glfwInit();
	window = glfwCreateWindow(width, height, name, NULL, NULL);
	glfwMakeContextCurrent(window);
	glewInit(); // calling this before above code will result in error
}

void EasyGLFW::init(int width, int height, const char* name) {
	EasyGLFW::THE_MOST_RECENT_INSTANCE = this;
	//modified = EasyGLFW_Modified();
	glfwInit();
	window = glfwCreateWindow(width, height, name, NULL, NULL);
	glfwMakeContextCurrent(window);
	
	glfwSetKeyCallback(window, HDR_KEYS);
	glfwSetCursorPosCallback(window, HDR_CURSOR_POS);
	modified.init(window);
}
void EasyGLFW::startLoop(){

	bool result;
	do {
		result = modified.loop(window);
		glfwPollEvents();
	} while (result);

	glfwDestroyWindow(window);
	glfwTerminate();
}

void EasyGLFW::HDR_KEYS(GLFWwindow* window, int key, int scancode, int action, int mods) {
	EasyGLFW::THE_MOST_RECENT_INSTANCE->modified.HDR_KEYS(window, key, scancode, action, mods);
}

void EasyGLFW::HDR_CURSOR_POS(GLFWwindow * window, double posX, double posY)
{
	EasyGLFW::THE_MOST_RECENT_INSTANCE->modified.HDR_CURSOR_POS(window, posX, posY);
}
