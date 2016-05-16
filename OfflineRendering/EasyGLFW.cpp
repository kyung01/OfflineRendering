#include "EasyGLFW.h"

void hhdlKeys(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	glfwDestroyWindow(window);
	glfwTerminate();
}

void EasyGLFW::init(int width, int height, const char* name) {
	glfwInit();
	window = glfwCreateWindow(width, height, name, NULL, NULL);
	glfwSetKeyCallback(window, HDR_KEYS);
}
void EasyGLFW::startLoop()
{
	bool result;
	do {
		result = loop();
		glfwPollEvents();
	} while (result);

}

bool EasyGLFW::loop()
{
	return true;
	//do stuff here 
}

void EasyGLFW::HDR_KEYS(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	glfwDestroyWindow(window);
	glfwTerminate();
}
