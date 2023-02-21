#include "HelloGL.h"
#include "GLUTCallbacks.h"

int main(int argc, char* argv[])
{
	HelloGL* window = new HelloGL(argc, argv);
	return 0;
}

HelloGL::HelloGL(int argc, char* argv[])
{
	rotation = 0.0f;

	GLUTCallbacks::Init(this);
	glutInit(&argc, argv);

	glutInitWindowSize(800, 800);

	glutCreateWindow("First OpenGL Program");
	glutDisplayFunc(GLUTCallbacks::Display);

	glutTimerFunc(FRAME_TIME, GLUTCallbacks::Timer, FRAME_TIME);

	_sceneGraph.Objects.push_back(Object(CreateNGon(8), ::Transform(0.1, -0.5, 0)));
	_sceneGraph.Objects[0].Children.push_back(Object(CreateNGon(4), ::Transform(-0.9, 0.5, 0)));
	_sceneGraph.Objects[0].Children[0].Children.push_back(Object(CreateNGon(6), ::Transform(0.6, 0.0, 0.0)));
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
		DrawModel(object);
		DrawChildren(object);
	}
}

void HelloGL::DrawChildren(Object& parent)
{
	DrawModel(parent);
	for (Object& child : parent.Children)
	{
		DrawChildren(child);
	}
}

void HelloGL::DrawModel(Object& obj)
{
	glPushMatrix();
	glTranslatef(obj.Transform.X, obj.Transform.Y, obj.Transform.Z);

	glRotatef(rotation, rotation, rotation, -rotation);

	DrawShape(obj.Model);
	glPopMatrix();
}


void HelloGL::DrawPolygon()
{
#pragma region Shapes
	Model::Model scalene = Model::Model();
	scalene.Polygons.push_back(
		Model::Polygon(
			Model::Vertex2D(-0.9, 0.9),
			Model::Vertex2D(-0.85, 1.0),
			Model::Vertex2D(-0.75, 0.9)
		)
	);

	Model::Model isosceles = Model::Model();
	isosceles.Polygons.push_back(
		Model::Polygon(
			Model::Vertex2D(-0.75, 0.8),
			Model::Vertex2D(-0.7, 1.0),
			Model::Vertex2D(-0.65, 0.8)
		)
	);

	Model::Model equilateral = Model::Model();
	equilateral.Polygons.push_back(
		Model::Polygon(
			Model::Vertex2D(-0.65, 0.7),
			Model::Vertex2D(-0.45, 1.0),
			Model::Vertex2D(-0.25, 0.7)
		)
	);

	Model::Model acute = Model::Model();
	acute.Polygons.push_back(
		Model::Polygon(
			Model::Vertex2D(-0.25, 0.9),
			Model::Vertex2D(-0.225, 1.0),
			Model::Vertex2D(-0.15, 0.9)
		)
	);

	Model::Model rightangle = Model::Model();
	rightangle.Polygons.push_back(
		Model::Polygon(
			Model::Vertex2D(-1.0, 1.0),
			Model::Vertex2D(-1.0, 0.9),
			Model::Vertex2D(-0.9, 0.9)
		)
	);

	Model::Model obtuse = Model::Model();
	obtuse.Polygons.push_back(
		Model::Polygon(
			Model::Vertex2D(-0.15, 1.0),
			Model::Vertex2D(-0.05, 0.8),
			Model::Vertex2D(-0.2, 0.8)
		)
	);
#pragma endregion

	Model::Model ngon = CreateNGon(10, (360 / 16) * (PI / 180));
	DrawShape(ngon);
}

void HelloGL::DrawShape(Model::Model model)
{
	for (Model::Polygon const &p : model.Polygons)
	{
		glBegin(GL_POLYGON);
		for (int i = 0; i < 3; i++)
		{
			glVertex2f(p.Vertices[i].X, p.Vertices[i].Y);
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
		shape.Polygons.push_back(
			Model::Polygon(
				Model::Vertex2D(0, 0),
				Model::Vertex2D(0 + 0.2 * cos(angle), 0 + 0.2 * sin(angle)),
				Model::Vertex2D(0 + 0.2 * cos(angle + angleIncrease), 
					0 + 0.2 * sin(angle + angleIncrease))
			)
		);
		angle += angleIncrease;
		
	}

	return shape;
}

void HelloGL::Update()
{
	glutPostRedisplay();

	rotation += 0.5f;
	if (rotation > 360.0f)
	{
		rotation = 0.0f;
	}


}