#ifndef DEMOSCENEPICKINGRAY_H
#define DEMOSCENEPICKINGRAY_H

#include "glm\glm.hpp"

class DemoScenePickingRay
{
public:
	DemoScenePickingRay(glm::vec3 cameraPos, glm::vec3 cameraLookAt, glm::vec3 cameraUp,
		float fovyAngle, float nearClipPanelDist, 
		float windowW, float windowH, float windowRatio);
	~DemoScenePickingRay(void);

public:
	void init();
	void calculatePickingRay(int mouseX, int mouseY);
	glm::vec3 getHitPointOnScreen();

public:
	glm::vec3 getClickPosOnNearClipPanel() const { return this->_clickPosOnNearClipPanel; }
	glm::vec3 getPickingRayDirection() const { return this->_pickingRayDirection; }

private:

private:
	glm::vec3 _cameraPos, _cameraLookAt, _cameraUp;
	float _fovyAngle, _nearClipPanelDist;
	float _windowW, _windowH, _windowRatio;

	glm::vec3 _viewDirection;	//	view direction from viewer (camera)
	glm::vec3 _nearClipPanelH, _nearClipPanelV;	//	h and v vectors on near clip panel in world position

	glm::vec3 _clickPosOnNearClipPanel;	// click position projected on near clip panel
	glm::vec3 _pickingRayDirection;	// direction vector of picking ray
};

#endif // !DEMOSCENEPICKINGRAY_H

