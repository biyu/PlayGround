#ifndef GAME_SPRITE_2D_H
#define GAME_SPRITE_2D_H

#include "GameObject.h"

class Texture2D;

class GameSprite2D : public GameObject
{
public:
	enum InGameStatus { Active, Inactive };

public:
	GameSprite2D();
	//GameSprite2D(size_t id, std::string textureFileName = "");
	~GameSprite2D();

public:
	bool setTexture(Texture2D* texture);
	bool loadTexture(std::string fileName);

	void setFrameNumber(size_t number) { this->_frameNumber = number; }
	void setPos(GLfloat x, GLfloat y) { this->_x = x; this->_y = y; }
	void setInGameStatus(InGameStatus status) {  }

	void nextFrame();

public:
	virtual void render();
	virtual void update(int deltaT /*milliseconds*/);

private:

private:
	GLfloat _x, _y;
	size_t _frameNumber, _currentFrame;
	Texture2D* _texture;
	InGameStatus _inGameStatus;
	int _deltaSum;
};

#endif // !GAME_SPRITE_2D_H
