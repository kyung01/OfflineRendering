#include <iostream>
#include "WorldRenderer.h"
#include "GlobalVariables.h"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"

float tmp = 0;
void WorldRenderer::init()
{
	const int SIZE = 600000;
	
	std::shared_ptr<float> arr_vert(new float[SIZE]);
	std::shared_ptr<float> arr_normal(new float[SIZE]);
	std::shared_ptr<int> arr_indices(new int[SIZE]);

	init(vao_bunny, PATH_PLY_BUNNY, arr_vert.get(), SIZE, arr_normal.get(), SIZE, arr_indices.get(), SIZE);
	init(vao_teapot, PATH_PLY_TEAPOT, arr_vert.get(), SIZE, arr_normal.get(), SIZE, arr_indices.get(), SIZE);
	init(vao_apple, PATH_PLY_APPLE, arr_vert.get(), SIZE, arr_normal.get(), SIZE, arr_indices.get(), SIZE);
	init(vao_cube, PATH_PLY_CUBE, arr_vert.get(), SIZE, arr_normal.get(), SIZE, arr_indices.get(), SIZE);
	init(vao_tetrahedron, PATH_PLY_TETRAHEDRON, arr_vert.get(), SIZE, arr_normal.get(), SIZE, arr_indices.get(), SIZE);
	
}

void WorldRenderer::render_environment(glm::mat4 * matView, GLuint id_mat_viewModel, GLuint id_pos)
{
	//std::cout << "WEE";
	float length = 3.0f;
	glBegin(GL_TRIANGLES);
	glVertexAttrib3f(id_pos, 0, 0, 0);
	glVertexAttrib3f(id_pos, 0, 1, 0);
	glVertexAttrib3f(id_pos, 0, 1, length);


	glVertexAttrib3f(id_pos, 0, 1, length);
	glVertexAttrib3f(id_pos, 0, 0, length);
	glVertexAttrib3f(id_pos, 0, 0, 0);

	//
	glVertexAttrib3f(id_pos, length, 0, 0);
	glVertexAttrib3f(id_pos, length, 1, 0);
	glVertexAttrib3f(id_pos, length, 1, length);

	 
	glVertexAttrib3f(id_pos, length, 1, length);
	glVertexAttrib3f(id_pos, length, 0, length);
	glVertexAttrib3f(id_pos, length, 0, 0);
	//

	glVertexAttrib3f(id_pos, 0, 0, 0);
	glVertexAttrib3f(id_pos, length, 0, 0);
	glVertexAttrib3f(id_pos, length, 1, 0);

	glVertexAttrib3f(id_pos, length, 1, 0);
	glVertexAttrib3f(id_pos, 0, 1, 0);
	glVertexAttrib3f(id_pos, 0, 0, 0);


	glVertexAttrib3f(id_pos, 0, 0, 0);
	glVertexAttrib3f(id_pos, 0, 0, length);
	glVertexAttrib3f(id_pos, length, 0, 0);


	glVertexAttrib3f(id_pos, length, 0, 0);
	glVertexAttrib3f(id_pos, length, 0, length);
	glVertexAttrib3f(id_pos, 0, 0, length);

	glEnd();
}

void WorldRenderer::init(KVertexArrayObject& vao,const char* file, float * arr_vert, int arr_vert_length, float * arr_normal, int arr_normal_length, int * arr_indices, int arr_indices_length)
{
	int store_arr_vert_length, store_indices_length;
	AssimpScene scene (file);
	scene.init_glList();
	scene.get_data(
		arr_vert, arr_vert_length,	
		arr_normal, arr_normal_length,
		arr_indices, arr_indices_length,
		store_arr_vert_length, store_indices_length);

	vao.init(arr_vert, arr_normal, store_arr_vert_length / 3, arr_indices, store_indices_length / 3,glm::vec3(scene.sceneMax.x, scene.sceneMax.y, scene.sceneMax.z) );
}
float move = 0;
void WorldRenderer::draw(glm::mat4 * matView, GLuint id_mat_viewModel, GLuint id_pos, GLuint id_pos_texture, GLuint id_color )
{
	float wall_lighting = .3f;
	move += 0.1f;
	std::cout << "awssw";
	// render_environment(matView, id_mat_viewModel, id_pos);
	glm::mat4 mat;
	//mat =  glm::scale(mat, glm::vec3(5, 5, 5));


	mat = glm::translate(*matView, glm::vec3(.5, vao_cube.boundingBox.y,-.05f));
	mat = glm::scale<float>(mat, glm::vec3(1,1,.1f));
	glUniformMatrix4fv(id_mat_viewModel, 1, GL_FALSE, (float*)glm::value_ptr(mat));
	glUniform4f(id_color, .0, .0, .9, wall_lighting);
	glBindVertexArray(vao_cube.id_vertex_array);
	glDrawElements(GL_TRIANGLES, vao_cube.indice_length * 3, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	mat = glm::translate(*matView, glm::vec3(.5f, -.05, .5f));
	mat = glm::scale<float>(mat, glm::vec3(1, .1f, 1.f));
	glUniformMatrix4fv(id_mat_viewModel, 1, GL_FALSE, (float*)glm::value_ptr(mat));
	glUniform4f(id_color, 0.1, 0.1, 0.1, wall_lighting);
	glBindVertexArray(vao_cube.id_vertex_array);
	glDrawElements(GL_TRIANGLES, vao_cube.indice_length * 3, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);


	mat = glm::translate(*matView, glm::vec3(-.05f, .5f, .5f));
	mat = glm::scale<float>(mat, glm::vec3(.1f,1.0f, 1.f));
	glUniformMatrix4fv(id_mat_viewModel, 1, GL_FALSE, (float*)glm::value_ptr(mat));
	glUniform4f(id_color, .0, .9, .0, wall_lighting);
	glBindVertexArray(vao_cube.id_vertex_array);
	glDrawElements(GL_TRIANGLES, vao_cube.indice_length * 3, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);


	mat = glm::translate(*matView, glm::vec3(.5f, vao_bunny.boundingBox.y/2 , .5f ));
	mat = glm::rotate<float>(mat, (70 +move*14 ) * (3.14 / 90), glm::vec3(0, 1, 0));
	glUniformMatrix4fv(id_mat_viewModel, 1, GL_FALSE, (float*)glm::value_ptr(mat));
	glUniform4f(id_color, 1.0f, 0.0f, 0.0f, 1.00f);
	glBindVertexArray(vao_bunny.id_vertex_array);
	glDrawElements(GL_TRIANGLES, vao_bunny.indice_length*3, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glBindVertexArray(0);
	return;
}