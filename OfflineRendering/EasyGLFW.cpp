#include "EasyGLFW.h"
#include <iostream>
EasyGLFW *EasyGLFW::THE_MOST_RECENT_INSTANCE = NULL;


void EasyGLFW::init(int width, int height, const char* name) {
	EasyGLFW::THE_MOST_RECENT_INSTANCE = this;
	//modified = EasyGLFW_Modified();
	glfwInit();
	window = glfwCreateWindow(width, height, name, NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, HDR_KEYS);
	modified.init();
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

void EasyGLFW::HDR_KEYS(GLFWwindow* window, int key, int scancode, int action, int mods){
	EasyGLFW::THE_MOST_RECENT_INSTANCE->modified.HDR_KEYS(window, key, scancode, action, mods);
}
