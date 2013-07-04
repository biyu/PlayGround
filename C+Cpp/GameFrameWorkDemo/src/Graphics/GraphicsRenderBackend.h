#ifndef GRAPHICS_RENDER_BACKEND_H
#define GRAPHICS_RENDER_BACKEND_H

#include <Util\Common.h>
#include "IGraphicsRenderCallbacks.h"

class GraphicsRenderBackend
{
protected:
	GraphicsRenderBackend(IGraphicsRenderCallbacks* gRenderCallbacks = 0);	// hide construtor

public:
	virtual void init(int argc, char** argv);
	virtual void run();
	virtual GLfloat fps();

public:
	void stage(IGraphicsRenderCallbacks* gRenderCallbacks);	// stage new render callbacks
	void unstage();	// unstage current render callbacks
	
protected:
	IGraphicsRenderCallbacks* currentRenderCallbacks() const;

private:
	static IGraphicsRenderCallbacks* _currentRenderCallbacks;
};

#endif // !GRAPHICS_RENDER_BACKEND_H
