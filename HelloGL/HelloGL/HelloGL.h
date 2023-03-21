#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include "Camera.h"
#include "InputManager.h"
#include "GL/freeglut.h"
#include "Mesh.h"
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

	void DrawObject(const std::shared_ptr<Mesh>& mesh);

	void DrawFrame();
	void TraverseSceneGraphChildren(const std::shared_ptr<Object>& object);
	void UpdateObjectMatrix(const std::shared_ptr<Object>& obj);

	InputManager InputManager;
	Camera* Camera;
private:
	SceneGraph _sceneGraph;
};