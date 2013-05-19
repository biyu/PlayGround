#ifndef DEMORENDERER_H
#define DEMORENDERER_H

#include <vector>

class DemoSceneObject;

class DemoScene
{
public:
	enum DemoSceneObjectType
	{
		Box
		// add more supported type
	};
public:
	static DemoScene* instance();
public:
	void init(int argc, char** argv);
	// call this BEFORE init function;
	void setWindowGeo(int windowX=0, int windowY=0, int windowWidth=0, int windowHeight=0);
	void startRender(void);

public:	// factory methods
	DemoSceneObject* CreateDemoObject(DemoSceneObjectType type, float x=0.0f, float y=0.0f, float z=0.0f);

private:
	DemoScene();	// singleton

private:
	// init opengl window
	void initGLWindow(int argc, char** argv);
	// init glut callbacks
	void initCallBacks();
	// init graphic scene
	void initRenderScene();
	void addObjectToScene(DemoSceneObject* sceneObject);
	void removeObjectFromScene();

private:	// static methods
	static void renderScene();
	static void sceneResize(int width, int height);
	static void updateScene();
	static void processNormalKeys(unsigned char key, int x, int y);

private:	// private members
	int _windowX;
	int _windowY;
	int _windowWidth;
	int _windowHeight;

	static std::vector<DemoSceneObject* > _renderObjects;
	static DemoScene* _instance;
};

#endif // !DEMORENDERER_H