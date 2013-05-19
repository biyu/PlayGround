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
		float roll, float pitch, float yaw);

private:

};

#endif // !DEMOOBJECTPAINTER_H
