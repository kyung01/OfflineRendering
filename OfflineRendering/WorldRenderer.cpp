#include <iostream>
#include "WorldRenderer.h"
#include "GlobalVariables.h"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"

float tmp = 0;
void WorldRenderer::drwa_environment()
{
	tmp += 3.5f;
	//draw counter clockwise
	//glScaled(1, 1, 1);
	//glTranslated(0, -.2f, -1);
	//glRotatef(tmp, 1, 0, 0);

	glPushMatrix();
	glBegin(GL_TRIANGLES);
	glNormal3f(0, 1,0);
	glColor3f(1, 0, 0);
	glVertex3f(0.5f, 0.0f, -0.5f);
	glVertex3f(-0.5f, 0.0f, -0.5f);
	glVertex3f(-.5f, 0.f, 0.5f);
	glNormal3f(0, 1,0);
	glNormal3f(0, 1,0);
	glNormal3f(0, 1, 0);
	glVertex3f(-0.5f, 0.0f, 0.5f);
	glVertex3f(0.5f, 0.0f, 0.5f);
	glVertex3f(0.5f, 0.0f, -0.5f);
	glNormal3f(0, 1, 0);
	glNormal3f(0, 1, 0);
	glEnd();
	glPopMatrix();
	/*
	glPushMatrix();
	glTranslated(0, .5	, -.5);
	glRotatef(90, 1, 0, 0);
	glBegin(GL_TRIANGLES);
	glNormal3f(0, 1, 0);
	glVertex3f(0.5f, 0.0f, -0.5f);
	glVertex3f(-0.5f, 0.0f, -0.5f);
	glVertex3f(-.5f, 0.f, 0.5f);
	glNormal3f(0, 1, 0);
	glNormal3f(0, 1, 0);
	glNormal3f(0, 1, 0);
	glVertex3f(-0.5f, 0.0f, 0.5f);
	glVertex3f(0.5f, 0.0f, 0.5f);
	glVertex3f(0.5f, 0.0f, -0.5f);
	glNormal3f(0, 1, 0);
	glNormal3f(0, 1, 0);
	glEnd();
	glPopMatrix();
	*/


}
void WorldRenderer::init()
{
	scene_bunny = std::make_shared<AssimpScene>(AssimpScene("Model/bunny.ply"));
	scene_bunny.get()->init_glList();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHT0);    /* Uses default lighting parameters */
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

	const int size = 100000;
	float arr[size];
	scene_bunny.get()->toArr(arr, size);
}

void WorldRenderer::draw()
{
	scene_bunny_angle += (360.0f / 20.0f) / 3.0f;
	glPushMatrix();
	//draw the lend
	
	float r = (1.0f / scene_bunny.get()->sceneMax.y) / 2;
	glTranslated(-scene_bunny.get()->sceneCenter.x, -scene_bunny.get()->sceneCenter.y, -scene_bunny.get()->sceneCenter.z);
	//glTranslatef(0, 0.0, -1.5f);
	glScalef(r, r, r);
	glRotatef(scene_bunny_angle, 0, 1, 0);
	//std::cout << scene_bunny.get()->sceneCenter.x<< " "<< scene_bunny.get()->sceneCenter.y << " " << scene_bunny.get()->sceneCenter.z << std::endl;
	//std::cout << r << std::endl;
	glCallList(scene_bunny.get()->gl_scene_id);
	glPopMatrix();
	drwa_environment();
}
void WorldRenderer::draw_scene_bunnies() {
	float r = (1.0f / scene_bunny.get()->sceneMax.y) / 2;
	for (int i = 0; i < 1; i++) {
		for (int j = 0; j < 3; j++) {
			glPushMatrix();
			glTranslated(-scene_bunny.get()->sceneCenter.x, -scene_bunny.get()->sceneCenter.y, -scene_bunny.get()->sceneCenter.z);
			glTranslated(i, 0, j);
			glScalef(r, r, r);
			//glRotatef(scene_bunny_angle, 0, 1, 0);
			//std::cout << scene_bunny.get()->sceneCenter.x<< " "<< scene_bunny.get()->sceneCenter.y << " " << scene_bunny.get()->sceneCenter.z << std::endl;
			//std::cout << r << std::endl;
			glCallList(scene_bunny.get()->gl_scene_id);
			glPopMatrix();
			drwa_environment();
			//drwa_environment();
		}
	}

}

void WorldRenderer::draw(glm::mat4 * matView, GLuint id_mat_viewModel, GLuint id_pos, GLuint id_pos_texture)
{
	float length = 1.f;
	glBegin(GL_TRIANGLES);
	glVertexAttrib3f(id_pos, length/2, 0.0f,  -length/2);
	glVertexAttrib3f(id_pos, -length/2, 0.0f, -length/2);
	glVertexAttrib3f(id_pos, -length/2, 0.f,   length/2);

	glVertexAttrib3f(id_pos, -length/2, 0.0f, length/2);
	glVertexAttrib3f(id_pos, length/2, 0.0f,  length/2);
	glVertexAttrib3f(id_pos, length/2, 0.0f, -length/2);


	glVertexAttrib3f(id_pos, -length/2, 0.0f,   length/2);
	glVertexAttrib3f(id_pos, -length/2, 0.0f,  -length/2);
	glVertexAttrib3f(id_pos, -length/2, length,-length/2);

	glVertexAttrib3f(id_pos, -length/2, length, -length/2);
	glVertexAttrib3f(id_pos, -length/2, length, length/2);
	glVertexAttrib3f(id_pos, -length/2, 0, length/2);

	glVertexAttrib3f(id_pos, -length / 2, 0, -length / 2);
	glVertexAttrib3f(id_pos, length / 2, 0, -length / 2);
	glVertexAttrib3f(id_pos, length / 2, length, -length / 2);


	glVertexAttrib3f(id_pos, length / 2, length, -length / 2);

	glVertexAttrib3f(id_pos, -length / 2, length, -length / 2);
	glVertexAttrib3f(id_pos, -length / 2, 0, -length / 2);



	//glVertexAttrib3f(id_pos, -length, length, -length);
	//glVertexAttrib3f(id_pos, -length, length, length);
	//glVertexAttrib3f(id_pos, -length, 0, length);

	for (int i = 0; i < 0; i++) {
		float y = i*.15f;
		float height = .1f;
		glVertexAttrib3f(id_pos, -0.5f, y+0.0f, 0.f);
		glVertexAttrib3f(id_pos, 0.5f, y + 0.0f, 0.0f);
		glVertexAttrib3f(id_pos, -0.5f, y + height, 0.0f);

		glVertexAttrib3f(id_pos, 0.5f, y + 0.0f, 0.0f);
		glVertexAttrib3f(id_pos, 0.5f, y + height, 0.0f);
		glVertexAttrib3f(id_pos, -0.5f, y + height, 0.0f);
	}
	
	glEnd();
	glBegin(GL_TRIANGLES);
	scene_bunny->RenderCheap(id_pos);
	glEnd();

	glm::mat4 mat;
	mat = glm::translate((*matView), glm::vec3(scene_bunny->sceneCenter.x, -scene_bunny->sceneCenter.y , scene_bunny->sceneCenter.z));
	//mat = glm::translate((*matView), glm::vec3(scene_bunny->sceneCenter.x, -scene_bunny->sceneCenter.y + .027f, scene_bunny->sceneCenter.z));
	//mat = glm::translate((*matView), glm::vec3(.3, scene_bunny->sceneMin.y, 0));
	mat =  glm::scale(mat, glm::vec3(4, 4, 4));
	//glm::mat4 mat_new = (*matView)*mat ;
	glUniformMatrix4fv(id_mat_viewModel, 1, GL_FALSE, (float*)glm::value_ptr(mat));
	glBegin(GL_TRIANGLES);
	scene_bunny->RenderCheap(id_pos);
	glEnd();
}

/*
for (int i = 0; i < -10; i++) {

glTranslatef(0, 0, 1);
glBegin(GL_TRIANGLES);
glColor3f(1.f, 0.f, 0.f);
glVertex3f(-0.6f, -0.4f, 0.f);
glColor3f(0.f, 1.f, 0.f);
glVertex3f(0.6f, -0.4f, 0.f);
glColor3f(0.f, 0.f, 1.f);
glVertex3f(0.f, 0.6f, 0.f);
glEnd();
}
*/
