#include <Graphics\Texture2D.h>
#include "GameSprite2D.h"
#include <Util\Common.h>

GameSprite2D::GameSprite2D()
	: GameObject(),
	_x(0.0f), _y(0.0f),
	_texture(0), _frameNumber(0), _currentFrame(0), _deltaSum(0),
	_inGameStatus(Active)
{
}

//GameSprite2D::GameSprite2D(size_t id, std::string textureFileName)
//	: GameObject(id),
//	_x(0.0f), _y(0.0f)
//{
//}

GameSprite2D::~GameSprite2D()
{
}

bool GameSprite2D::setTexture(Texture2D* texture)
{
	return false;
}

bool GameSprite2D::loadTexture(std::string fileName)
{
	this->_texture = new Texture2D(fileName);
	bool succeed = this->_texture->load();
	if(succeed)
	{
		std::wstringstream wss;
		wss << L"texture: w " << std::to_wstring(this->_texture->width()) 
			<< L", h "<< std::to_wstring(this->_texture->height()) << std::endl;
		Debug(wss.str());
	}
	else
	{
		Debug(L"load texture failed");
	}

	return succeed;
}

void GameSprite2D::nextFrame()
{ 
	if (this->_frameNumber == 0)
	{
		Debug(L"empty frame number");
		return;
	}
	this->_currentFrame = (++this->_currentFrame) % this->_frameNumber;
}


void GameSprite2D::render()
{
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	glLoadIdentity();
	glTranslatef(this->_x, this->_y, 0.0f);

	Texture2D* pTexture = this->_texture;
	if(pTexture == NULL)
		return;

	glEnable(GL_TEXTURE_2D);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);	//set color back to white
	pTexture->bind(GL_TEXTURE0);
	// calculate frame width and height
	if(this->_frameNumber == 0)
		return;
	float frameWidth = pTexture->width() * 1.0f / this->_frameNumber;
	float frameHeight = pTexture->height() * 1.0f;
	float texCoordU = this->_currentFrame * 1.0f/this->_frameNumber;
	float texCoordUOffset = 1.0f/this->_frameNumber;

	glBegin(GL_QUADS);
	// opengl loads pixel data in upside-down way. So top left -> bottom left, bottom right -> top right
	glTexCoord2f(texCoordU, 0.0f); glVertex2f(-frameWidth/2.0f, frameHeight/2.0f);	// top left
	glTexCoord2f(texCoordU+texCoordUOffset, 0.0f); glVertex2f(frameWidth/2.0f, frameHeight/2.0f);	// top right
	glTexCoord2f(texCoordU+texCoordUOffset, 1.0f); glVertex2f(frameWidth/2.0f, -frameHeight/2.0f);	// bottom right
	glTexCoord2f(texCoordU, 1.0f); glVertex2f(-frameWidth/2.0f, -frameHeight/2.0f);	// bottom left
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}

void GameSprite2D::update(int deltaT /*milliseconds*/)
{
	this->_deltaSum += deltaT;
	if(this->_deltaSum >= 160 /*ms*/)
	{
		this->nextFrame();
		this->_deltaSum = 0;
	}
}