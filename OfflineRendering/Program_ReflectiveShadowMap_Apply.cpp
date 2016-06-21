#include "Program_ReflectiveShadowMap_Apply.h"

void Program_ReflectiveShadowMap_Apply::init_uniformLocs()
{
	Program_View_Inverted::init_uniformLocs();
	id_mat_light = glGetUniformLocation(id_program, NAME_MAT_LIGHT);
	id_world_size = glGetUniformLocation(id_program, NAME_WORLD_SIZE);
	id_texture_position = glGetUniformLocation(id_program, NAME_MAT_LIGHT);
	id_texture_depth = glGetUniformLocation(id_program, NAME_TEXTURE_DEPTH);
	id_texture_normal = glGetUniformLocation(id_program, NAME_TEXTURE_NORMAL);
	id_texture_flux = glGetUniformLocation(id_program, NAME_TEXTURE_FLUX);
	id_rand_seed = glGetUniformLocation(id_program, NAME_RAND_SEED);
}

void Program_ReflectiveShadowMap_Apply::use(
	float * mat_proj, float * mat_viewModel, float * mat_view_inverted, float* mat_light,
	float * world_size, 
	GLuint texture_position, GLuint texture_depth, GLuint texture_normal, GLuint texture_flux)
{
	Program_View_Inverted::use(mat_proj, mat_viewModel, mat_view_inverted);
	glUniformMatrix4fv(id_mat_light, 1, GL_FALSE, mat_light);
	glUniform3f(id_world_size, world_size[0], world_size[1], world_size[2]);
	GLuint id_targets[4] = { id_texture_position ,id_texture_depth,id_texture_normal,id_texture_flux};
	GLuint targets[4] = { texture_position ,texture_depth ,texture_normal ,texture_flux };
	for (int i = 0; i < 4; i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, targets[i]);
		glUniform1i(id_targets[i], i);
	}

}

void Program_ReflectiveShadowMap_Apply::set_rand_seed(float n)
{
	glUniform1f(id_rand_seed, n);
}
