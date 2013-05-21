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
	// NOTICE: manually create 3d box instead of using glut api
	// TODO: can be changed by using glutSolidCube()
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

void DemoObjectPainter::drawTextureBox(float x, float y, float z,
									   float dx, float dy, float dz,
									   float sx, float sy, float sz,
									   float roll, float pitch, float yaw)
{
	glPushMatrix();

	glTranslatef(x, y, z);
	glScalef(sx, sy, sz);
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