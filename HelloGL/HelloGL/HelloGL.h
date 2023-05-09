#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include "Camera.h"
#include "InputManager.h"
#include "Light.h"
#include "GL/freeglut.h"
#include "Mesh.h"
#include "SceneGraph.h"
#include "Text.h"

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

	void DrawObject(const std::shared_ptr<Object>& obj);
	void DrawLight();
	void DrawString(const std::shared_ptr<Text>& text);

	void DrawFrame();
	void TraverseSceneGraphChildren(ListNode<std::shared_ptr<Object>>* node);
	void UpdateObjectMatrix(const std::shared_ptr<Object>& obj);

	void OnWindowResize(int width, int height);

	InputManager InputManager;
	Camera* Camera;
private:
	SceneGraph _sceneGraph;
	bool _mouseBoundToScreen = true;

	Light _light;
};