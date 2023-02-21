#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "Model.h"
#include "SceneGraph.h"

constexpr auto FRAME_TIME = 16;
constexpr auto PI = 3.14159265358979323846;

class HelloGL
{
public:
	HelloGL(int argc, char* argv[]);
	~HelloGL(void);

	void Display();
	void Update();
	void DrawPolygon();
	
	void DrawShape(Model::Model shape);
	Model::Model CreateNGon(int n, float angle = 0);

	void DrawModels();
	void DrawChildren(Object& parent);
	void DrawModel(Object& obj);

private:
	SceneGraph _sceneGraph;
	float rotation;
};