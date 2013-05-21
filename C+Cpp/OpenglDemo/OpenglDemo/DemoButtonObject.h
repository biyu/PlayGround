#ifndef DEMOBUTTONOBJECT_H
#define DEMOBUTTONOBJECT_H

#include "DemoSceneObject.h"
#include "IDemoClickableObject.h"

class DemoObjectPainter;

class DemoButtonObject : public DemoSceneObject, public IDemoClickableObject
{
public:
	DemoButtonObject(DemoScene* parent, float x=0.0f, float y=0.0f, float z=0.0f,
		float dx=1.0f, float dy=1.0f, float dz=1.0f /*, texture path*/);
	~DemoButtonObject();

public:
	float getDX() const { return this->_dx; }
	float getDY() const { return this->_dy; }
	float getDZ() const { return this->_dz; }

	void setDX(float newDX) { this->_dx = newDX; }
	void setDY(float newDY) { this->_dy = newDY; }
	void setDZ(float newDZ) { this->_dz = newDZ; }

public:
	// override pure virtual funcs of DemoSceneObject
	virtual void render();
	virtual void update();

	// override pure virtual funcs of IDemoClickableObject interface
	virtual void onPressed();
	virtual void onReleased();	
	virtual void onHover();

private:
	// button specific members
	float _dx;	// half lenght in x
	float _dy;	// half lenght in y
	float _dz;	// half lenght in z

	bool _isPressed;
	DemoObjectPainter* _painter;
};

#endif // !DEMOBUTTONOBJECT_H

