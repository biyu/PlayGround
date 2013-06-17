#ifndef DEMORENDEREROBJECT_H
#define DEMORENDEREROBJECT_H

#include "glm\glm.hpp"

class DemoScene;

class DemoSceneObject
{
public:
	DemoSceneObject(DemoScene* scene, glm::vec3 worldPos)
		: _worldPos(worldPos), 
		_worldScale(glm::vec3(0.0f, 0.0f, 0.0f)),
		_worldRotation(glm::vec3(0.0f, 0.0f, 0.0f)),
		_worldRotationSpd(glm::vec3(0.0f, 0.0f, 0.0f)),
		_scene(scene)
	{
		// TODO: find a better way to handle object id
		static unsigned int currentId = 100;
		this->_id = currentId++;
	}
	~DemoSceneObject() { }

public:	// getter and setter
	glm::vec3 getWorldPos() const { return this->_worldPos; }
	glm::vec3 getWorldScale() const { return this->_worldScale; }
	glm::vec3 getWorldRotation() const { return this->_worldRotation; }
	glm::vec3 getWorldRotationSpd() const { return this->_worldRotationSpd; }
	unsigned int getId() const { return this->_id; }
	
	void setWorldPos(glm::vec3 newPos) { this->_worldPos = newPos; }
	void setWorldScale(glm::vec3 newScale) { this->_worldScale = newScale; }
	void setWorldRotation(glm::vec3 newRotation) { this->_worldRotation = newRotation; }
	void setWorldRotationSpd(glm::vec3 newRotationSpd) { this->_worldRotationSpd = newRotationSpd; }

public:
	virtual void render() = 0;
	virtual void update() = 0;

protected:
	// transform members
	glm::vec3 _worldPos;
	glm::vec3 _worldScale;
	glm::vec3 _worldRotation;
	glm::vec3 _worldRotationSpd;
	

	unsigned int _id;
	DemoScene* _scene;
};

#endif // !DEMORENDEREROBJECT_H