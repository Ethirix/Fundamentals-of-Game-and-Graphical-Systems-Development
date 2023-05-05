#pragma once

class HelloGL;

namespace GLUTCallbacks
{
	void Init(HelloGL* gl);

	void Display();

	void Timer(int frameTime);

	void KeyboardDown(unsigned char key, int x, int y);
	void KeyboardUp(unsigned char key, int x, int y);
	void KeyboardSpecialDown(int key, int x, int y);
	void KeyboardSpecialUp(int key, int x, int y);

	void Mouse(int button, int state, int x, int y);
	void MouseMotion(int x, int y);
	void MousePassiveMotion(int x, int y);

	void OnWindowResize(int w, int h);
}
