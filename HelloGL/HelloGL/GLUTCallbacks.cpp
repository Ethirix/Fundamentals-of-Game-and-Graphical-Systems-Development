#include "GLUTCallbacks.h"
#include "HelloGL.h"

namespace GLUTCallbacks
{
	namespace
	{
		HelloGL* helloGL = nullptr;
	}

	void Init(HelloGL* gl)
	{
		helloGL = gl;
	}

	void Display()
	{
		if (helloGL != nullptr)
		{
			helloGL->Display();
		}
	}

	void Timer(int frameTime)
	{
		int updateTime = glutGet(GLUT_ELAPSED_TIME);
		helloGL->Update();
		updateTime = glutGet(GLUT_ELAPSED_TIME) - updateTime;
		glutTimerFunc(frameTime - updateTime, Timer, frameTime);
	}

	void KeyboardDown(unsigned char key, int x, int y)
	{
		helloGL->InputManager.SetKeyDown(Keys::CastToKey(key));
	}

	void KeyboardUp(unsigned char key, int x, int y)
	{
		helloGL->InputManager.SetKeyUp(Keys::CastToKey(key));
	}

	void KeyboardSpecialDown(int key, int x, int y)
	{
		helloGL->InputManager.SetSpecialKeyDown(Keys::CastToSpecialKey(key));
	}

	void KeyboardSpecialUp(int key, int x, int y)
	{
		helloGL->InputManager.SetSpecialKeyUp(Keys::CastToSpecialKey(key));
	}

	void Mouse(int button, int state, int x, int y)
	{
		switch (state)
		{
		case 0:
			helloGL->InputManager.SetMouseButtonDown(Keys::CastToMouseButton(button));
			break;
		case 1:
			helloGL->InputManager.SetMouseButtonUp(Keys::CastToMouseButton(button));
			break;
		default:
			break;
		}

		helloGL->InputManager.SetCursorPosition(Vector2(x, y), Keys::MouseMovement::BUTTON_DOWN);
	}

	void MouseMotion(int x, int y)
	{
		helloGL->InputManager.SetCursorPosition(Vector2(x, y), Keys::MouseMovement::BUTTON_DOWN);
	}

	void MousePassiveMotion(int x, int y)
	{
		helloGL->InputManager.SetCursorPosition(Vector2(x, y), Keys::MouseMovement::PASSIVE);
	}
}