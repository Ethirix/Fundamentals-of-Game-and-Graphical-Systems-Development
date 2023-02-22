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

	glutInitWindowSize(800, 800);

	glutCreateWindow("First OpenGL Program");
	glutDisplayFunc(GLUTCallbacks::Display);

	glutTimerFunc(FRAME_TIME, GLUTCallbacks::Timer, FRAME_TIME);

	_sceneGraph.Objects.emplace_back(CreateNGon(8), ::Transform(Vector3(0.1, -0.5, 0)));
	_sceneGraph.Objects[0].Children.emplace_back(CreateNGon(4), ::Transform(Vector3(-0.9, 0.5, 0)));
	_sceneGraph.Objects[0].Children[0].Children.emplace_back(CreateNGon(6), ::Transform(Vector3(0.4, 0.2, 0.0), Vector3(45, 0, 0)));
	glutMainLoop();
}

HelloGL::~HelloGL(void)
{
}

void HelloGL::Display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	
	DrawModels();

	glFlush();
}

void HelloGL::DrawModels()
{
	for (Object& object : _sceneGraph.Objects)
	{
		object.Transform.Rotation.Z += 0.5f;
		DrawChildren(object);
	}
}

void HelloGL::DrawChildren(Object& object, Transform parentTransform)
{
	DrawModel(object, parentTransform);
	for (Object& child : object.Children)
	{
		//TODO: Figure out a far better way of writing this. -Possibly ask Peter or Craig about Overloading Operators...
		Transform t = Transform();
		t.Position.X = object.Transform.Position.X + parentTransform.Position.X;
		t.Position.Y = object.Transform.Position.Y + parentTransform.Position.Y;
		t.Position.Z = object.Transform.Position.Z + parentTransform.Position.Z;

		t.Rotation.X = object.Transform.Rotation.X + parentTransform.Rotation.X;
		t.Rotation.Y = object.Transform.Rotation.Y + parentTransform.Rotation.Y;
		t.Rotation.Z = object.Transform.Rotation.Z + parentTransform.Rotation.Z;
		//--------------------------------------------------------------------------------------------------------------

		DrawChildren(child, t);
	}
}

void HelloGL::DrawModel(Object& obj, Transform parentTransform)
{
	glPushMatrix();

	//TODO: Figure out how to rotate Objects around a point, using Parent-Child Relationship...

	glRotatef(parentTransform.Rotation.X, parentTransform.Position.X + 1, 0, 0);
	glRotatef(parentTransform.Rotation.Y, 0, parentTransform.Position.Y + 1, 0);
	glRotatef(parentTransform.Rotation.Z, 0, 0, parentTransform.Position.Z + 1);

	glTranslatef(parentTransform.Position.X + obj.Transform.Position.X,
	             parentTransform.Position.Y + obj.Transform.Position.Y,
	             parentTransform.Position.Z + obj.Transform.Position.Z);

	//local rotation?
	glRotatef(obj.Transform.Rotation.X, 1, 0, 0);
	glRotatef(obj.Transform.Rotation.Y, 0, 1, 0);
	glRotatef(obj.Transform.Rotation.Z, 0, 0, 1);

	//-----------------------------------------------------------------------------------------

	DrawShape(obj.Model);
	glPopMatrix();
}


void HelloGL::DrawPolygon()
{
#pragma region Shapes
	Model::Model scalene = Model::Model();
	scalene.Polygons.emplace_back(
		Model::Vertex2D(-0.9, 0.9),
			Model::Vertex2D(-0.85, 1.0),
			Model::Vertex2D(-0.75, 0.9)

	);

	Model::Model isosceles = Model::Model();
	isosceles.Polygons.emplace_back(
		Model::Vertex2D(-0.75, 0.8),
			Model::Vertex2D(-0.7, 1.0),
			Model::Vertex2D(-0.65, 0.8)

	);

	Model::Model equilateral = Model::Model();
	equilateral.Polygons.emplace_back(
		Model::Vertex2D(-0.65, 0.7),
			Model::Vertex2D(-0.45, 1.0),
			Model::Vertex2D(-0.25, 0.7)

	);

	Model::Model acute = Model::Model();
	acute.Polygons.emplace_back(
		Model::Vertex2D(-0.25, 0.9),
			Model::Vertex2D(-0.225, 1.0),
			Model::Vertex2D(-0.15, 0.9)

	);

	Model::Model rightangle = Model::Model();
	rightangle.Polygons.emplace_back(
		Model::Vertex2D(-1.0, 1.0),
			Model::Vertex2D(-1.0, 0.9),
			Model::Vertex2D(-0.9, 0.9)

	);

	Model::Model obtuse = Model::Model();
	obtuse.Polygons.emplace_back(
		Model::Vertex2D(-0.15, 1.0),
			Model::Vertex2D(-0.05, 0.8),
			Model::Vertex2D(-0.2, 0.8)

	);
#pragma endregion

	Model::Model ngon = CreateNGon(10, 360.0f / 16.0f * (PI / 180));
	DrawShape(ngon);
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
	float angleIncrease = 2.0f * PI / n;

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

void HelloGL::Update()
{
	glutPostRedisplay();
}