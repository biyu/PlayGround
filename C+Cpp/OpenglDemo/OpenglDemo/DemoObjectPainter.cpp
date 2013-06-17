#include "DemoObjectPainter.h"
#include <vector>
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
								float roll, float pitch, float yaw,
								float sx, float sy, float sz)
{
	// NOTICE: manually create 3d box instead of using glut api
	// create vertex list
	glm::vec4 vertexVecs []  = {
		glm::vec4(-dx, dy, dz, 1.0f),		// 0
		glm::vec4(dx, dy, dz, 1.0f),		// 1
		glm::vec4(dx, -dy, dz, 1.0f),		// 2
		glm::vec4(-dx, -dy, dz, 1.0f),	// 3
		glm::vec4(-dx, dy, -dz, 1.0f),	// 4
		glm::vec4(dx, dy, -dz, 1.0f),		// 5
		glm::vec4(dx, -dy, -dz, 1.0f),	// 6
		glm::vec4(-dx, -dy, -dz, 1.0f)	// 7
	};

	GLfloat
		min_x, max_x,
		min_y, max_y,
		min_z, max_z;

	glPushMatrix();

	glTranslatef(x, y, z);
	glScalef(sx, sy, sz);
	glRotatef(roll,1.0,0.0,0.0);
	glRotatef(pitch,0.0,1.0,0.0);
	glRotatef(yaw,0.0,0.0,1.0);

	glm::mat4 modelViewMatrix;
	glGetFloatv (GL_MODELVIEW_MATRIX, &modelViewMatrix[0][0]);
	for(int i=0; i<8; i++)
	{
		vertexVecs[i] = modelViewMatrix * vertexVecs[i];
	}
	min_x = max_x = vertexVecs[0].x;
	min_y = max_y = vertexVecs[0].y;
	min_z = max_z = vertexVecs[0].z;
	for (int i = 0; i < 8; i++) {
		if (vertexVecs[i].x < min_x) min_x = vertexVecs[i].x;
		if (vertexVecs[i].x > max_x) max_x = vertexVecs[i].x;
		if (vertexVecs[i].y < min_y) min_y = vertexVecs[i].y;
		if (vertexVecs[i].y > max_y) max_y = vertexVecs[i].y;
		if (vertexVecs[i].z < min_z) min_z = vertexVecs[i].z;
		if (vertexVecs[i].z > max_z) max_z = vertexVecs[i].z;
	}

	glBegin(GL_QUADS);

	glColor3f(0.0f,1.0f,0.0f);	// Green
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

	GLfloat hWidth = (max_x - min_x + 0.3f)/2.0f;
	GLfloat hHeight = (max_y - min_y + 0.3f)/2.0f;
	glPushMatrix();
	glTranslatef(x,y,z);
	glColor3f(0.0f,1.0f,0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2f(-hWidth, hHeight);
	glVertex2f(hWidth, hHeight);
	glVertex2f(hWidth, -hHeight);
	glVertex2f(-hWidth, -hHeight);
	glEnd();
	glPopMatrix();
}

void DemoObjectPainter::drawBox(glm::vec3 worldPos, glm::vec3 geo,
								glm::vec3 rotation, glm::vec3 scale)
{
	glm::vec3 hGeo = geo / 2.0f;
	this->drawBox(worldPos.x, worldPos.y, worldPos.z,
		hGeo.x, hGeo.y, hGeo.z,
		rotation.x, rotation.y, rotation.z,
		scale.x, scale.y, scale.z);
}