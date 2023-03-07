#include "GLUTCallbacks.h"
#include "HelloGL.h"
#include "InputEnums.h"

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
		helloGL->Keyboard(Keys::CastToKey(key), KeyState::DOWN, x, y);
	}

	void KeyboardUp(unsigned char key, int x, int y)
	{
		helloGL->Keyboard(Keys::CastToKey(key), KeyState::UP, x, y);
	}

	void KeyboardSpecialDown(int key, int x, int y)
	{
		helloGL->Keyboard(Keys::GetSpecialKeyFromInt(key), KeyState::DOWN, x, y);
	}

	void KeyboardSpecialUp(int key, int x, int y)
	{
		helloGL->Keyboard(Keys::GetSpecialKeyFromInt(key), KeyState::UP, x, y);
	}

	void Mouse(int button, int state, int x, int y)
	{
		
	}

	void MouseMotion(int x, int y)
	{
		
	}

	void MousePassiveMotion(int x, int y)
	{
		
	}
}