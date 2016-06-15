#include <iostream>
#include "WorldRenderer.h"
#include "GlobalVariables.h"

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
	glBegin(GL_TRIANGLES);
	glVertexAttrib3f(id_pos, 0.5f, 0.0f, -0.5f);
	glVertexAttrib3f(id_pos, -0.5f, 0.0f, -0.5f);
	glVertexAttrib3f(id_pos, -.5f, 0.f, 0.5f);

	glVertexAttrib3f(id_pos, -0.5f, 0.0f, 0.5f);
	glVertexAttrib3f(id_pos, 0.5f, 0.0f, 0.5f);
	glVertexAttrib3f(id_pos, 0.5f, 0.0f, -0.5f);
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
