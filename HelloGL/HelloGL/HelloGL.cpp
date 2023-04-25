#include "HelloGL.h"

#include "GLUTCallbacks.h"
#include "Screen.h"
#include "Texture2D.h"

int main(int argc, char* argv[])
{
	HelloGL* window = new HelloGL(argc, argv);
	return 0;
}

HelloGL::HelloGL(int argc, char* argv[])
{
	GLUTCallbacks::Init(this);
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 800);

	glutCreateWindow("First OpenGL Program");

	glutDisplayFunc(GLUTCallbacks::Display);
	glutReshapeFunc(GLUTCallbacks::OnWindowResize);

	glutTimerFunc(FRAME_TIME, GLUTCallbacks::Timer, FRAME_TIME);

	glutKeyboardFunc(GLUTCallbacks::KeyboardDown);
	glutKeyboardUpFunc(GLUTCallbacks::KeyboardUp);
	glutSpecialFunc(GLUTCallbacks::KeyboardSpecialDown);
	glutSpecialUpFunc(GLUTCallbacks::KeyboardSpecialUp);

	glutMouseFunc(GLUTCallbacks::Mouse);
	glutMotionFunc(GLUTCallbacks::MouseMotion);
	glutPassiveMotionFunc(GLUTCallbacks::MousePassiveMotion);

	Camera = new ::Camera();

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, 800, 800);
	gluPerspective(75, 1, 0.1, 1000);
	glMatrixMode(GL_MODELVIEW);

	for (unsigned i = 0; i < 10000; i++)
	{
		_sceneGraph.Objects.InsertFirst(std::make_shared<Object>(
			"Models/cube2.txt",
			"Textures/Penguins.raw",
			Transform(
				Vector3(rand() % 2000 / 10.0f - 20, rand() % 800 / 10.0f - 20, rand() % 800 / 10.0f - 20),
				Vector3(rand() % 720, rand() % 720, rand() % 720)
			))
		);
	}

	glutMainLoop();
}

HelloGL::~HelloGL()
{
	delete Camera;
	Camera = nullptr;
}

void HelloGL::OnWindowResize(int width, int height)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, width, height);
	gluPerspective(Camera->FieldOfView, static_cast<GLdouble>(width) / height, Camera->NearPlane, Camera->FarPlane);
	Screen::SetResolution(width, height);
	glMatrixMode(GL_MODELVIEW);

	Display();
}

void HelloGL::Update()
{
	glLoadIdentity();
	gluLookAt(Camera->Eye.X, Camera->Eye.Y, Camera->Eye.Z,
		Camera->Center.X, Camera->Center.Y, Camera->Center.Z,
	          Camera->Up.X, Camera->Up.Y, Camera->Up.Z);

	CheckKeyboardInputs();
	Mesh::CheckMeshExistsInGame();

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
	if (InputManager.IsKeyDown(Keys::Keys::F))
	{
		_sceneGraph.Objects.DeleteList();
	}

	if (InputManager.IsKeyDown(Keys::Keys::T))
	{
		_sceneGraph.Objects.DeleteAt(0);
	}

	if (InputManager.IsSpecialKeyDown(Keys::SpecialKeys::RIGHT_ARROW))
	{
		Camera->Center.X += 0.1f;
		Camera->Eye.X += 0.1f;
	}
	if (InputManager.IsSpecialKeyDown(Keys::SpecialKeys::LEFT_ARROW))
	{
		Camera->Eye.X -= 0.1f;
		Camera->Center.X -= 0.1f;
	}
	if (InputManager.IsSpecialKeyDown(Keys::SpecialKeys::DOWN_ARROW))
	{
		Camera->Eye.Z += 0.1f;
		Camera->Center.Z += 0.1f;
	}
	if (InputManager.IsSpecialKeyDown(Keys::SpecialKeys::UP_ARROW))
	{
		Camera->Eye.Z -= 0.1f;
		Camera->Center.Z -= 0.1f;
	}
	if (InputManager.IsKeyDown(Keys::Keys::SPACE))
	{
		Camera->Eye.Y += 0.1f;
		Camera->Center.Y += 0.1f;
	}
	if (InputManager.IsSpecialKeyDown(Keys::SpecialKeys::LEFT_CONTROL))
	{
		Camera->Eye.Y -= 0.1f;
		Camera->Center.Y -= 0.1f;
	}
}

void HelloGL::DrawFrame()
{
	ListNode<std::shared_ptr<Object>>* node = _sceneGraph.Objects.GetNode(0);
	while (node != nullptr)
	{
		TraverseSceneGraphChildren(node);
		node = node->Next;
	}
}

void HelloGL::TraverseSceneGraphChildren(ListNode<std::shared_ptr<Object>>* node)
{
	glPushMatrix();
	UpdateObjectMatrix(node->Data);
	DrawObject(node->Data);

	ListNode<std::shared_ptr<Object>>* childNode = node->Data->Children.GetNode(0);
	while (childNode != nullptr)
	{
		TraverseSceneGraphChildren(childNode);
		childNode = childNode->Next;
	}
	glPopMatrix();
}

void HelloGL::UpdateObjectMatrix(const std::shared_ptr<Object>& obj)
{
	glTranslatef(obj->Transform.Position.X,
		obj->Transform.Position.Y,
		obj->Transform.Position.Z);

	glRotatef(obj->Transform.Rotation.X, 1, 0, 0);
	glRotatef(obj->Transform.Rotation.Y, 0, 1, 0);
	glRotatef(obj->Transform.Rotation.Z, 0, 0, -1);
}

void HelloGL::DrawObject(const std::shared_ptr<Object>& obj)
{
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, obj->Mesh->IndexedVertices.Index);
	glColorPointer(3, GL_FLOAT, 0, obj->Mesh->IndexedColors.Index);
	glTexCoordPointer(2, GL_FLOAT, 0, obj->Mesh->TextureCoordinates.Index);

	glDrawElements(GL_TRIANGLES, obj->Mesh->Indices.IndexLength, GL_UNSIGNED_SHORT, obj->Mesh->Indices.Index);

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}