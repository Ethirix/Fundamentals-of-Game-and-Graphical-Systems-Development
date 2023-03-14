#include "HelloGL.h"

#include <cmath>
#include "GLUTCallbacks.h"

int main(int argc, char* argv[])
{
	HelloGL* window = new HelloGL(argc, argv);
	return 0;
}

HelloGL::HelloGL(int argc, char* argv[])
{
	GLUTCallbacks::Init(this);
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 800);

	glutCreateWindow("First OpenGL Program");

	glutDisplayFunc(GLUTCallbacks::Display);
	glutTimerFunc(FRAME_TIME, GLUTCallbacks::Timer, FRAME_TIME);

	glutKeyboardFunc(GLUTCallbacks::KeyboardDown);
	glutKeyboardUpFunc(GLUTCallbacks::KeyboardUp);
	glutSpecialFunc(GLUTCallbacks::KeyboardSpecialDown);
	glutSpecialUpFunc(GLUTCallbacks::KeyboardSpecialUp);

	glutMouseFunc(GLUTCallbacks::Mouse);
	glutMotionFunc(GLUTCallbacks::MouseMotion);
	glutPassiveMotionFunc(GLUTCallbacks::MousePassiveMotion);

	Camera = new ::Camera();

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, 800, 800);
	gluPerspective(75, 1, 0.1, 1000);
	glMatrixMode(GL_MODELVIEW);

	_sceneGraph.Objects.emplace_back(Model("Models/cube.txt"));

	glutMainLoop();
}

HelloGL::~HelloGL()
{
	delete Camera;
	Camera = nullptr;
}

void HelloGL::Update()
{
	glLoadIdentity();
	gluLookAt(Camera->Eye.X, Camera->Eye.Y, Camera->Eye.Z,
		Camera->Center.X, Camera->Center.Y, Camera->Center.Z,
	          Camera->Up.X, Camera->Up.Y, Camera->Up.Z);

	CheckKeyboardInputs();

	glutPostRedisplay();
}

void HelloGL::Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	DrawFrame();

	glFlush();
	glutSwapBuffers();
}

void HelloGL::CheckKeyboardInputs()
{
	if (InputManager.IsKeyDown(Keys::Keys::D))
	{
		_sceneGraph.Objects[0].Transform.Rotation.Z += 1.0f;
	}
	if (InputManager.IsKeyDown(Keys::Keys::A))
	{
		_sceneGraph.Objects[0].Transform.Rotation.Z -= 1.0f;
	}
	if (InputManager.IsKeyDown(Keys::Keys::W))
	{
		_sceneGraph.Objects[0].Transform.Rotation.X += 1.0f;
	}
	if (InputManager.IsKeyDown(Keys::Keys::S))
	{
		_sceneGraph.Objects[0].Transform.Rotation.X -= 1.0f;
	}
	if (InputManager.IsKeyDown(Keys::Keys::Q))
	{
		_sceneGraph.Objects[0].Transform.Rotation.Y -= 1.0f;
	}
	if (InputManager.IsKeyDown(Keys::Keys::E))
	{
		_sceneGraph.Objects[0].Transform.Rotation.Y += 1.0f;
	}

	if (InputManager.IsSpecialKeyDown(Keys::SpecialKeys::RIGHT_ARROW))
	{
		Camera->Center.X += 0.05f;
		Camera->Eye.X += 0.05f;
	}
	if (InputManager.IsSpecialKeyDown(Keys::SpecialKeys::LEFT_ARROW))
	{
		Camera->Eye.X -= 0.05f;
		Camera->Center.X -= 0.05f;
	}
	if (InputManager.IsSpecialKeyDown(Keys::SpecialKeys::DOWN_ARROW))
	{
		Camera->Eye.Z += 0.05f;
		Camera->Center.Z += 0.05f;
	}
	if (InputManager.IsSpecialKeyDown(Keys::SpecialKeys::UP_ARROW))
	{
		Camera->Eye.Z -= 0.05f;
		Camera->Center.Z -= 0.05f;
	}
	if (InputManager.IsKeyDown(Keys::Keys::SPACE))
	{
		Camera->Eye.Y += 0.05f;
		Camera->Center.Y += 0.05f;
	}
	if (InputManager.IsSpecialKeyDown(Keys::SpecialKeys::LEFT_CONTROL))
	{
		Camera->Eye.Y -= 0.05f;
		Camera->Center.Y -= 0.05f;
	}
}

void HelloGL::DrawFrame()
{
	for (Object& object : _sceneGraph.Objects)
	{
		TraverseSceneGraphChildren(object);
	}
}

void HelloGL::TraverseSceneGraphChildren(Object& object)
{
	glPushMatrix();
	UpdateObjectMatrix(object);
	DrawObject(object.Model);

	for (Object& child : object.Children)
	{
		TraverseSceneGraphChildren(child);
	}
	glPopMatrix();
}

void HelloGL::UpdateObjectMatrix(Object& obj)
{
	glTranslatef(obj.Transform.Position.X,
		obj.Transform.Position.Y,
		obj.Transform.Position.Z);

	glRotatef(obj.Transform.Rotation.X, 1, 0, 0);
	glRotatef(obj.Transform.Rotation.Y, 0, 1, 0);
	glRotatef(obj.Transform.Rotation.Z, 0, 0, -1);
}

void HelloGL::DrawObject(Model& model)
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, model.IndexedVertices.first);
	glColorPointer(3, GL_FLOAT, 0, model.IndexedColors.first);

	glDrawElements(GL_TRIANGLES, model.Indices.second, GL_UNSIGNED_SHORT, model.Indices.first);

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}