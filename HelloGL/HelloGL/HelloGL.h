#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "Shape.h"

class HelloGL
{
public:
	HelloGL(int argc, char* argv[]);
	~HelloGL(void);

	void Display();
	void DrawPolygon();
	
	void DrawShape(Shape::Shape shape);
	Shape::Shape CreateShape(int n, float angle = 0);
};