#ifndef DEMOBUTTONOBJECT_H
#define DEMOBUTTONOBJECT_H

#include "DemoSceneObject.h"
#include "IDemoClickableObject.h"

class DemoObjectPainter;

class DemoButtonObject : public DemoSceneObject, public IDemoClickableObject
{
public:
	DemoButtonObject(DemoScene* parent, glm::vec3 worldPos, glm::vec3 geo = glm::vec3(2.0f, 1.0f, 1.0f) /*, texture path*/);
	~DemoButtonObject();

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
	// button specific members
	glm::vec3 _geo;	// lenght in x, y, z

	DemoObjectPainter* _painter;
};

#endif // !DEMOBUTTONOBJECT_H

