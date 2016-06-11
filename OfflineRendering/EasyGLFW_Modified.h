#pragma once
#include "GLFW_GLEW.h"
#include "PlayerMovement.h"
#include "HPR.h"
#include "AssimpScene.h"
#include <iostream>
#include <vector>

using namespace std;
class EasyGLFW_Modified {
	PlayerMovement plrMove;
	int id;
	bool isContinue;
	vector<int> windowSize;
	vector<double> posCursorPre;
	AssimpScene scene_bunny;
	GLenum gl_list_scene_bunny;
public:
	EasyGLFW_Modified();
	void init(GLFWwindow * window);
	bool loop(GLFWwindow* window); // modify the loop as you please
	void HDR_KEYS(GLFWwindow* window, int key, int scancode, int action, int mods);// modify the function as you please 
	void HDR_CURSOR_POS(GLFWwindow* window, double posX, double posY);


};