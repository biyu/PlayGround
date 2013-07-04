#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <Util\Common.h>
#include <Util\Constants.h>

class GameObject
{
protected:
	GameObject(size_t id=MAX_NUM_OF_STAGE_GAME_OBJECTS);

public:
	~GameObject();

public:
	// getter and setter
	size_t id() const { return this->_id; }
	void setId(size_t id) { this->_id = id; }

public:
	virtual void render() = 0;
	virtual void update(int deltaT /*milliseconds*/) = 0;

private:
	size_t _id;
};

#endif // !GAME_OBJECT_H
