#include "DemoScenePickingRay.h"
#include <cmath>

#define PI atan(1.0)*4

DemoScenePickingRay::DemoScenePickingRay(glm::vec3 cameraPos, glm::vec3 cameraLookAt, glm::vec3 cameraUp,
		float fovyAngle, float nearClipPanelDist, float windowW, float windowH, float windowRatio)
		: _cameraPos(cameraPos), _cameraLookAt(cameraLookAt), _cameraUp(cameraUp),
		_fovyAngle(fovyAngle), _nearClipPanelDist(nearClipPanelDist), 
		_windowW(windowW), _windowH(windowH), _windowRatio(windowRatio)
{
	this->init();
}


DemoScenePickingRay::~DemoScenePickingRay(void)
{
}

void DemoScenePickingRay::init()
{
	// get the direction where you are looking at
	this->_viewDirection = glm::normalize(this->_cameraLookAt - this->_cameraPos);
	// get the near panel axis vectors in world space
	this->_nearClipPanelH = glm::normalize(glm::cross(this->_viewDirection, this->_cameraUp));
	this->_nearClipPanelV = glm::normalize(glm::cross(this->_nearClipPanelH, this->_viewDirection));
	// scale near panel axis vectors
	float fovyAngleRadians = this->_fovyAngle * PI / 180.0f;
	float nearClipPanelHalfHeight = tan(fovyAngleRadians/2.0f)*this->_nearClipPanelDist;
	float nearClipPanelHalfWidth = nearClipPanelHalfHeight * this->_windowRatio;
	this->_nearClipPanelH *= nearClipPanelHalfWidth;
	this->_nearClipPanelV *= nearClipPanelHalfHeight;
}

void DemoScenePickingRay::calculatePickingRay(int mouseX, int mouseY)
{
	// get new lookat position
	this->_clickPosOnNearClipPanel = this->_cameraPos + this->_viewDirection*this->_nearClipPanelDist;
	// change screen coordinate center to lower-left
	float screenX = mouseX;
	float screenY = this->_windowH-mouseY*1.0f;
	screenX -= this->_windowW/2.0f;
	screenY -= this->_windowH/2.0f;
	// normalize position based on center coordinate
	screenX /= this->_windowW/2.0f;
	screenY /= this->_windowH/2.0f;
	// get click position in world space
	this->_clickPosOnNearClipPanel.x = this->_clickPosOnNearClipPanel.x + this->_nearClipPanelH.x*screenX + this->_nearClipPanelV.x*screenY;
	this->_clickPosOnNearClipPanel.y = this->_clickPosOnNearClipPanel.y + this->_nearClipPanelH.y*screenX + this->_nearClipPanelV.y*screenY;
	this->_clickPosOnNearClipPanel.z = this->_clickPosOnNearClipPanel.z + this->_nearClipPanelH.z*screenX + this->_nearClipPanelV.z*screenY;
	// get picking ray direction
	this->_pickingRayDirection = this->_clickPosOnNearClipPanel - this->_cameraPos;
}

glm::vec3 DemoScenePickingRay::getHitPointOnScreen()
{
	glm::vec3 hitPointVec;
	/*line standard equation in 3D world: 
	(x-x0)/m = (y-y0)/n = (z-z0)/p = t
	(m,n,p) is direction vector, and (x0, y0, z0) is start position
	*/
	float t = -this->_clickPosOnNearClipPanel.z / this->_pickingRayDirection.z;
	/* line parametized equation in 3D world:
	x = x0 + m*t
	y = y0 + n*t
	z = z0 + p*t
	*/
	hitPointVec.x = this->_clickPosOnNearClipPanel.x + this->_pickingRayDirection.x * t;
	hitPointVec.y = this->_clickPosOnNearClipPanel.y + this->_pickingRayDirection.y * t;
	hitPointVec.z = 0.0f;
	
	return hitPointVec;
}
