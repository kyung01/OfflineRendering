#pragma once
#include "GLFW_GLEW.h"
#include "AssimpScene.h"
#include <memory>
class WorldRenderer {
	std::shared_ptr<AssimpScene> scene_bunny;
	float scene_bunny_angle;
	//render the world
	void drwa_environment();
public:
	void init();
	void draw();// draw the world collection of required draw calls


};