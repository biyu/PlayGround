#ifndef DEMORENDERER_H
#define DEMORENDERER_H

#define BUFSIZE 512

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

private:
	enum DemoSceneMode
	{
		Render,
		Select
	};

public:
	static DemoScene* instance();
	~DemoScene();

public:
	void init(int argc, char** argv);
	// call this BEFORE init function;
	void setWindowGeo(int windowX=0, int windowY=0, int windowWidth=0, int windowHeight=0);
	void startRender(void);

public:	// factory methods
	DemoSceneObject* createDemoObject(DemoSceneObjectType type, float x=0.0f, float y=0.0f, float z=0.0f);

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
	void removeObjectFromSceneById(unsigned int objectId);
	void removeLastObjectFromScene();

	void startPicking(int cursorX, int cursorY);
	unsigned int stopPicking();
	void processPicking(unsigned int pickedId);
	void handleObjectClicked(unsigned int clickedObjectId);

private:	// static methods
	static void renderScene();
	static void sceneResize(int width, int height);
	static void updateScene();
	static void processNormalKeys(unsigned char key, int x, int y);
	static void handleMouseEvent(int button, int state, int x, int y);

private:	// private members
	int _windowX;
	int _windowY;
	int _windowWidth;
	int _windowHeight;
	float _windowRatio;
	// for picking
	unsigned int _selectBuf[BUFSIZE];
	DemoSceneMode _mode;
	int _mouseCursorX;
	int _mouseCursorY;

	static std::vector<DemoSceneObject* > _renderObjects;
	static DemoScene* _instance;
};

#endif // !DEMORENDERER_H