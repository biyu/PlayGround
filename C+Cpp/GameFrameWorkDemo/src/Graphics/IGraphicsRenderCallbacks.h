#ifndef IGRAPHICS_RENDER_CALLBACKS_H
#define IGRAPHICS_RENDER_CALLBACKS_H

/*
* General interface class including all callbacks used by graphics backends
*/
class IGraphicsRenderCallbacks
{
public:
	virtual void render_callback() = 0;
	virtual void resize_callback(int width, int height) = 0;
	virtual void update_callback(int deltaT) = 0;
	virtual void normalKeyboard_callback(unsigned char key, int x, int y) = 0;	// "x and y" indicates current mouse location
	virtual void specialKeyboard_callback(int key, int x, int y) = 0;	// "x and y" indicates current mouse location
	virtual void mouse_callback(int button, int state, int x, int y) = 0;
	virtual void mousePassiveMotion_callback(int x, int y) = 0;
};

#endif // IGRAPHICS_RENDER_CALLBACKS_H