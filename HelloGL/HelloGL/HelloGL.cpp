#include "HelloGL.h"

#include "GLUTCallbacks.h"
#include "Screen.h"
#include "Texture2D.h"

int main(int argc, char* argv[])
{
	HelloGL* window = new HelloGL(argc, argv);
	return 0;
}

//TODO: Text Display
//TODO: Materials and Lighting
//TODO: Additional Features
//TODO: A Scene (simulation or something).

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

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glutSetCursor(GLUT_CURSOR_NONE);

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

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);

	_light = Light(Vector3(10.0f, 25.0f, 10.0f), 
		Lighting(
			Vector4(0.2f, 0.2f, 0.2f, 1.0f), 
			Vector4(1.0f, 1.0f, 1.0f, 1.0f),
			Vector4(0.2f, 0.2f, 0.2f, 1.0f)
		)
	);

	auto plane = _sceneGraph.Objects.InsertFirst(
		std::make_shared<Object>(
			"Models/plane.obj",
			"Textures/planeTexture.tga",
			Transform(),
			Material(
				Vector4(1,1,1,1),
				Vector4(1,1,1,1), 
				Vector4(0, 0, 0, 1),
				0
			)
		)
	);

	auto text = plane->Data->Children.InsertFirst(
		std::make_shared<Text>(
			"Currently Selected Object: [NONE]",
			Transform(
				Vector3(3, 3, 0)
			)
		)
	);

	_selectedText = std::static_pointer_cast<Text>(text->Data);

	auto table =  plane->Data->Children.InsertFirst(
		std::make_shared<Object>(
			"Models/table.obj", 
			"Textures/tableTexture.tga",
			Transform(),
			Material(
				Vector4(1,1,1,1),
				Vector4(1,1,1,1), 
				Vector4(1, 1, 1, 1),
				100
			)
		)
	);

	auto icoSphere = plane->Data->Children.InsertFirst(
		std::make_shared<Object>(
			"Models/icosphere.obj",
			"Textures/IcosphereTexture.tga"
		)
	);

	auto mug = table->Data->Children.InsertFirst(
		std::make_shared<Object>(
			"Models/mug.obj",
			"Textures/mugTexture.tga",
			Transform(
				Vector3(0.2f, 1.65f, 0),
				Vector3(0, 25.0f, 0)
			)
		)
	);

	glutWarpPointer(Screen::GetResolution().X / 2, Screen::GetResolution().Y / 2);
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

	if (_mouseBoundToScreen)
	{
		Vector2 resolution = Screen::GetResolution();
		if (resolution.X % 2 != 0)
			resolution.X--;
		if (resolution.Y % 2 != 0)
			resolution.Y--;

		Camera->Yaw += InputManager.GetCursorPosition().X - resolution.X / 2.0f;
		Camera->Pitch -= InputManager.GetCursorPosition().Y - resolution.Y / 2.0f;

		if (Camera->Pitch > 89.0f)
			Camera->Pitch = 89.0f;
		if (Camera->Pitch < -89.0f)
			Camera->Pitch = -89.0f;

		Camera->Eye = Camera->Position; //GLOBAL SPACE MOVEMENT

		Vector3 dir;
		dir.X = cos((PI * Camera->Yaw) / 180) * cos((PI * Camera->Pitch) / 180);
		dir.Y = sin((PI * Camera->Pitch) / 180);
		dir.Z = sin((PI * Camera->Yaw) / 180) * cos((PI * Camera->Pitch) / 180);
		Camera->Center = Camera->Eye + dir.Normalize();

		glutWarpPointer(resolution.X / 2, resolution.Y / 2);
	}

	gluLookAt(Camera->Eye.X, Camera->Eye.Y, Camera->Eye.Z,
		Camera->Center.X, Camera->Center.Y, Camera->Center.Z,
	          Camera->Up.X, Camera->Up.Y, Camera->Up.Z);

	CheckKeyboardInputs();
	Mesh::CheckMeshExistsInGame();
	Texture2D::CheckTextureExistsInGame();

	if (_keybindCooldown)
	{
		_keybindCooldownTimer += FRAME_TIME;
		if (_keybindCooldownTimer >= _keybindCooldownTime)
		{
			_keybindCooldown = false;
			_keybindCooldownTimer = 0;
		}
	}

	if (_enableSelection)
	{
		std::stringstream ss;
		ss << "Currently Selected Object: ";
		if (_selectedObjectTree.GetLastNode())
		{
			auto obj = _selectedObjectTree.GetLastNode()->Data->Children.GetNode(_selectedWidth)->Data;
			ss << obj->Name << "\n";
			ss << "Position: X: " << obj->Transform.Position.X << " Y: " << obj->Transform.Position.Y << " Z: " << obj->Transform.Position.Z << "\n";
			ss << "Rotation: X: " << obj->Transform.Rotation.X << " Y: " << obj->Transform.Rotation.Y << " Z: " << obj->Transform.Rotation.Z << "\n";
		}
		else
		{
			auto obj = _sceneGraph.Objects.GetNode(_selectedWidth)->Data;
			ss << obj->Name << "\n";
			ss << "Position: X: " << obj->Transform.Position.X << " Y: " << obj->Transform.Position.Y << " Z: " << obj->Transform.Position.Z << "\n";
			ss << "Rotation: X: " << obj->Transform.Rotation.X << " Y: " << obj->Transform.Rotation.Y << " Z: " << obj->Transform.Rotation.Z << "\n";
		}

		_selectedText->String = ss.str();
	}
	else
	{
		_selectedText->String = "Selection Disabled";
	}

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
	if (InputManager.IsKeyDown(Keys::Keys::FORWARD_SLASH) && !_keybindCooldown)
	{
		_enableSelection = !_enableSelection;
		_selectedObjectTree.DeleteList();
		_selectedWidth = 0;

		_keybindCooldown = true;
	}
	if (InputManager.IsKeyDown(Keys::Keys::SIX) && !_keybindCooldown)
	{
		if (_selectedObjectTree.GetNode(0) && _sceneGraph.Objects.GetNode(_selectedWidth + 1))
		{
			_selectedWidth += 1;
			_keybindCooldown = true;
		}
		else if (_selectedObjectTree.GetLastNode() && _selectedObjectTree.GetLastNode()->Data->Children.GetNode(_selectedWidth + 1))
		{
			_selectedWidth += 1;
			_keybindCooldown = true;
		}
	}
	if (InputManager.IsKeyDown(Keys::Keys::FOUR) && !_keybindCooldown)
	{
		if ((_selectedObjectTree.GetNode(0) && _sceneGraph.Objects.GetNode(_selectedWidth - 1)))
		{
			_selectedWidth -= 1;
			_keybindCooldown = true;
		}
		else if (_selectedObjectTree.GetLastNode() && _selectedObjectTree.GetLastNode()->Data->Children.GetNode(_selectedWidth - 1))
		{
			_selectedWidth -= 1;
			_keybindCooldown = true;
		}
	}
	if (InputManager.IsKeyDown(Keys::Keys::TWO) && !_keybindCooldown)
	{
		std::shared_ptr<Object> parent;

		if (!_selectedObjectTree.GetLastNode())
		{
			parent = _sceneGraph.Objects.GetNode(_selectedWidth)->Data;
		}
		else
		{
			parent = _selectedObjectTree.GetLastNode()->Data->Children.GetNode(_selectedWidth)->Data;
		}

		if (parent->Children.GetNode(0))
		{
			if (!_selectedObjectTree.GetLastNode() || _selectedObjectTree.GetLastNode()->Data != parent)
			{
				_selectedObjectTree.MakeNode(parent);
				_selectedWidth = 0;
				_keybindCooldown = true;
			}
		}
	}
	if (InputManager.IsKeyDown(Keys::Keys::EIGHT) && !_keybindCooldown)
	{
		if (_selectedObjectTree.GetLastNode())
		{
			_selectedObjectTree.DeleteAt(_selectedObjectTree.GetIndex(_selectedObjectTree.GetLastNode()));
			_selectedWidth = 0;
			_keybindCooldown = true;
		}
	}

	if (_enableSelection && InputManager.IsKeyDown(Keys::Keys::W))
	{
		if (_selectedObjectTree.GetLastNode())
		{
			_selectedObjectTree.GetLastNode()->Data->Children.GetNode(_selectedWidth)->Data->Transform.Position.Z -= 0.05f;
		}
		else
		{
			_sceneGraph.Objects.GetNode(_selectedWidth)->Data->Transform.Position.Z -= 0.05f;
		}

	}
	if (_enableSelection && InputManager.IsKeyDown(Keys::Keys::S))
	{
		if (_selectedObjectTree.GetLastNode())
		{
			_selectedObjectTree.GetLastNode()->Data->Children.GetNode(_selectedWidth)->Data->Transform.Position.Z += 0.05f;
		}
		else
		{
			_sceneGraph.Objects.GetNode(_selectedWidth)->Data->Transform.Position.Z += 0.05f;
		}
	}
	if (_enableSelection && InputManager.IsKeyDown(Keys::Keys::A))
	{
		if (_selectedObjectTree.GetLastNode())
		{
			_selectedObjectTree.GetLastNode()->Data->Children.GetNode(_selectedWidth)->Data->Transform.Position.X -= 0.05f;
		}
		else
		{
			_sceneGraph.Objects.GetNode(_selectedWidth)->Data->Transform.Position.X -= 0.05f;
		}
	}
	if (_enableSelection && InputManager.IsKeyDown(Keys::Keys::D))
	{
		if (_selectedObjectTree.GetLastNode())
		{
			_selectedObjectTree.GetLastNode()->Data->Children.GetNode(_selectedWidth)->Data->Transform.Position.X += 0.05f;
		}
		else
		{
			_sceneGraph.Objects.GetNode(_selectedWidth)->Data->Transform.Position.X += 0.05f;
		}
	}
	if (_enableSelection && InputManager.IsKeyDown(Keys::Keys::Q))
	{
		if (_selectedObjectTree.GetLastNode())
		{
			_selectedObjectTree.GetLastNode()->Data->Children.GetNode(_selectedWidth)->Data->Transform.Rotation.Y -= 1.0f;
		}
		else
		{
			_sceneGraph.Objects.GetNode(_selectedWidth)->Data->Transform.Rotation.Y -= 1.0f;
		}
	}
	if (_enableSelection && InputManager.IsKeyDown(Keys::Keys::E))
	{
		if (_selectedObjectTree.GetLastNode())
		{
			_selectedObjectTree.GetLastNode()->Data->Children.GetNode(_selectedWidth)->Data->Transform.Rotation.Y += 1.0f;
		}
		else
		{
			_sceneGraph.Objects.GetNode(_selectedWidth)->Data->Transform.Rotation.Y += 1.0f;
		}
	}
	if (_enableSelection && InputManager.IsKeyDown(Keys::Keys::R))
	{
		if (_selectedObjectTree.GetLastNode())
		{
			_selectedObjectTree.GetLastNode()->Data->Children.GetNode(_selectedWidth)->Data->Transform.Rotation.X -= 1.0f;
		}
		else
		{
			_sceneGraph.Objects.GetNode(_selectedWidth)->Data->Transform.Rotation.X -= 1.0f;
		}
	}
	if (_enableSelection && InputManager.IsKeyDown(Keys::Keys::F))
	{
		if (_selectedObjectTree.GetLastNode())
		{
			_selectedObjectTree.GetLastNode()->Data->Children.GetNode(_selectedWidth)->Data->Transform.Rotation.X += 1.0f;
		}
		else
		{
			_sceneGraph.Objects.GetNode(_selectedWidth)->Data->Transform.Rotation.X += 1.0f;
		}
	}
	if (_enableSelection && InputManager.IsKeyDown(Keys::Keys::SPACE))
	{
		if (_selectedObjectTree.GetLastNode())
		{
			_selectedObjectTree.GetLastNode()->Data->Children.GetNode(_selectedWidth)->Data->Transform.Position.Y += 0.05f;
		}
		else
		{
			_sceneGraph.Objects.GetNode(_selectedWidth)->Data->Transform.Position.Y += 0.05f;
		}
	}
	if (_enableSelection && InputManager.IsSpecialKeyDown(Keys::SpecialKeys::LEFT_CONTROL))
	{
		if (_selectedObjectTree.GetLastNode())
		{
			_selectedObjectTree.GetLastNode()->Data->Children.GetNode(_selectedWidth)->Data->Transform.Position.Y -= 0.05f;
		}
		else
		{
			_sceneGraph.Objects.GetNode(_selectedWidth)->Data->Transform.Position.Y -= 0.05f;
		}
	}

	if (InputManager.IsKeyDown(Keys::Keys::HASH))
	{
		_sceneGraph.Objects.DeleteList();
	}

	if (InputManager.IsKeyDown(Keys::Keys::SQUARE_BRACKET_RIGHT) && !_keybindCooldown)
	{
		_sceneGraph.Objects.DeleteAt(0);
		_keybindCooldown = true;
	}

	if (InputManager.IsSpecialKeyDown(Keys::SpecialKeys::RIGHT_ARROW) && _mouseBoundToScreen)
	{
		Camera->Position.X += 0.1f;
	}
	if (InputManager.IsSpecialKeyDown(Keys::SpecialKeys::LEFT_ARROW) && _mouseBoundToScreen)
	{
		Camera->Position.X -= 0.1f;
	}
	if (InputManager.IsSpecialKeyDown(Keys::SpecialKeys::DOWN_ARROW) && _mouseBoundToScreen)
	{
		Camera->Position.Z += 0.1f;
	}
	if (InputManager.IsSpecialKeyDown(Keys::SpecialKeys::UP_ARROW) && _mouseBoundToScreen)
	{
		Camera->Position.Z -= 0.1f;
		//Camera->Eye = Camera->Center; FORWARD ROTATION BASED ONLY
	}
	if (InputManager.IsSpecialKeyDown(Keys::SpecialKeys::RIGHT_SHIFT) && _mouseBoundToScreen)
	{
		Camera->Position.Y += 0.1f;
	}
	if (InputManager.IsSpecialKeyDown(Keys::SpecialKeys::RIGHT_CONTROL) && _mouseBoundToScreen)
	{
		Camera->Position.Y -= 0.1f;
	}

	if (InputManager.IsKeyDown(Keys::Keys::ESCAPE) && !_keybindCooldown)
	{
		_mouseBoundToScreen = !_mouseBoundToScreen;
		_keybindCooldown = true;

		if (_mouseBoundToScreen)
		{
			glutSetCursor(GLUT_CURSOR_NONE);
			Vector2 resolution = Screen::GetResolution();
			glutWarpPointer(resolution.X / 2, resolution.Y / 2);
		}
		if (!_mouseBoundToScreen)
			glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
	}

	if (InputManager.IsSpecialKeyDown(Keys::SpecialKeys::LEFT_ALT) && InputManager.IsSpecialKeyDown(Keys::SpecialKeys::F4))
	{
		glutLeaveMainLoop();
	}
}

void HelloGL::DrawFrame()
{
	DrawLight();

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
	if (obj->Mesh == nullptr)
	{
		if (auto text = std::static_pointer_cast<Text>(obj))
			DrawString(text);

		return;
	}

	glBindTexture(GL_TEXTURE_2D, obj->Texture->GetID());

	glBegin(GL_TRIANGLES);
	for (int i = 0; i < obj->Mesh->VertexIndices.IndexLength; i++)
	{
		glNormal3f(obj->Mesh->IndexedNormals.Index[obj->Mesh->NormalIndices.Index[i]].X,
		           obj->Mesh->IndexedNormals.Index[obj->Mesh->NormalIndices.Index[i]].Y,
		           obj->Mesh->IndexedNormals.Index[obj->Mesh->NormalIndices.Index[i]].Z);

		glTexCoord2f(obj->Mesh->TextureCoordinates.Index[obj->Mesh->TexCoordIndices.Index[i]].U,
		             obj->Mesh->TextureCoordinates.Index[obj->Mesh->TexCoordIndices.Index[i]].V);

		glMaterialfv(GL_FRONT, GL_AMBIENT, &obj->Material.Ambient.X);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, &obj->Material.Diffuse.X);
		glMaterialfv(GL_FRONT, GL_SPECULAR, &obj->Material.Specular.X);
		glMaterialf(GL_FRONT, GL_SHININESS, obj->Material.Shininess);

		glVertex3f(obj->Mesh->IndexedVertices.Index[obj->Mesh->VertexIndices.Index[i]].X,
		           obj->Mesh->IndexedVertices.Index[obj->Mesh->VertexIndices.Index[i]].Y,
		           obj->Mesh->IndexedVertices.Index[obj->Mesh->VertexIndices.Index[i]].Z);
	}
	glEnd();

	/*glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);

	glNormalPointer(GL_FLOAT, 0, obj->Mesh->IndexedNormals.Index);
	glTexCoordPointer(2, GL_FLOAT, 0, obj->Mesh->TextureCoordinates.Index);
	glVertexPointer(3, GL_FLOAT, 0, obj->Mesh->IndexedVertices.Index);

	glDrawElements(GL_TRIANGLES, obj->Mesh->VertexIndices.IndexLength, GL_UNSIGNED_SHORT, obj->Mesh->VertexIndices.Index);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);*/
}

void HelloGL::DrawLight()
{
	glLightfv(GL_LIGHT0, GL_AMBIENT, &_light.Lighting.Ambient.X);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, &_light.Lighting.Diffuse.X);
	glLightfv(GL_LIGHT0, GL_SPECULAR, &_light.Lighting.Specular.X);

	glLightfv(GL_LIGHT0, GL_POSITION, &_light.Position.X);
}

void HelloGL::DrawString(const std::shared_ptr<Text>& text)
{
	glDisable(GL_LIGHTING);
	glRasterPos2f(0.0f, 0.0f);
	glColor3f(text->Color.X, text->Color.Y, text->Color.Z);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)text->String.c_str());
	glEnable(GL_LIGHTING);
}