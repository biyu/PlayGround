#include <Util\Common.h>
#include <Graphics\OpenGLRenderBackend.h>
#include <Demos\TestDemos\GameStageTestDemo.h>
#include <Game\GameSprite2D.h>

int main(int argc, char** argv)
{
	srand((unsigned)time(NULL));
	// test
	GraphicsRenderBackend* renderBackend = OpenGLRenderBackend::instance();
	renderBackend->init(argc, argv); // call init() before starting rendering

	GameStage* testDemo = new GameStageTestDemo(std::string("GameStageTestDemo"));
	testDemo->setRenderBackend(renderBackend);

	GameSprite2D* testSprite = new GameSprite2D();
	testSprite->loadTexture("..\\..\\..\\src\\Demos\\TestDemos\\Images\\little_bear_sprite_sheet.png");
	testSprite->setPos(800,500);
	testSprite->setFrameNumber(12);
	testDemo->addToStage(testSprite);

	renderBackend->stage(testDemo);
	renderBackend->run();
	return 0;
}