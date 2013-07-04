#include <Util\Common.h>
#include "GameStage.h"
#include "GameObject.h"
#include <Graphics\GraphicsRenderBackend.h>

/* 
 * private class: 
 * - generate unique id for each game object on each game stage
 * - the amount of game objects can not exceed over the MAX_NUM_OF_STAGE_GAME_OBJECTS
 * - old id can be reused when the previous object was released
 */
class GameObjectIdGenerator
{
public:
	GameObjectIdGenerator()
		: _counterFlags()
	{ 
		this->_counterFlags.reset();
	}
	~GameObjectIdGenerator() { }

public:
	/* 
	 * get first available id in the game stage
	 * return true if succeeded, false if something wrong
	 */
	bool generateId(size_t* id_ptr)
	{
		*id_ptr = this->findFirstAvailableId();
		if (*id_ptr == this->max_capability())
		{
			Debug(L"too much game objects on this stage, need to remove some");
			return false;
		}
		this->setId(*id_ptr);
		return true;
	}

	void releaseId(size_t id)
	{
		if(id < this->max_capability())
		{
			this->unsetId(id);
		}
		else
		{
			Debug(L"wrong game object id");
		}
	}

	// get the max number of game objects for each game stage
	size_t max_capability() { return MAX_NUM_OF_STAGE_GAME_OBJECTS; }

private:
	size_t findFirstAvailableId()
	{
		size_t id = 0;
		while((id < this->max_capability())
			&&(this->_counterFlags.test(id)))
		{
			id++;
		}
		return id;
	}

	void setId(size_t id) { this->_counterFlags.set(id); }
	void unsetId(size_t id) { this->_counterFlags.reset(id); }

private:
	// bitset for object ids; 0 -> unused, 1 -> used
	std::bitset<MAX_NUM_OF_STAGE_GAME_OBJECTS> _counterFlags;
};

// ################################### GameStage implementation ###################################

GameStage::GameStage(std::string stageName)
	: _name(stageName), _idGenerator(new GameObjectIdGenerator()), _renderBackend(0),
	_debugEnabled(false), _screenWidth(0), _screenHeight(0)
{

}

GameStage::~GameStage()
{
	// clean all game objects of this stage
	for(std::map<size_t, GameObject* >::iterator rit = this->_children.begin(); rit != this->_children.end(); rit++)
	{
		GameObject* object = rit->second;
		delete object;
	}
	this->_children.clear();
}

void GameStage::addToStage(GameObject* object)
{
	if(object == NULL)
	{
		Debug(L"invalid game object");
		return;
	}
	size_t id;
	if (this->_idGenerator->generateId(&id))
	{
		object->setId(id);
		this->_children.insert(std::pair<size_t, GameObject* >(object->id(), object));
	}
	else
	{
		Debug(L"id generation failed");
		return;
	}
	
}

bool GameStage::removeFromStage(GameObject* object)
{
	if(this->_children.empty()
		|| object == NULL)
	{
		Debug(L"error happens when removing game object from stage");
		return false;
	}
	std::map<size_t, GameObject* >::iterator object_it = this->_children.find(object->id());
	if(object_it != this->_children.end())
	{
		this->_idGenerator->releaseId(object_it->first);
		delete object_it->second;
		this->_children.erase(object_it);
		return true;
	}
	else
	{
		Debug(L"can not find game object in current stage");
		return false;
	}
}

void GameStage::renderDebugInfo(GLfloat x, GLfloat y, GLfloat z)
{
	if(this->_renderBackend == NULL)
	{
		Debug(L"render backend is null");
		return;
	}
	// build debug information string
	std::stringstream ss;
	ss << "stage name: " << this->_name << std::endl;
	ss << "fps: " << std::to_string(this->_renderBackend->fps()) << std::endl;
	ss << "children amount: " << std::to_string(this->_children.size()) << std::endl;

	renderGLStr(x, y, z, ss.str());
}

void GameStage::renderGLStr(GLfloat x, GLfloat y, GLfloat z, std::string info)
{
	glPushMatrix();
	glLoadIdentity();
	glColor3f(0.0f, 1.0f, 0.0f);
	glRasterPos3f(x, y, z);
	glutBitmapString(RENDER_BACKEND_DEBUG_FONT_TYPE, (unsigned char*)info.c_str());
	glPopMatrix();
}

void GameStage::renderChildren()
{
	if(this->_children.empty())
		return;

	for (std::map<size_t, GameObject*>::iterator rit = this->_children.begin(); rit != this->_children.end(); ++rit)
	{
		GameObject* renderObject = rit->second;
		renderObject->render();
	}
}

void GameStage::render_callback()
{
	if(!this->_debugEnabled)	// debug not enabled, return
		return;
	// render debug information on left-top corner by default
	this->renderDebugInfo(10.0f, this->_screenHeight-50.0f, 0.0f);
}

void GameStage::resize_callback(int width, int height)
{
	this->_screenWidth = width;
	this->_screenHeight = height;
}

void GameStage::update_callback(int deltaT)
{
	if(this->_children.empty())
		return;
	// clean all game objects of this stage
	for(std::map<size_t, GameObject* >::iterator rit = this->_children.begin(); rit != this->_children.end(); rit++)
	{
		GameObject* child = rit->second;
		child->update(deltaT);
	}
}

void GameStage::normalKeyboard_callback(unsigned char key, int x, int y)
{

}

void GameStage::specialKeyboard_callback(int key, int x, int y)
{
	// F1 -> key = 1
	switch (key)
	{
	case 1:	// F1 pressed
		// switch debug mode on and off
		this->_debugEnabled = !this->_debugEnabled;
	default:
		break;
	}
}

void GameStage::mouse_callback(int button, int state, int x, int y)
{

}

void GameStage::mousePassiveMotion_callback(int x, int y)
{

}
