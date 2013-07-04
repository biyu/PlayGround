#ifndef GAME_STAGE_H
#define GAME_STAGE_H

#include <Util\Common.h>
#include <Graphics\IGraphicsRenderCallbacks.h>

class GameObject;
class GameObjectIdGenerator;
class GraphicsRenderBackend;

class GameStage : public IGraphicsRenderCallbacks
{
protected:
	GameStage(std::string stageName);
	~GameStage();

public:
	virtual void init() { }
	void setRenderBackend(GraphicsRenderBackend* renderBackend) { this->_renderBackend = renderBackend; }
	void addToStage(GameObject* object);
	bool removeFromStage(GameObject* object);

public:
	// public accessors
	std::string name() const { return this->_name; }
	const std::map<unsigned int, GameObject*>& children() const { return this->_children; }

	GLint screenWidth() const { return this->_screenWidth; }
	GLint screenHeight() const { return this->_screenHeight; }

protected:
	void renderDebugInfo(GLfloat x, GLfloat y, GLfloat z);
	void renderChildren();

private:
	void renderGLStr(GLfloat x, GLfloat y, GLfloat z, std::string info);

public:
	// default callback actions of game stage
	virtual void render_callback();
	virtual void resize_callback(int width, int height);
	virtual void update_callback(int deltaT);
	virtual void normalKeyboard_callback(unsigned char key, int x, int y);
	virtual void specialKeyboard_callback(int key, int x, int y);
	virtual void mouse_callback(int button, int state, int x, int y);
	virtual void mousePassiveMotion_callback(int x, int y);
	
private:
	std::string _name;	// stage name
	std::map<size_t, GameObject* > _children;
	GameObjectIdGenerator* _idGenerator;
	GraphicsRenderBackend* _renderBackend;
	bool _debugEnabled;
	GLint _screenWidth, _screenHeight;
};

#endif // !GAME_STAGE_H
