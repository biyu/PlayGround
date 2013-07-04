#include "GameStageTestDemo.h"
#include <Game\GameSprite2D.h>

GameStageTestDemo::GameStageTestDemo(std::string stageName)
	: GameStage(stageName)
{
}

GameStageTestDemo::~GameStageTestDemo()
{
}

void GameStageTestDemo::init()
{

}

void GameStageTestDemo::render_callback()
{
	GameStage::render_callback();
	this->renderChildren();
}

void GameStageTestDemo::resize_callback(int width, int height)
{
	GameStage::resize_callback(width, height);
	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);
	// Reset Matrix
	glLoadIdentity();
	// Set the viewport to be the entire window
	glViewport(0, 0, width, height);
	// Set the correct perspective.
	gluOrtho2D(0, width, 0, height);
	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

void GameStageTestDemo::update_callback(int deltaT)
{
	GameStage::update_callback(deltaT);
}

void GameStageTestDemo::normalKeyboard_callback(unsigned char key, int x, int y)
{
	GameStage::normalKeyboard_callback(key, x, y);
	switch (key)
	{
	case 110:
		{
			GameSprite2D* sprite = dynamic_cast<GameSprite2D*>(this->children().at(0));
			if (sprite != NULL)
				sprite->nextFrame();
		}
	default:
		break;
	}
}

void GameStageTestDemo::specialKeyboard_callback(int key, int x, int y)
{
	GameStage::specialKeyboard_callback(key, x, y);
}

void GameStageTestDemo::mouse_callback(int button, int state, int x, int y)
{

}

void GameStageTestDemo::mousePassiveMotion_callback(int x, int y)
{

}