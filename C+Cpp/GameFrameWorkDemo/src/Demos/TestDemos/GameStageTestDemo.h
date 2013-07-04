#ifndef GAME_STAGE_TEST_DEMO
#define GAME_STAGE_TEST_DEMO

#include <Game\GameStage.h>

class GameStageTestDemo : public GameStage
{
public:
	GameStageTestDemo(std::string stageName);
	~GameStageTestDemo();

public:
	void init();	// overrive GameStage::init();

public:
	// default callback actions of game stage
	void render_callback();
	void resize_callback(int width, int height);
	void update_callback(int deltaT);
	void normalKeyboard_callback(unsigned char key, int x, int y);
	void specialKeyboard_callback(int key, int x, int y);
	void mouse_callback(int button, int state, int x, int y);
	void mousePassiveMotion_callback(int x, int y);

private:
};

#endif // !GameStageTestDemo
