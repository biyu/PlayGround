#ifndef DEMORENDERER_H
#define DEMORENDERER_H

#define BUFSIZE 512

#include <vector>
#include <map>
#include "glm\glm.hpp"

class DemoSceneObject;
class IDemoClickableObject;
class DemoScenePickingRay;

class DemoScene
{
public:
	enum DemoSceneObjectType
	{
		Box,
		Button
		// add more supported type
	};

private:
	enum DemoSceneMouseState { MouseDown, MouseUp };

public:
	static DemoScene* instance();
	~DemoScene();

public:
	void init(int argc, char** argv);
	// call this BEFORE init function;
	void setWindowGeo(int windowX=0, int windowY=0, int windowWidth=0, int windowHeight=0);
	void startRender(void);

public:	// factory methods
	DemoSceneObject* createDemoObject(DemoSceneObjectType type, glm::vec3 worldPos);
	DemoSceneObject* createDemoObject(DemoSceneObjectType type, float x=0.0f, float y=0.0f, float z=0.0f);
	void removeDemoObject(DemoSceneObject* object);

	DemoScenePickingRay* getPickingRay();

private:
	DemoScene();	// singleton

private:
	// init opengl window
	void initGLWindow(int argc, char** argv);
	// init glut callbacks
	void initCallBacks();
	// init graphic scene
	void initRenderScene();

	void drawScene();

	void addObjectToScene(DemoSceneObject* sceneObject);
	void removeLastObjectFromScene();
	DemoSceneObject* getObjectById(unsigned int id);
	void processPicking(unsigned int pickedId);

private:	// static methods
	static void renderScene();
	static void sceneResize(int width, int height);
	static void updateScene();
	static void processNormalKeys(unsigned char key, int x, int y);
	static void handleMouseEvent(int button, int state, int x, int y);
	static void handlePassiveMotionEvent(int x, int y);

private:	// private members
	int _windowX, _windowY;
	int _windowWidth, _windowHeight;
	float _windowRatio;
	float _fovyAngle;	//field of view angle on y axis
	float _nearClipPanelDist;	// the "distance" of near clip panel from viewer(camera)
	float _farClipPanelDist;	// the "distance" of far clip panel from viewer(camera)
	glm::vec3 _cameraPos, _cameraLookAt, _cameraUp;

	// for picking
	DemoSceneMouseState _mouseState;
	IDemoClickableObject* _selectedChild;
	DemoScenePickingRay* _pickingRay;

	static std::map<unsigned int, DemoSceneObject* > _childrens;
	static DemoScene* _instance;
};

#endif // !DEMORENDERER_H