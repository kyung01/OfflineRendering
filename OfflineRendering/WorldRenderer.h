#pragma once
#include <memory>
#include "GLFW_GLEW.h"
#include "AssimpScene.h"
#include "KVertexArrayObject.h"
#include "glm\glm.hpp"
class WorldRenderer {
	const char
		*PATH_PLY_BUNNY		= "Model/bunny.ply",
		*PATH_PLY_TEAPOT	= "Model/teapot.ply",
		*PATH_PLY_APPLE		= "Model/cube.ply";
	glm::mat4 mat_model;
	std::shared_ptr<AssimpScene> scene_bunny;
	KVertexArrayObject vao_bunny, vao_teapot, vao_apple;
	float scene_bunny_angle;
	//render the world
	void render_environment(glm::mat4 *matView, GLuint id_mat_viewModel, GLuint id_pos);
	void init(KVertexArrayObject &vao,const char * path,
		float * arr_vert, int arr_vert_length,
		float * arr_normal, int arr_normal_length,
		int * arr_indices, int arr_indices_length);
public:
	void init();
	void draw(glm::mat4 *matView, GLuint id_mat_viewModel, GLuint id_pos, GLuint id_pos_texture);


};