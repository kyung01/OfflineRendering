#pragma once
#include "GLFW_GLEW.h"
#include "EasyGLFW_Modified.h"
#include <string>
using namespace std;

class EasyGLFW {
	static EasyGLFW *THE_MOST_RECENT_INSTANCE;
	static void HDR_KEYS(GLFWwindow* window, int key, int scancode, int action, int mods);// modify the function as you please 
	static void HDR_CURSOR_POS(GLFWwindow* window, double posX, double posY);// modify the function as you please 
	
	EasyGLFW_Modified modified;
public:
	GLFWwindow* window;
	void createContext(const char* name, int width, int height);
	void endContext();

	void init(int width, int height, const char* name);//depreciated
	void startLoop(); //depreciated
};