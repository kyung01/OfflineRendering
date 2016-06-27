#include <string>
#include <iostream>
#include <fstream>
#include "OpenGL_ProjectManager.h"
#include "GlobalVariables.h"
#include "ShaderPath.h"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"


float movement = 0;// 3.14 / 2;

void OpenGL_ProjectManager::init()
{
	this->easyGLFW.createContext(GlobalVariables::CONTEXT_NAME, GlobalVariables::CONTEXT_WIDTH, GlobalVariables::CONTEXT_HEIGHT);
	this->stateRender = RENDER_OFFLINE;// first we will initiate to render in real time

	glEnable(GL_DEPTH_TEST);
	glClearColor(0, 0, 0, 1);
	color_default = glm::vec4(1, 1, 1, 1);

	worldRender.init();
	world_space = glm::vec3(3, 3, 3);
	if (!program_texture.init_old(PATH_SHADER_TEXTURE_VERT, PATH_SHADER_TEXTURE_FRAG))
		error("Program_texture failed to init.");
	if (!program_rsm.init_old(PATH_SHADER_RSM_VERT, PATH_SHADER_RSM_FRAG))
		error("program_rsm failed to init.");
	if (!program_rsm_apply.init_old(PATH_SHADER_RSM_APPLY_VERT, PATH_SHADER_RSM_APPLY_FRAG))
		error("program_rsm failed to init.");
	program_rsm_apply.set_rand_seed(rand());

	fbo_rsm.init();
	fbo_rsm.set_depthbuffer(1024, 1024);
	fbo_rsm.set_colorbuffer(1024, 1024);
	fbo_rsm.set_colorbuffer(1024, 1024);
	fbo_rsm.set_colorbuffer(1024, 1024);

	biasMatrix = glm::mat4(
		0.5, 0.0, 0.0, 0.0,
		0.0, 0.5, 0.0, 0.0,
		0.0, 0.0, 0.5, 0.0,
		0.5, 0.5, 0.5, 1.0
		);
	mat_proj_firstPerson = glm::perspective<float>(2.0f, (float)GlobalVariables::CONTEXT_WIDTH / GlobalVariables::CONTEXT_HEIGHT, 0.1f, 2000.f);
	mat_proj_ortho = glm::ortho<float>(-2, 2, -2, 2, 0, 5);
	mat_proj_ortho_screen = glm::ortho<float>(0, GlobalVariables::CONTEXT_WIDTH, GlobalVariables::CONTEXT_HEIGHT, 0);
	
	mat_me_modelView = glm::lookAt(
		glm::vec3(1.2f, .9f , 1.2f), 
		glm::vec3(0.5f, 0.3f, .5f), 
		glm::vec3(0, 1, 0));
	mat_me_view_inversed = glm::inverse(mat_me_modelView);
	glm::vec3
		lightPos = glm::vec3(1.5f, .5f, 2.5),
		lightCenter = glm::vec3(lightPos.x, 0, 0) + glm::vec3(cos(movement), 0, 0)* 1.25f;

	mat_light_modelView = glm::lookAt(
		lightPos,
		lightCenter,
		glm::vec3(0, 1, 0));
	
	mat_light_MVP = biasMatrix * mat_proj_ortho * mat_light_modelView;

}
void OpenGL_ProjectManager::render_texture(GLuint id_vert, GLuint id_vert_texture, GLuint id_texture, int index)
{
	int
		width = 300, height = 300,
		xMax = GlobalVariables::CONTEXT_WIDTH / width,
		x = width *(index % xMax), y = height*(index/xMax);
	glBindTexture(GL_TEXTURE_2D, id_texture);

	glBegin(GL_QUADS);

	glVertexAttrib2f(id_vert_texture, 0.0, 1.0);
	glVertexAttrib3f(id_vert, x + 0.0, y + 0.0, 0);

	glVertexAttrib2f(id_vert_texture, 1.0, 1.0);
	glVertexAttrib3f(id_vert, x + width, y + 0.0f, 0);

	glVertexAttrib2f(id_vert_texture, 1.0, 0.0);
	glVertexAttrib3f(id_vert, x + width, y + height, 0);

	glVertexAttrib2f(id_vert_texture, 0.0, 0.0);
	glVertexAttrib3f(id_vert, x + 0.0, y + height, 0);

	glEnd();
}


void OpenGL_ProjectManager::error(const char * error_message)
{
	cout << "OpenGL_ProjectManager::error::" << error_message << endl;
	system("pause");
	exit(-1);
}

void OpenGL_ProjectManager::set_FBO(KFrameBufferObject * buffer)
{
	if (buffer == NULL) {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, GlobalVariables::CONTEXT_WIDTH, GlobalVariables::CONTEXT_HEIGHT);
		return;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, buffer->id_fbo);
	/*
	*/
	GLuint attachment[10];
	for (int i = 0; i < buffer->ids_texutre_color.size(); i++) {
		attachment[i] = GL_COLOR_ATTACHMENT0 + i;
	}
	glDrawBuffers(buffer->ids_texutre_color.size(), attachment);

	glViewport(0, 0, buffer->get_color_width() , buffer->get_color_height() );
}

void OpenGL_ProjectManager::update(float timeElapsed)
{
	cout << "Wsw" << endl;
	movement += .002f;
	mat_me_modelView = glm::lookAt(
		glm::vec3(1.2f, .9f -movement, 1.2f),
		glm::vec3(0.5f, 0.3f, .5f),
		glm::vec3(0, 1, 0));
}

void OpenGL_ProjectManager::render()
{
	//cout << "WEEWWE";
	glm::vec3
		world_size = glm::vec3(1, 1, 1),
		lightPos = glm::vec3(0.4, .5, 0.0) + glm::vec3(abs(cos(0 + 45)), 0, abs(sin(0 + 45))) *1.5f,
		lightCenter = glm::vec3(.0f, 0, .0f),
		lightDir = glm::normalize(lightCenter - lightPos);

	mat_light_modelView = glm::lookAt(
		lightPos,
		lightCenter,
		glm::vec3(0, 1, 0));
	mat_light_view_inverted = glm::inverse(mat_light_modelView);
	mat_light_MVP = biasMatrix * mat_proj_ortho * mat_light_modelView;



	set_FBO(&fbo_rsm);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	program_rsm.use(
		glm::value_ptr(mat_proj_ortho), glm::value_ptr(mat_light_modelView), glm::value_ptr(mat_light_view_inverted),
		glm::value_ptr(world_size),
		glm::value_ptr(lightPos), glm::value_ptr(lightDir), glm::value_ptr(color_default),
		glm::value_ptr(color_default));
	worldRender.draw(&mat_light_modelView, program_rsm.id_mat_viewModel, program_rsm.id_pos, 0, program_rsm.id_material_color);
	program_rsm.unUse();

	set_FBO(NULL);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	program_rsm_apply.use(
		glm::value_ptr(mat_proj_firstPerson), glm::value_ptr(mat_me_modelView), glm::value_ptr(mat_me_view_inversed),
		glm::value_ptr(mat_light_MVP),
		glm::value_ptr(world_size),
		fbo_rsm.get_color(0), fbo_rsm.get_depth(), fbo_rsm.get_color(1), fbo_rsm.get_color(2));

	worldRender.draw(&mat_me_modelView, program_rsm_apply.id_mat_viewModel, program_rsm_apply.id_pos, 0, program_rsm_apply.id_material_color);
	program_rsm_apply.unUse();

	glm::mat4 m;
	set_FBO(NULL);
	glClear(GL_DEPTH_BUFFER_BIT);
	program_texture.use(glm::value_ptr(mat_proj_ortho_screen), glm::value_ptr(m), -1);
	render_texture(program_texture.id_pos, program_texture.id_pos_texture, fbo_rsm.get_color(0), 0);
	render_texture(program_texture.id_pos, program_texture.id_pos_texture, fbo_rsm.get_color(1), 1);
	render_texture(program_texture.id_pos, program_texture.id_pos_texture, fbo_rsm.get_color(2), 2);
	program_texture.unUse();
}

void OpenGL_ProjectManager::renderRealTimeBegin()
{
	update(.01f);
	render();
	glfwSwapBuffers(this->easyGLFW.window);
}




void OpenGL_ProjectManager::renderOfflineBegin()
{
	renderRealTimeBegin();
}
void OpenGL_ProjectManager::renderRealTimeEnd()
{
	glfwPollEvents();
}
void OpenGL_ProjectManager::renderOfflineEnd()
{
	renderRealTimeEnd();
}

void OpenGL_ProjectManager::end()
{
	if (easyGLFW.window) {
		glfwDestroyWindow(easyGLFW.window);
	}	
}	