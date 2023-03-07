#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL/freeglut.h"
#include "Model.h"
#include "SceneGraph.h"

constexpr int FRAME_TIME = 14;
constexpr double PI = 3.141592653589793;

class HelloGL
{
public:
	HelloGL(int argc, char* argv[]);
	~HelloGL(void);

	void Display();
	void Update();
	void DrawPolygon();
	
	void DrawShape(const Model::Model& model);
	Model::Model CreateNGon(int n, float angle = 0);

	void DrawModels();
	void DrawChildren(Object& object);
	void DrawModel(Object& obj);

private:
	SceneGraph _sceneGraph;
};