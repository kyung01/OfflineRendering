#include "EasyGLFW_Modified.h"
#include <iostream>
#include <map>
#include <glm\vec3.hpp>
#include "PlayerMovement.h"
EasyGLFW_Modified::EasyGLFW_Modified() {
	isContinue = true;
}

void EasyGLFW_Modified::init()
{
	//plrMove2 = &PlayerMovement();
	//PlayerMovement().move(PlayerMovement::DIR_MOVEMENT::BACKWARD,.5f);
}

void draw() {
	glBegin(GL_TRIANGLES);
	glColor3f(1.f, 0.f, 0.f);
	glVertex3f(-0.6f, -0.4f, 0.f);
	glColor3f(0.f, 1.f, 0.f);
	glVertex3f(0.6f, -0.4f, 0.f);
	glColor3f(0.f, 0.f, 1.f);
	glVertex3f(0.f, 0.6f, 0.f);
	glEnd();
}


bool EasyGLFW_Modified::loop(GLFWwindow* window)
{
	//
	int *frameSize = new int[2];
	glfwGetFramebufferSize(window, &frameSize[0], &frameSize[1]);

	//gotta draw stuff
	glViewport(0, 0, frameSize[0], frameSize[1]);
	glm::vec3 e = glm::vec3(1, 2, 3);
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glTranslatef(plrMove.x(), plrMove.y(),plrMove.z());
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//draw stuff here
	draw();
	glfwSwapBuffers(window);
	return isContinue;
}

//std::map<int, glfw> keyMovemnet = {};
void EasyGLFW_Modified::HDR_KEYS(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	if (action != GLFW_PRESS) return;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		std::cout << "EasyGLFW_Modified Pressed Escape Key!\n";
		isContinue = false;
	}
	if (key == GLFW_KEY_S) {
		plrMove.move(PlayerMovement::LEFT, .1f);
		

	}

}