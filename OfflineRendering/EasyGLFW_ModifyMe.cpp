#include "EasyGLFW_Modified.h"
#include <iostream>
#include <map>
#include <glm\vec3.hpp>
#include "PlayerMovement.h"
EasyGLFW_Modified::EasyGLFW_Modified() :
	windowSize(2),
	posCursorPre(2),
	scene_bunny("Model/bunny.ply"){
	
	isContinue = true;
}


void EasyGLFW_Modified::init(GLFWwindow* window)
{
	glfwGetWindowSize(window,&windowSize[0], &windowSize[1]);
	posCursorPre.assign({ windowSize [0]*.5f, windowSize [1]*.5f});
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPos(window, windowSize[0] * .5f, windowSize[1] * .5f);
	//plrMove2 = &PlayerMovement();
	//PlayerMovement().move(PlayerMovement::DIR_MOVEMENT::BACKWARD,.5f);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHT0);    /* Uses default lighting parameters */
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	gl_list_scene_bunny = glGenLists(1);
	glNewList(gl_list_scene_bunny, GL_COMPILE);
	scene_bunny.Render();
	glEndList();


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
	cout << "EE";
	int *frameSize = new int[2];
	glfwGetFramebufferSize(window, &frameSize[0], &frameSize[1]);

	//gotta draw stuff
	glViewport(0, 0, frameSize[0], frameSize[1]);
	glm::vec3 e = glm::vec3(1, 2, 3);

	
	glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0f, 102.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	vec3 pos = plrMove.getPosition();
	vec3 center = pos + plrMove.getDirForward();
	vec3 dirUpward = plrMove.getDirUpward();
	gluLookAt(
		-pos.x, pos.y, pos.z, 
		-center.x, center.y, center.z,
	//	0,1,0);
		dirUpward.x, dirUpward.y, dirUpward.z);
	//glTranslatef(-plrMove.x(), plrMove.y(),plrMove.z());
	//draw stuff here
	for (int i = 0; i < 10; i++) {
		glRotatef(40, 0, 1, 0);
		glPushMatrix();
		glTranslatef(0, 0, 3);
		draw();
		glPopMatrix();

	}
	glCallList(gl_list_scene_bunny);
	glfwSwapBuffers(window);
	return isContinue;
}

std::map<int, int> mapKeyDir({
	{ GLFW_KEY_W, PlayerMovement::FORWARD },
	{ GLFW_KEY_S, PlayerMovement::BACKWARD },
	{ GLFW_KEY_A, PlayerMovement::LEFT},
	{ GLFW_KEY_D, PlayerMovement::RIGHT }});
//std::map<int, glfw> keyMovemnet = {};
void EasyGLFW_Modified::HDR_KEYS(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		std::cout << "EasyGLFW_Modified Pressed Escape Key!\n";
		isContinue = false;
	}
	for (std::map<int, int>::iterator it = mapKeyDir.begin(); it != mapKeyDir.end(); it++) {
		if (key == it->first && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
			plrMove.move((PlayerMovement::DIR_MOVEMENT) it->second, .1f);
		}
	}
}

void EasyGLFW_Modified::HDR_CURSOR_POS(GLFWwindow * window, double posX, double posY)
{
	float power = .01f;
	double posXChange = posX - posCursorPre[0];
	double posYChange = posY - posCursorPre[1];
	//cout << "POSITION " << posXChange << " " << posYChange << endl;
	posCursorPre[0] = posX;
	posCursorPre[1] = posY;
	plrMove.rotateAxis(-posXChange*power, -posYChange*power);
}


