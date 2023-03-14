#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include "Camera.h"
#include "InputManager.h"
#include "GL/freeglut.h"
#include "Model.h"
#include "SceneGraph.h"

constexpr int FRAME_TIME = 16;
constexpr double PI = 3.141592653589793;

class HelloGL
{
public:
	HelloGL(int argc, char* argv[]);
	~HelloGL();

	void Display();
	void Update();

	void CheckKeyboardInputs();

	void DrawObject(Model& model);

	void DrawFrame();
	void TraverseSceneGraphChildren(Object& object);
	void UpdateObjectMatrix(Object& obj);

	InputManager InputManager;
	Camera* Camera;
private:
	SceneGraph _sceneGraph;
};