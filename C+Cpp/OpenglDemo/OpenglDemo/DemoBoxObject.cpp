#include "DemoScene.h"
#include "DemoBoxObject.h"
#include "DemoObjectPainter.h"
#include <stdlib.h>
#include <time.h>
#include <GL\glut.h>

DemoBoxObject::DemoBoxObject(DemoScene* parent, glm::vec3 worldPos, glm::vec3 geo)
	: DemoSceneObject(parent, worldPos), _geo(geo)
{
	this->_isClockwise = (rand()%100+1) > 50 ? true : false;
	this->_painter = new DemoObjectPainter();

	glm::vec3 rotationSpdVec = glm::vec3(0.2f, 0.4f, 0.6f);
	this->_worldRotationSpd = this->_isClockwise ? rotationSpdVec : -rotationSpdVec;
}

DemoBoxObject::~DemoBoxObject()
{
}

void DemoBoxObject::render()
{
	_painter->drawBox(this->_worldPos, this->_geo, this->_worldRotation);
}

void DemoBoxObject::update()
{
	this->_worldRotation += this->_worldRotationSpd;
}

void DemoBoxObject::onMousePressed()
{
	IDemoClickableObject::onMousePressed();
}

void DemoBoxObject::onMouseReleased()
{
	IDemoClickableObject::onMouseReleased();

	DemoScene* parent = this->_scene;
	if(parent == NULL)
		return;
	parent->removeDemoObject(this);
}

void DemoBoxObject::onMouseOver()
{
	if(!this->_isMouseOver)
	{
		this->_worldRotationSpd *= 8;
	}
	IDemoClickableObject::onMouseOver();
}

void DemoBoxObject::onMouseLeft()
{
	if(this->_isMouseOver)
	{
		this->_worldRotationSpd /= 8;
	}
	IDemoClickableObject::onMouseLeft();
}