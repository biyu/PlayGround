#include "DemoBoxObject.h"
#include "DemoObjectPainter.h"
#include <stdlib.h>
#include <time.h>
#include <GL\glut.h>

DemoBoxObject::DemoBoxObject(float x, float y, float z,
							 float dx, float dy, float dz)
	: DemoSceneObject(x, y, z), _dx(dx), _dy(dy), _dz(dz)
{
	this->_isClockwise = (rand()%100+1) > 50 ? true : false;
	this->_objectPainter = new DemoObjectPainter();

	this->setRollSpd(this->_isClockwise ? 0.2f : -0.2f);
	this->setPitchSpd(this->_isClockwise ? 0.4f : -0.4f);
	this->setYawSpd(this->_isClockwise ? 0.6f : -0.6f);
}

DemoBoxObject::~DemoBoxObject()
{
}

void DemoBoxObject::render()
{
	_objectPainter->drawBox(this->_x, this->_y, this->_z,
		this->_dx, this->_dy, this->_dz,
		this->_roll, this->_pitch, this->_yaw);
}

void DemoBoxObject::update()
{
	this->_roll += this->getRollSpd();
	this->_pitch += this->getPitchSpd();
	this->_yaw += this->getYawSpd();
}