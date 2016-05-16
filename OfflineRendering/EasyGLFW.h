#pragma once
#include "GLFW\glfw3.h"
#include <string>
using namespace std;

class EasyGLFW {
private :
	GLFWwindow* window;
	bool loop(); // modify the loop as you please
	static void HDR_KEYS(GLFWwindow* window, int key, int scancode, int action, int mods);// modify the function as you please 
public:
	void init(int width, int height, const char* name);
	void startLoop();
};