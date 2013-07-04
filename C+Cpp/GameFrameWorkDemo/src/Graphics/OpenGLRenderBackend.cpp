#include <Util\Common.h>
#include <Util\Constants.h>
#include "OpenGLRenderBackend.h"

OpenGLRenderBackend* OpenGLRenderBackend::_instance = 0;

OpenGLRenderBackend::OpenGLRenderBackend(IGraphicsRenderCallbacks* gRenderCallbacks)
	: GraphicsRenderBackend(gRenderCallbacks), 
	_windowPosX(0), _windowPosY(0),
	_windowWidth(DEFAULT_WINDOW_WIDTH), _windowHeight(DEFAULT_WINDOW_HEIGHT),
	_previousTime(0), _deltaTime(0),
	_fps(0.0f), _frameCount(0), _deltaTimeSum(0)
{
}

OpenGLRenderBackend* OpenGLRenderBackend::instance(IGraphicsRenderCallbacks* gRenderCallbacks)
{
	if(OpenGLRenderBackend::_instance == 0)
	{
		OpenGLRenderBackend::_instance = new OpenGLRenderBackend(gRenderCallbacks);
	}
	return OpenGLRenderBackend::_instance;
}

void OpenGLRenderBackend::init(int argc, char** argv)
{
	this->initGLWindow(argc, argv);
	this->initGLSettings();
	this->initCallbacks();
}

void OpenGLRenderBackend::run()
{
	this->_previousTime = glutGet(GLUT_ELAPSED_TIME);
	glutMainLoop();
}

void OpenGLRenderBackend::initGLWindow(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowPosition(this->_windowPosX, this->_windowPosY);
	glutInitWindowSize(this->_windowWidth, this->_windowHeight);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	// NOTICE: create window before setting callback funcs
	glutCreateWindow("OpenGLRenderWindow");

	// Must be done after glut is initialized!
	GLenum res = glewInit();
	if (res != GLEW_OK) {
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
		return;
	}
}

void OpenGLRenderBackend::initGLSettings()
{
	glClearColor (0.0, 0.0, 0.0, 0.0);
	//glEnable(GL_DEPTH);
	//glEnable(GL_DEPTH_TEST);
	//glClearDepth(1.0f);
	//glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void OpenGLRenderBackend::initCallbacks()
{
	glutDisplayFunc(OpenGLRenderBackend::render);
	glutReshapeFunc(OpenGLRenderBackend::resize);
	glutIdleFunc(OpenGLRenderBackend::update);
	glutKeyboardFunc(OpenGLRenderBackend::normalKeyboard);
	glutSpecialFunc(OpenGLRenderBackend::specialKeyboard);
	glutMouseFunc(OpenGLRenderBackend::mouse);
	glutPassiveMotionFunc(OpenGLRenderBackend::mousePassiveMotion);
}

void OpenGLRenderBackend::updateDeltaTime()
{
	int currentTime = glutGet(GLUT_ELAPSED_TIME);
	int timeSpan = currentTime - this->_previousTime;
	this->_deltaTime = timeSpan;
	this->_previousTime = currentTime;
	
	//Debug(std::to_wstring(this->_deltaTime));
}

void OpenGLRenderBackend::updateFPS()
{
	// delta time (in milliseconds) is updated between frames
	if (this->_deltaTime == 0)
		return;

	// calculate average frame number per second
	this->_frameCount++;
	this->_deltaTimeSum += this->_deltaTime;

	if (this->_deltaTimeSum > 1000 /*milliseconds*/)
	{
		this->_fps = this->_frameCount * 1000.0f / this->_deltaTimeSum;
		this->_frameCount = 0;
		this->_deltaTimeSum = 0;
	}
}

void OpenGLRenderBackend::render()
{
	OpenGLRenderBackend* renderBackend = OpenGLRenderBackend::instance();
	IGraphicsRenderCallbacks* renderCallbacks = renderBackend->currentRenderCallbacks();

	glClear(GL_COLOR_BUFFER_BIT);

	if(renderCallbacks != 0)
	{
		renderCallbacks->render_callback();
	}

	glutSwapBuffers();
}

void OpenGLRenderBackend::resize(int width, int height)
{
	OpenGLRenderBackend* renderBackend = OpenGLRenderBackend::instance();
	IGraphicsRenderCallbacks* renderCallbacks = renderBackend->currentRenderCallbacks();

	if(renderCallbacks != 0)
	{
		renderCallbacks->resize_callback(width, height);
	}
}

void OpenGLRenderBackend::update()
{
	OpenGLRenderBackend* renderBackend = OpenGLRenderBackend::instance();
	IGraphicsRenderCallbacks* renderCallbacks = renderBackend->currentRenderCallbacks();

	renderBackend->updateDeltaTime();
	renderBackend->updateFPS();

	// calculate globle debug information

	if(renderCallbacks != 0)
	{
		renderCallbacks->update_callback(renderBackend->_deltaTime);
	}

	glutPostRedisplay();
}

void OpenGLRenderBackend::normalKeyboard(unsigned char key, int x, int y)
{
	OpenGLRenderBackend* renderBackend = OpenGLRenderBackend::instance();
	IGraphicsRenderCallbacks* renderCallbacks = renderBackend->currentRenderCallbacks();
	if(renderCallbacks != 0)
	{
		renderCallbacks->normalKeyboard_callback(key, x, y);
	}
}

void OpenGLRenderBackend::specialKeyboard(int key, int x, int y)
{
	OpenGLRenderBackend* renderBackend = OpenGLRenderBackend::instance();
	IGraphicsRenderCallbacks* renderCallbacks = renderBackend->currentRenderCallbacks();
	if(renderCallbacks != 0)
	{
		renderCallbacks->specialKeyboard_callback(key, x, y);
	}
}

void OpenGLRenderBackend::mouse(int button, int state, int x, int y)
{
	OpenGLRenderBackend* renderBackend = OpenGLRenderBackend::instance();
	IGraphicsRenderCallbacks* renderCallbacks = renderBackend->currentRenderCallbacks();
	if(renderCallbacks != 0)
	{
		renderCallbacks->mouse_callback(button, state, x, y);
	}
}

void OpenGLRenderBackend::mousePassiveMotion(int x, int y)
{
	OpenGLRenderBackend* renderBackend = OpenGLRenderBackend::instance();
	IGraphicsRenderCallbacks* renderCallbacks = renderBackend->currentRenderCallbacks();
	if(renderCallbacks != 0)
	{
		renderCallbacks->mousePassiveMotion_callback(x, y);
	}
}