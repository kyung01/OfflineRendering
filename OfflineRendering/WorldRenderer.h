#pragma once
#include "GLFW_GLEW.h"
class WorldRenderer {
	//render the world
public:
	void drawAndRecord();// draw but also saved all the data to somewhere
	void drawRecorded();

};