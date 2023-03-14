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

	glutInitDisplayMode(GLUT_DOUBLE);
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

	_sceneGraph.Objects.emplace_back(CreateNGon(8), ::Transform(Vector3(0.0, 0.0, 0)));
	_sceneGraph.Objects[0].Children.emplace_back(CreateNGon(6), ::Transform(Vector3(-0.5f, 0.5, 0)));
	_sceneGraph.Objects[0].Children[0].Children.emplace_back(CreateNGon(4), ::Transform(Vector3(0.4f, 0.2f, 0.0)));

	glutMainLoop();
}

HelloGL::~HelloGL(void)
{
}

void HelloGL::Update()
{
	Keyboard();
	glutPostRedisplay();
}

void HelloGL::Display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	DrawModels();

	glFlush();
	glutSwapBuffers();
}

void HelloGL::Keyboard()
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
}

void HelloGL::DrawModels()
{
	for (Object& object : _sceneGraph.Objects)
	{
				
		DrawChildren(object);
	}
}

void HelloGL::DrawChildren(Object& object)
{
	glPushMatrix();
	DrawModel(object);

	for (Object& child : object.Children)
	{
		DrawChildren(child);
	}
	glPopMatrix();
}

void HelloGL::DrawModel(Object& obj)
{
	glTranslatef(obj.Transform.Position.X,
		obj.Transform.Position.Y,
		obj.Transform.Position.Z);

	glRotatef(obj.Transform.Rotation.X, 1, 0, 0);
	glRotatef(obj.Transform.Rotation.Y, 0, 1, 0);
	glRotatef(obj.Transform.Rotation.Z, 0, 0, 1);

	DrawShape(obj.Model);
}

void HelloGL::DrawShape(const Model::Model& model)
{
	for (Model::Polygon const &p : model.Polygons)
	{
		glBegin(GL_POLYGON);
		for (Model::Vertex2D vertex : p.Vertices)
		{
			glVertex2f(vertex.X, vertex.Y);
		}
		glEnd();
	}
}

Model::Model HelloGL::CreateNGon(int n, float angle)
{
	float angleIncrease = 2.0 * PI / n;

	Model::Model shape;

	for (int i = 0; i < n; i++)
	{
		shape.Polygons.emplace_back(
			Model::Vertex2D(0, 0),
			Model::Vertex2D(0.2f * std::cos(angle), 0.2f * std::sin(angle)),
			Model::Vertex2D(0.2f * std::cos(angle + angleIncrease), 
				0.2f * std::sin(angle + angleIncrease))
		);
		angle += angleIncrease;
		
	}

	return shape;
}