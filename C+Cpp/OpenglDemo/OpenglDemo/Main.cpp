#include "DemoScene.h"
#include "DemoBoxObject.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>

int main(int argc, char** argv)
{
	srand((unsigned)time(NULL));
	DemoScene* scene = DemoScene::instance();
	scene->setWindowGeo(0,0,1000,800);
	scene->init(argc, argv);

	// create button
	DemoBoxObject* button = (DemoBoxObject*)scene->createDemoObject(DemoScene::Button, 0.0f, -8.0f, -2.0f);
	button->setDX(2.0f);

	scene->startRender();
	return 0;
}
 