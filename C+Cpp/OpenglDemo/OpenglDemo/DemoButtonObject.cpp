#include "DemoObjectPainter.h"
#include "DemoScene.h"
#include "DemoButtonObject.h"


DemoButtonObject::DemoButtonObject(DemoScene* parent, float x, float y, float z, 
								   float dx, float dy, float dz)
		: DemoSceneObject(parent, x, y, z), 
		_dx(dx), _dy(dy), _dz(dz), _isPressed(false)
{
	this->_painter = new DemoObjectPainter();
}


DemoButtonObject::~DemoButtonObject()
{

}

void DemoButtonObject::render()
{
	if(this->_isPressed)
	{
		this->_painter->drawTextureBox(this->_x, this->_y, this->_z,
			this->_dx, this->_dy, this->_dz,
			0.9f, 0.9f, 1.0f,
			this->_roll, this->_pitch, this->_yaw);
	}
	else
	{
		this->_painter->drawTextureBox(this->_x, this->_y, this->_z,
			this->_dx, this->_dy, this->_dz,
			1.0f, 1.0f, 1.0f,
			this->_roll, this->_pitch, this->_yaw);
	}
}

void DemoButtonObject::update()
{

}

void DemoButtonObject::onPressed()
{
	this->_isPressed = true;
}

void DemoButtonObject::onReleased()
{
	this->_isPressed = false;
	this->_parent->createDemoObject(DemoScene::Box, rand()%20 * 1.0f - 10.0f, rand()%10 * 1.0f - 5.0f, -2.0f);
}

void DemoButtonObject::onHover() 
{

}
