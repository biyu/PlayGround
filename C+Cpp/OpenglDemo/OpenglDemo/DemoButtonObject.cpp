#include "DemoObjectPainter.h"
#include "DemoScene.h"
#include "DemoButtonObject.h"


DemoButtonObject::DemoButtonObject(DemoScene* parent, glm::vec3 worldPos, glm::vec3 geo)
		: DemoSceneObject(parent, worldPos), _geo(geo)
{
	this->_painter = new DemoObjectPainter();
}


DemoButtonObject::~DemoButtonObject()
{

}

void DemoButtonObject::render()
{
	if(this->_isMousePressed)
	{
		this->_painter->drawBox(this->_worldPos,
			this->_geo,
			glm::vec3(0.9f, 0.9f, 1.0f),
			this->_worldRotation);
	}
	else
	{
		this->_painter->drawBox(this->_worldPos,
			this->_geo,
			glm::vec3(1.0f, 1.0f, 1.0f),
			this->_worldRotation);
	}
}

void DemoButtonObject::update()
{

}

void DemoButtonObject::onMousePressed()
{
	IDemoClickableObject::onMousePressed();
}

void DemoButtonObject::onMouseReleased()
{
	IDemoClickableObject::onMouseReleased();

	this->_scene->createDemoObject(DemoScene::Box, glm::vec3(rand()%20 * 1.0f - 10.0f, rand()%10 * 1.0f - 5.0f, -2.0f));
}

void DemoButtonObject::onMouseOver() 
{

}

void DemoButtonObject::onMouseLeft()
{

}