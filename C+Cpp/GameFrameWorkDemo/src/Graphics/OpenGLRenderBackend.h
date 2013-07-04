#ifndef OPENGL_RENDER_BACKEND_H
#define OPENGL_RENDER_BACKEND_H

#include <Util\Common.h>
#include "GraphicsRenderBackend.h"

class OpenGLRenderBackend : public GraphicsRenderBackend
{
private:
	OpenGLRenderBackend(IGraphicsRenderCallbacks* gRenderCallbacks = 0);

public:
	static OpenGLRenderBackend* instance(IGraphicsRenderCallbacks* gRenderCallbacks = 0);
	void init(int argc=0, char** argv=0);	// override GraphicsRenderBackend::init()
	void run();		// override GraphicsRenderBackend::run()

public:
	GLfloat fps() { return this->_fps; }	// override GraphicsRenderBackend::fps()

private:
	void initGLWindow(int argc, char** argv);
	void initGLSettings();
	void initCallbacks();

	void updateDeltaTime();	// in milliseconds
	void updateFPS();
	void renderDebugInfo();
	void renderGLStr(GLfloat x, GLfloat y, GLfloat z, std::string info);

private:
	static void render();
	static void resize(int width, int height);
	static void update();
	static void normalKeyboard(unsigned char key, int x, int y);
	static void specialKeyboard(int key, int x, int y);
	static void mouse(int button, int state, int x, int y);
	static void mousePassiveMotion(int x, int y);

private:
	GLint _windowPosX, _windowPosY;
	GLint _windowWidth, _windowHeight;
	GLint _previousTime, _deltaTime;
	GLfloat _fps;	// frame per second
	GLint _frameCount, _deltaTimeSum;	// for calculating average fps

	static OpenGLRenderBackend* _instance;	// singleton
};

#endif // !OPENGL_RENDER_BACKEND_H