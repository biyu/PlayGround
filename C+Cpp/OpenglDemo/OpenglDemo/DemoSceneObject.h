#ifndef DEMORENDEREROBJECT_H
#define DEMORENDEREROBJECT_H

class DemoScene;

class DemoSceneObject
{
public:
	DemoSceneObject(DemoScene* parent, float x=0.0f, float y=0.0f, float z=0.0f)
		: _x(x), _y(y), _z(z),
		_roll(0.0f), _pitch(0.0f), _yaw(0.0f),
		_rollSpd(0.0f), _pitchSpd(0.0f), _yawSpd(0.0f),
		_scene(parent)
	{
		// TODO: find a better way to handle object id
		static unsigned int currentId = 100;
		this->_id = currentId++;
	}
	~DemoSceneObject() { }

public:	// getter and setter
	float getX() const { return this->_x; }
	float getY() const { return this->_y; }
	float getZ() const { return this->_z; }
	float getRoll() const { return this->_roll; }
	float getPitch() const { return this->_pitch; }
	float getYaw() const { return this->_yaw; }
	float getRollSpd() const { return this->_rollSpd; }
	float getPitchSpd() const { return this->_pitchSpd; }
	float getYawSpd() const { return this->_yawSpd; }
	unsigned int getId() const { return this->_id; }
	
	void setX(float newX) { this->_x = newX; }
	void setY(float newY) { this->_y = newY; }
	void setZ(float newZ) { this->_z = newZ; }
	void setRoll(float newRoll) { this->_roll = newRoll; }
	void setPitch(float newPitch) { this->_pitch = newPitch; }
	void setYaw(float newYaw) { this->_yaw = newYaw; }
	void setRollSpd(float newRollSpd) { this->_rollSpd = newRollSpd; }
	void setPitchSpd(float newPitchSpd) { this->_pitchSpd = newPitchSpd; }
	void setYawSpd(float newYawSpd) { this->_yawSpd = newYawSpd; }

public:
	virtual void render() = 0;
	virtual void update() = 0;

protected:
	float _x, _y, _z;
	float _roll, _pitch, _yaw;
	float _rollSpd, _pitchSpd, _yawSpd;
	unsigned int _id;
	DemoScene* _scene;
};

#endif // !DEMORENDEREROBJECT_H