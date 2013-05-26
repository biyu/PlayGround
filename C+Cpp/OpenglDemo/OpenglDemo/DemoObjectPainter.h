#ifndef DEMOOBJECTPAINTER_H
#define DEMOOBJECTPAINTER_H

#include "glm\glm.hpp"

class DemoObjectPainter
{
public:
	DemoObjectPainter();
	~DemoObjectPainter();

public: // add new draw funcs here
	void drawBox(float x, float y, float z,
		float dx, float dy, float dz,
		float roll=0.0f, float pitch=0.0f, float yaw=0.0f,
		float sx = 1.0f, float sy = 1.0f, float sz = 1.0f);

	void drawBox(glm::vec3 worldPos, 
		glm::vec3 geo = glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f), 
		glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f));

private:

};

#endif // !DEMOOBJECTPAINTER_H
