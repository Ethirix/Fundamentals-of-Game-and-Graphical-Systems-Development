#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL/freeglut.h"
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
	
	void DrawShape(const Model::Model& model);
	Model::Model CreateNGon(int n, float angle = 0);

	void DrawModels();
	void DrawChildren(Object& object, Transform parentTransform = Transform());
	void DrawModel(Object& obj, Transform parentTransform = Transform());

private:
	SceneGraph _sceneGraph;
};