#ifndef DEMOBOXOBJECT_H
#define DEMOBOXOBJECT_H

#include "DemoSceneObject.h"
#include "IDemoClickableObject.h"

class DemoObjectPainter;

class DemoBoxObject : public DemoSceneObject, public IDemoClickableObject
{
public:
	DemoBoxObject(DemoScene* parent, glm::vec3 worldPos, glm::vec3 geo = glm::vec3(1.0f,1.0f,1.0f));
	~DemoBoxObject();

public:
	glm::vec3 getGeo() const { return this->_geo; }
	void setDX(glm::vec3 newGeo) { this->_geo = newGeo; }

public:
	// override pure virtual funcs of DemoSceneObject
	virtual void render();
	virtual void update();

	// override pure virtual funcs of IDemoClickableObject interface
	virtual void onMousePressed();
	virtual void onMouseReleased();	
	virtual void onMouseOver();
	virtual void onMouseLeft();

private:
	// box specific members
	glm::vec3 _geo;	// lenght in x, y, z

	bool _isClockwise;
	DemoObjectPainter* _painter;
};

#endif // !DEMOBOXOBJECT_H