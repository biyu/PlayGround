#include "DemoObjectPainter.h"
#include <GL\glut.h>

DemoObjectPainter::DemoObjectPainter()
{
}

DemoObjectPainter::~DemoObjectPainter()
{
}

// TODO: use dynamical color later
void DemoObjectPainter::drawBox(float x, float y, float z,
								float dx, float dy, float dz,
								float roll, float pitch, float yaw)
{
	glPushMatrix();

	glTranslatef(x, y, z);
	glRotatef(roll,1.0,0.0,0.0);
	glRotatef(pitch,0.0,1.0,0.0);
	glRotatef(yaw,0.0,0.0,1.0);

	glBegin(GL_QUADS);

	glColor3f(0.0f,1.0f,0.0f);	// Blue
	glVertex3f( dx, dy,-dz);
	glVertex3f(-dx, dy,-dz);
	glVertex3f(-dx, dy, dz);
	glVertex3f( dx, dy, dz);

	glColor3f(1.0f,0.5f,0.0f);	// Orange
	glVertex3f( dx,-dy, dz);
	glVertex3f(-dx,-dy, dz);
	glVertex3f(-dx,-dy,-dz);
	glVertex3f( dx,-dy,-dz);

	glColor3f(1.0f,1.0f,0.0f);	// Yellow
	glVertex3f( dx,-dy,-dz);
	glVertex3f(-dx,-dy,-dz);
	glVertex3f(-dx, dy,-dz);
	glVertex3f( dx, dy,-dz);

	glColor3f(0.0f,0.0f,1.0f);	// Blue
	glVertex3f(-dx, dy, dz);
	glVertex3f(-dx, dy,-dz);
	glVertex3f(-dx,-dy,-dz);
	glVertex3f(-dx,-dy, dz);

	glColor3f(1.0f,0.0f,1.0f);	// Violet
	glVertex3f( dx, dy,-dz);
	glVertex3f( dx, dy, dz);
	glVertex3f( dx, -dy, dz);
	glVertex3f( dx,-dy,-dz);

	glColor3f(1.0f,0.0f,0.0f);	// Red    
	glVertex3f( dx, dy, dz);
	glVertex3f(-dx, dy, dz);
	glVertex3f(-dx,-dy, dz);
	glVertex3f( dx,-dy, dz);

	glEnd();
	glPopMatrix();
}