#include "WorldRenderer.h"

void WorldRenderer::drawAndRecord()
{
	glPushMatrix();
	glTranslatef(0, 0, -3);
	for (int i = 0; i < 10; i++) {

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
	glPopMatrix();
	
}
