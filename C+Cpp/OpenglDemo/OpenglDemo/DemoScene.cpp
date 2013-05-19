#include "DemoScene.h"
#include "DemoBoxObject.h"
#include <GL\glut.h>	// define after "stdlib"

std::vector<DemoSceneObject* > DemoScene::_renderObjects;
DemoScene* DemoScene::_instance = NULL;

// TODO: make this class as singleton
DemoScene::DemoScene() 
	: _windowX(0), _windowY(0), _windowWidth(0), _windowHeight(0)
{
}

DemoScene* DemoScene::instance()
{
	if (_instance == NULL)
	{
		_instance = new DemoScene();
	}
	return _instance;
}

void DemoScene::init(int argc, char** argv)
{
	this->initGLWindow(argc, argv);
	this->initCallBacks();
	this->initRenderScene();
}

void DemoScene::setWindowGeo(int windowX, int windowY, int windowWidth, int windowHeight)
{
	this->_windowX = windowX;
	this->_windowY = windowY;
	this->_windowWidth = windowWidth;
	this->_windowHeight = windowHeight;
}

void DemoScene::initGLWindow(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowPosition(this->_windowX, this->_windowY);
	glutInitWindowSize(this->_windowWidth, this->_windowHeight);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	// NOTICE: create window before setting callback funcs
	glutCreateWindow("OpenGLDemo");
}

void DemoScene::initCallBacks()
{
	glutDisplayFunc(DemoScene::renderScene);
	glutReshapeFunc(DemoScene::sceneResize);
	glutIdleFunc(DemoScene::updateScene);
	glutKeyboardFunc(DemoScene::processNormalKeys);
}

void DemoScene::initRenderScene()
{
	glClearColor(0, 0, 0, 0);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.0f);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void DemoScene::startRender()
{
	glutMainLoop();
}

void DemoScene::renderScene()
{
	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	// setup camera
	gluLookAt(0.0f, 0.0f, -30.0f,
			  0.0f, 0.0f, -1.0f,
			  0.0f, 1.0f, 0.0f);

	for (std::vector<DemoSceneObject*>::iterator rit = DemoScene::_renderObjects.begin(); rit != DemoScene::_renderObjects.end(); ++rit)
	{
		DemoSceneObject* renderObject = *rit;
		renderObject->render();
	}

	glutSwapBuffers();
}

void DemoScene::sceneResize(int width, int height)
{
	// avoid zero exception
	if(height == 0)
		height = 1;
	float ratio = 1.0 * width / height;
	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);
	// Reset Matrix
	glLoadIdentity();
	// Set the viewport to be the entire window
	glViewport(0, 0, width, height);
	// Set the correct perspective.
	gluPerspective(45, ratio , 1 , 1000);
	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

void DemoScene::updateScene()
{
	for (std::vector<DemoSceneObject*>::iterator rit = DemoScene::_renderObjects.begin(); rit != DemoScene::_renderObjects.end(); ++rit)
	{
		DemoSceneObject* renderObject = *rit;
		renderObject->update();
	}
	DemoScene::renderScene();
}

void DemoScene::processNormalKeys(unsigned char key, int x, int y)
{
	DemoScene* render = DemoScene::instance();
	// when pressing 'N', add new object to scene at random position
	if(key == 110)
	{
		render->CreateDemoObject(DemoScene::Box, rand()%20 * 1.0f - 10.0f, rand()%10 * 1.0f - 5.0f, -2.0f);
	}
	// when pressing 'D', delete last object from scene
	if(key == 100)
	{
		render->removeObjectFromScene();
	}
}

DemoSceneObject* DemoScene::CreateDemoObject(DemoSceneObjectType type, float x, float y, float z)
{
	DemoSceneObject* sceneObject = NULL;
	switch (type)
	{
	case DemoScene::Box:
		sceneObject = new DemoBoxObject(x, y, z); 
		break;
	default:
		return NULL;
		break;
	}
	addObjectToScene(sceneObject);
	return sceneObject;
}

void DemoScene::addObjectToScene(DemoSceneObject* renderObject)
{
	this->_renderObjects.push_back(renderObject);
}

void DemoScene::removeObjectFromScene()
{
	if (this->_renderObjects.size() > 0)
	{
		this->_renderObjects.erase(_renderObjects.end()-1);
	}
}