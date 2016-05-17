#pragma once
#include "GLFW\glfw3.h"
#include "PlayerMovement.h"
#include "HPR.h"
#include <iostream>
using namespace std;
class EasyGLFW_Modified {
	PlayerMovement plrMove;
	int id;
	bool isContinue;
public:
	EasyGLFW_Modified();
	void init();
	bool loop(GLFWwindow* window); // modify the loop as you please
	void HDR_KEYS(GLFWwindow* window, int key, int scancode, int action, int mods);// modify the function as you please 


};