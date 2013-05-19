#ifndef DEMOBOXOBJECT_H
#define DEMOBOXOBJECT_H

#include "DemoSceneObject.h"

class DemoObjectPainter;

class DemoBoxObject : public DemoSceneObject
{
public:
	DemoBoxObject(float x=0.0f, float y=0.0f, float z=0.0f,
		float dx=1.0f, float dy=1.0f, float dz=1.0f);
	~DemoBoxObject();

public:
	float getDX() const { return this->_dx; }
	float getDY() const { return this->_dy; }
	float getDZ() const { return this->_dz; }

	void setDX(float newDX) { this->_dx = newDX; }
	void setDY(float newDY) { this->_dy = newDY; }
	void setDZ(float newDZ) { this->_dz = newDZ; }

public:	// override pure virtual funcs
	virtual void render();
	virtual void update();

private:
	// box specific members
	float _dx;	// half lenght in x
	float _dy;	// half lenght in y
	float _dz;	// half lenght in z

	bool _isClockwise;
	DemoObjectPainter* _objectPainter;
};

#endif // !DEMOBOXOBJECT_H