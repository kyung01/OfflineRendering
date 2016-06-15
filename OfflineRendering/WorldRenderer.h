#pragma once
#include <memory>
#include "GLFW_GLEW.h"
#include "AssimpScene.h"
#include "glm\glm.hpp"
class WorldRenderer {
	glm::mat4 mat_model;
	std::shared_ptr<AssimpScene> scene_bunny;
	float scene_bunny_angle;
	//render the world
	void drwa_environment();
public:
	void init();
	void draw();// draw the world collection of required draw calls
	void draw_scene_bunnies();
	void draw(glm::mat4 *matView, GLuint id_mat_viewModel, GLuint id_pos, GLuint id_pos_texture);


};