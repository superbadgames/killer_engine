#ifndef EXAMPLE_H
#define EXAMPLE_H

//User defined includes


//3rd party includes
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>


class Example {
public:
	Example();

	bool init();
	void Prepare(float dt);
	void Render();
	void ShutDown();

	void OnResize(int width, int height);

private:
	float m_rotationAngle;
};

#endif