#ifndef DEMOOBJECTPAINTER_H
#define DEMOOBJECTPAINTER_H

class DemoObjectPainter
{
public:
	DemoObjectPainter();
	~DemoObjectPainter();

public: // add new draw funcs here
	void drawBox(float x, float y, float z,
		float dx, float dy, float dz,
		float roll=0.0f, float pitch=0.0f, float yaw=0.0f);
	// TODO: using GLM vectors instead of seperated xyz
	void drawTextureBox(float x, float y, float z,
		float dx, float dy, float dz,
		float sx=0.0f, float sy=0.0f, float sz=0.0f,
		float roll=0.0f, float pitch=0.0f, float yaw=0.0f);

private:

};

#endif // !DEMOOBJECTPAINTER_H
