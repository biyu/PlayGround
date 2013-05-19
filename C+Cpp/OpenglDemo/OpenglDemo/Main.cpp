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
	// debug
	DemoBoxObject* testObj;
	testObj = (DemoBoxObject*)scene->CreateDemoObject(DemoScene::Box, -1.5f, 0.0f, -2.0f);
	testObj->setDX(2.0f);
	scene->CreateDemoObject(DemoScene::Box, 1.5f, 0.0f, -4.0f);

	scene->startRender();
	return 0;
}
 