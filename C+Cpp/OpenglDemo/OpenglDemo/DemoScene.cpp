#include "DemoBoxObject.h"
#include "DemoButtonObject.h"
#include "DemoScene.h"
#include "IDemoClickableObject.h"
#include "DemoScenePickingRay.h"
//#include "Vector3f.h"
#include <cmath>
#include <GL\glut.h>	// define after "stdlib"
#include <iostream>

std::map<unsigned int, DemoSceneObject* > DemoScene::_childrens;
DemoScene* DemoScene::_instance = NULL;

// TODO: make this class as singleton
DemoScene::DemoScene() 
	: _windowX(0), _windowY(0), 
	_windowWidth(0), _windowHeight(0), _windowRatio(0.0f),
	_fovyAngle(45), _nearClipPanelDist(1.0f), _farClipPanelDist(1000.0f),
	_cameraPos(glm::vec3(0.0f, 0.0f, 30.0f)), _cameraLookAt(glm::vec3(0.0f, 0.0f, 0.0f)), _cameraUp(glm::vec3(0.0f, 1.0f, 0.0f)),
	_mouseState(DemoScene::MouseUp),
	_selectedChild(0), _pickingRay(0)
{
	
}

DemoScene::~DemoScene()
{
	// clean all scene objects
	for(std::map<unsigned int, DemoSceneObject*>::iterator rit = DemoScene::_childrens.begin(); rit != DemoScene::_childrens.end(); rit++)
	{
		DemoSceneObject* object = rit->second;
		delete object;
	}
	this->_childrens.clear();
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
	this->_windowRatio = 1.0 * this->_windowWidth / this->_windowHeight;
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
	glutMouseFunc(DemoScene::handleMouseEvent);
	glutPassiveMotionFunc(DemoScene::handlePassiveMotionEvent);
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
	DemoScene* scene = DemoScene::instance();

	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	// setup camera
	gluLookAt(0.0f, 0.0f, 30.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f);

	scene->drawScene();
	glutSwapBuffers();
}

void DemoScene::drawScene()
{
	// picking
	glInitNames();
	for (std::map<unsigned int, DemoSceneObject*>::iterator rit = DemoScene::_childrens.begin(); rit != DemoScene::_childrens.end(); ++rit)
	{
		DemoSceneObject* renderObject = rit->second;
		glPushName(renderObject->getId());
		renderObject->render();
		glPopName();
	}
}

void DemoScene::sceneResize(int width, int height)
{
	DemoScene* scene = DemoScene::instance();
	// avoid zero exception
	if(height == 0)
		height = 1;
	scene->_windowRatio = 1.0 * width / height;
	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);
	// Reset Matrix
	glLoadIdentity();
	// Set the viewport to be the entire window
	glViewport(0, 0, width, height);
	// Set the correct perspective.
	gluPerspective(scene->_fovyAngle, scene->_windowRatio , scene->_nearClipPanelDist, scene->_farClipPanelDist);
	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

void DemoScene::updateScene()
{
	for (std::map<unsigned int, DemoSceneObject*>::iterator rit = DemoScene::_childrens.begin(); rit != DemoScene::_childrens.end(); ++rit)
	{
		DemoSceneObject* renderObject = rit->second;
		renderObject->update();
	}
	DemoScene::renderScene();
}

void DemoScene::processNormalKeys(unsigned char key, int x, int y)
{
	DemoScene* scene = DemoScene::instance();
	// when pressing 'N', add new object to scene at random position
	if(key == 110)
	{
		scene->createDemoObject(DemoScene::Box, rand()%20 * 1.0f - 10.0f, rand()%10 * 1.0f - 5.0f, -2.0f);
	}
	// when pressing 'D', delete last object from scene
	if(key == 100)
	{
		scene->removeLastObjectFromScene();
	}
}

void DemoScene::handleMouseEvent(int button, int state, int x, int y)
{
	DemoScene* scene = DemoScene::instance();
	if (button != GLUT_LEFT_BUTTON)
		return;
	switch (state)
	{
	case GLUT_DOWN:
		scene->_mouseState = DemoScene::MouseDown;
		break;
	case GLUT_UP:
		{
			scene->_mouseState = DemoScene::MouseUp;
			DemoScenePickingRay* pickRay = scene->getPickingRay();
			pickRay->calculatePickingRay(x, y);
			glm::vec3 hitPointVec = pickRay->getHitPointOnScreen();
			scene->createDemoObject(DemoScene::Box, hitPointVec);
			break;
		}
	default:
		scene->_mouseState = DemoScene::MouseUp;
		break;
	}
	glutPostRedisplay(); 
}

void DemoScene::handlePassiveMotionEvent(int x, int y)
{

}

DemoScenePickingRay* DemoScene::getPickingRay()
{
	if(this->_pickingRay == NULL)
		this->_pickingRay = new DemoScenePickingRay(this->_cameraPos, this->_cameraLookAt, this->_cameraUp,
													this->_fovyAngle, this->_nearClipPanelDist, 
													this->_windowWidth, this->_windowHeight, this->_windowRatio);
	return this->_pickingRay;
}

void DemoScene::processPicking(unsigned int pickedId)
{
	if (pickedId == 0)
	{
		// if mouse up outside any object, check selected object cache
		if (this->_selectedChild != NULL
			&& this->_mouseState == DemoScene::MouseUp)
		{
			this->_selectedChild->onMouseReleased();
			this->_selectedChild = NULL;
		}
		return;
	}

	// get object by object id
	DemoSceneObject* object = this->getObjectById(pickedId);
	if(object == NULL)
		return;
	// check if object is clickable or not
	IDemoClickableObject* clickableObject = dynamic_cast<IDemoClickableObject*>(object);
	if(clickableObject == NULL)
		return;

	// TODO: handle different mouse actions here on picked object
	switch (this->_mouseState)
	{
	case DemoScene::MouseDown:
		clickableObject->onMousePressed();
		this->_selectedChild = clickableObject;
		break;
	case DemoScene::MouseUp:
		if(this->_selectedChild != NULL)
			this->_selectedChild->onMouseReleased();
		this->_selectedChild = NULL;
		break;
	}
}

DemoSceneObject* DemoScene::createDemoObject(DemoSceneObjectType type, glm::vec3 worldPos)
{
	DemoSceneObject* sceneObject = NULL;
	switch (type)
	{
	case DemoScene::Box:
		sceneObject = new DemoBoxObject(this, worldPos); 
		break;
	case DemoScene::Button:
		sceneObject = new DemoButtonObject(this, worldPos);
		break;
	default:
		return NULL;
		break;
	}
	addObjectToScene(sceneObject);
	return sceneObject;
}

DemoSceneObject* DemoScene::createDemoObject(DemoSceneObjectType type, float x, float y, float z)
{
	return this->createDemoObject(type, glm::vec3(x, y, z));
}

void DemoScene::removeDemoObject(DemoSceneObject* object)
{
	if (this->_childrens.empty()
		|| object == NULL)
		return;

	std::map<unsigned int, DemoSceneObject* >::iterator object_it = this->_childrens.find(object->getId());
	if(object_it != this->_childrens.end())
	{
		delete object_it->second;
		this->_childrens.erase(object_it);
	}
}

void DemoScene::addObjectToScene(DemoSceneObject* renderObject)
{
	if(renderObject == NULL)
		return;
	this->_childrens.insert(std::pair<unsigned int, DemoSceneObject*>(renderObject->getId(), renderObject));
}

// for test use
void DemoScene::removeLastObjectFromScene()
{
	if(this->_childrens.empty())
		return;
	this->removeDemoObject(this->_childrens.rbegin()->second);
}

DemoSceneObject* DemoScene::getObjectById(unsigned int id)
{
	std::map<unsigned int, DemoSceneObject* >::iterator object_it = this->_childrens.find(id);
	if(object_it != this->_childrens.end())
	{
		return object_it->second;
	}
	return NULL;
}