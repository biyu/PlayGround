#include "GraphicsRenderBackend.h"

IGraphicsRenderCallbacks* GraphicsRenderBackend::_currentRenderCallbacks = 0;


GraphicsRenderBackend::GraphicsRenderBackend(IGraphicsRenderCallbacks* gRenderCallbacks)
{
	if(gRenderCallbacks != 0)
		this->stage(gRenderCallbacks);
}

void GraphicsRenderBackend::init(int argc, char** argv)
{
	// need to be overrided in derived classes
}

void GraphicsRenderBackend::run()
{
	// need to be overrided in derived classes
}

GLfloat GraphicsRenderBackend::fps()
{
	// return 0 by default
	return 0.0f;
}

void GraphicsRenderBackend::stage(IGraphicsRenderCallbacks* gRenderCallbacks)
{
	if(gRenderCallbacks == 0)
		return;

	if(GraphicsRenderBackend::_currentRenderCallbacks != 0)
		this->unstage();

	GraphicsRenderBackend::_currentRenderCallbacks = gRenderCallbacks;
}

void GraphicsRenderBackend::unstage()
{
	if(GraphicsRenderBackend::_currentRenderCallbacks != 0)
	{
		GraphicsRenderBackend::_currentRenderCallbacks = 0;
	}
}

IGraphicsRenderCallbacks* GraphicsRenderBackend::currentRenderCallbacks() const
{
	return GraphicsRenderBackend::_currentRenderCallbacks;
}